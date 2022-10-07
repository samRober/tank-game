#include "BasicEnemyTurret.h"

BasicEnemyTurret::BasicEnemyTurret(float x, float y, ModelLoader& ml, b2World& world):
	Turret(x,y,ml,world,ObjectType::enemy)
{
	set_mesh(ml.loadMeshFromFile("enemy_gun_turret.scn"));
	body_->SetAngularDamping(5);
	body_->SetSleepingAllowed(false);

	turn_speed_ = turn_speed_ * 10;
	b2PolygonShape shape;
	shape.SetAsBox(1.2f, 1.05f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;
	fixture_def.friction = 1.0f;
	fixture_def.restitution = 0.5f;
	fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::air);
	fixture_def.filter.maskBits =static_cast<int>(CollisionLayers::air);
	fixture_def.filter.groupIndex = static_cast<int>(CollisionGroups::enemy);
	body_->CreateFixture(&fixture_def);

}

void BasicEnemyTurret::fire()
{
	audio_manager_->PlaySample(fire_sound_id);
	b2Vec2 pos = body_->GetPosition();
	gef::Vector2 offset = gef::Vector2(1.f, 0.7f);

	if (shoot_left_) {
		offset.x = -offset.x;
	}
	
	offset = offset.Rotate(body_->GetAngle());
	
	auto bullet = std::make_unique<Bullet>(pos.x + offset.x, pos.y + offset.y, body_->GetAngle(), CollisionGroups::enemy, ml_, world_);
	bullet->init_sounds(sl_);
	manager_->add_object(move(bullet));
	shoot_left_ = !shoot_left_;

}



void BasicEnemyTurret::init_sounds(SoundLoader* sl)
{
	Turret::init_sounds(sl);
	fire_sound_id = sl->loadSound("turret fire.ogg", 400.0f);
}
