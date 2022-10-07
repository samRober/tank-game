#include "double_player_turret.h"
#include "GameObjectManager.h"
Double_player_turret::Double_player_turret(float x, float y, ModelLoader& ml, b2World& world):
	Turret(x,y,ml,world,ObjectType::player)
{
	set_mesh(ml.loadMeshFromFile("double_barrel.scn"));
	turn_speed_ = 375.f;
	modelOffset_ = gef::Vector4(0, 1, 0);
	setupBody();
}

void Double_player_turret::setupBody()
{
	body_->SetAngularDamping(4);
	body_->SetSleepingAllowed(false);

	b2PolygonShape shape;
	shape.SetAsBox(0.77f, 1.68f,b2Vec2(0.0f,0.4f),0);


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

void Double_player_turret::update(const float delta_time)
{
	Turret::update(delta_time);
	timer += delta_time;
}

void Double_player_turret::fire()
{
	if (timer >= time_between_shots) {
		//play sound
		if (audio_manager_) {
			audio_manager_->PlaySample(fire_sound_id);
		}
		gef::Vector2 offset;
		if (shoot_left) {
			offset = gef::Vector2(-0.42f, 1.26);
		}
		else {
			offset = gef::Vector2(0.42f, 1.26);
		}
		//fire gun

		offset =offset.Rotate(body_->GetAngle());
		auto position = body_->GetPosition();


		auto bullet = std::make_unique<Bullet>(position.x + offset.x, position.y + offset.y, body_->GetAngle(), CollisionGroups::player, ml_, world_);
		bullet->modelOffset_.set_y(bullet->modelOffset_.y() * scale_);
		bullet->init_sounds(sl_);
		manager_->add_object(std::move(bullet));
		body_->ApplyLinearImpulseToCenter(b2Vec2(-get_dir().x * 75, -get_dir().y * 75), true);

		shoot_left = !shoot_left;
		timer = 0;
	}
}

void Double_player_turret::set_manager(GameObjectManager* manager)
{
	Turret::set_manager(manager);
}

void Double_player_turret::init_sounds(SoundLoader* sl)
{
	Turret::init_sounds(sl);
	fire_sound_id = sl->loadSound("turret fire.ogg", 15.0f);
}
