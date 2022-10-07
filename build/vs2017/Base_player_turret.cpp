#include "Base_player_turret.h"
#include <GameObjectManager.h>

Base_player_turret::Base_player_turret(float x, float y, ModelLoader& ml, b2World& world):
Turret(x, y + 0.6f, ml, world,ObjectType::player),
barrel_smoke(x,y+1.6f + 0.6f,world),
barrel_fire(x, y + 1.6f + 0.6f,world)
{
	set_mesh(ml_.loadMeshFromFile("tank_turret.scn"));
	modelOffset_ = gef::Vector4(0,0.f,-0.6f);
	turn_speed_ = 350.f;
	//set up emitters
	barrel_smoke.set_mesh(ml.loadMeshFromFile("smoke.scn"));
	barrel_smoke.scale_ = 0.4f;
	barrel_smoke.modelOffset_.set_y(1.2f);
	barrel_smoke.direction_ = gef::Vector4(0,0,3.0f);
	barrel_smoke.max_age_ = 0.6f;
	barrel_smoke.start_varience_ = 0.f;
	barrel_smoke.target_varience_ = 3.0f;

	barrel_fire.set_mesh(ml.loadMeshFromFile("fire_cube.scn"));
	barrel_fire.scale_ = 0.4f;
	barrel_fire.modelOffset_.set_y(1.2f);
	barrel_fire.direction_ = gef::Vector4(0, 0, 1.5f);
	barrel_fire.max_age_ = 0.3f;
	barrel_fire.start_varience_ = 0.5f;
	barrel_fire.target_varience_ = 2.0f;

	setupBody();
	//join emitters
	auto barrel_fire_body = barrel_fire.get_body();
	b2DistanceJointDef barrel_fire_def;
	barrel_fire_def.Initialize(barrel_fire_body, get_body(), barrel_fire_body->GetWorldCenter(), get_body()->GetWorldPoint(b2Vec2(0.f, 1.6f)));
	world.CreateJoint(&barrel_fire_def);

	auto barrel_smoke_body = barrel_smoke.get_body();
	b2DistanceJointDef barrel_smoke_def;
	barrel_smoke_def.Initialize(barrel_smoke_body, get_body(), barrel_smoke_body->GetWorldCenter(), get_body()->GetWorldPoint(b2Vec2(0.f, 1.6f)));
	world.CreateJoint(&barrel_smoke_def);
}

void Base_player_turret::setupBody()
{
	body_->SetAngularDamping(4);
	body_->SetSleepingAllowed(false);

	b2PolygonShape shape;
	shape.SetAsBox(0.2f, 1.85f);


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



void Base_player_turret::update(const float delta_time)
{
	Turret::update(delta_time);
	gef::Vector2 target_dir = gef::Vector2(0.0f, 3.0f);
	target_dir = target_dir.Rotate(body_->GetAngle());
	barrel_smoke.direction_.set_x(target_dir.x);
	barrel_smoke.direction_.set_z(target_dir.y);
	barrel_smoke.update(0);
	target_dir = gef::Vector2(0.0f, 1.5f);
	target_dir = target_dir.Rotate(body_->GetAngle());
	barrel_fire.direction_.set_x(target_dir.x);
	barrel_fire.direction_.set_z(target_dir.y);
	barrel_fire.update(0);

	timer += delta_time;
}

void Base_player_turret::fire()
{
	
	if (timer >= time_between_shots) {
		//play sound
		if (audio_manager_) {
			audio_manager_->PlaySample(fire_sound_id);
		}
		//fire gun
		gef::Vector2 dir = get_dir();
		auto position = body_->GetPosition();
		position.x += dir.x * 1.5f;
		position.y += dir.y * 1.5f;
		auto bullet = std::make_unique<Bullet>(position.x, position.y, body_->GetAngle(), CollisionGroups::player, ml_, world_);
		bullet->modelOffset_.set_y(bullet->modelOffset_.y() * scale_);
		bullet->init_sounds(sl_);
		manager_->add_object(std::move(bullet));
		body_->ApplyLinearImpulseToCenter(b2Vec2(-dir.x * 75, -dir.y * 75), true);
		//emit particles
		for (int i = 0; i < 25; i++)
		{
			barrel_smoke.emit();
		}
		for (int i = 0; i < 5; i++)
		{
			barrel_fire.emit();
		}
		timer = 0;
	}	
}

void Base_player_turret::set_manager(GameObjectManager* manager)
{
	Turret::set_manager(manager);
	barrel_smoke.set_manager(manager);
	barrel_fire.set_manager(manager);

}

void Base_player_turret::init_sounds(SoundLoader* sl)
{
	Turret::init_sounds(sl);
	fire_sound_id = sl->loadSound("turret fire.ogg", 15.0f);
}
