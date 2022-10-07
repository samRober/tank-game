#include "LaserPlayerTurret.h"
#include "GameObjectManager.h"
#include "maths/math_utils.h"

LaserPlayerTurret::LaserPlayerTurret(float x, float y, ModelLoader& ml, b2World& world):
	Turret(x,y,ml,world,ObjectType::player)
{
	set_mesh(ml.loadMeshFromFile("laser_barrel.scn"));
	turn_speed_ = 750;
	body_->SetAngularDamping(4);
	body_->SetSleepingAllowed(false);
	modelOffset_ = gef::Vector4(0, 1, 0);
	b2PolygonShape shape;
	shape.SetAsBox(0.84, 1.82f, b2Vec2(0.0f, 0.4f), 0);


	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 0.2f;
	fixture_def.friction = 0.1f;
	fixture_def.restitution = 0.5;
	fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::air);
	fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::air);
	fixture_def.filter.groupIndex = static_cast<int>(CollisionGroups::player);
	body_->CreateFixture(&fixture_def);
}

void LaserPlayerTurret::update(const float delta_time)
{
	Turret::update(delta_time);
	timer += delta_time;
	fire_time += delta_time;
	if (fire_time <= max_fire_time) {
		gef::Vector2 dir = get_dir();
		dir.Normalise();
		auto position = body_->GetPosition();
		position.x += dir.x * 2.5f;
		position.y += dir.y * 2.5f;



		auto world = body_->GetWorld();
		//raycast
		LaserRaycastCallback callback;
		auto target = position;
		target.x += dir.x * 15.f;
		target.y += dir.y * 15.f;
		world->RayCast(&callback, position, target);
		//end point is the point that the recast hit an object
		b2Vec2 end_point;
		if (callback.m_fixture) {
			end_point = callback.m_point;
			end_point -= position;
			auto hit_object = reinterpret_cast<GameObject*>(callback.m_fixture->GetBody()->GetUserData().pointer);
		//	hit_object->handle_collision(ObjectType::laser_beam);
		}
		else {//if the raycast didn't hit an object then just set the endpoint to the end point of the raycast
			end_point = target;
			end_point -= position;
		}
		float i = 0;
		//spawn a red cube with a width of 0.25 every 0.25 units until the end point 
		for (float len = end_point.Length(); len > 0; len -= 0.25f) {

			gef::Transform laser_trans;
			laser_trans.Set(transform());
			laser_trans.set_scale(gef::Vector4(0.5f, 0.5f, 0.5f));
			laser_trans.set_translation(gef::Vector4(position.x + dir.x * 0.25 * i, 1, position.y + dir.y * 0.25 * i));

			auto laser_beam = std::make_unique<Particle>(0.01f);
			laser_beam->set_mesh(ml_.loadMeshFromFile("laser.scn"));
			laser_beam->set_start_transform(laser_trans.GetMatrix());
			laser_beam->set_end_transform(laser_trans.GetMatrix());


			manager_->add_particle(std::move(laser_beam));

			i++;
		}

		

		//play sound
		if (!audio_manager_->sample_voice_playing(fire_sound_id)) {
			audio_manager_->PlaySample(fire_sound_id);
		}
	}
}

void LaserPlayerTurret::fire()
{
	if (timer >= time_between_shots) {
		fire_time = 0;
		timer = 0;
	}
}

void LaserPlayerTurret::set_manager(GameObjectManager* manager)
{
	Turret::set_manager(manager);
}

void LaserPlayerTurret::init_sounds(SoundLoader* sl)
{
	Turret::init_sounds(sl);
	fire_sound_id = sl->loadSound("Laser sound.ogg", 25.0f);
}
