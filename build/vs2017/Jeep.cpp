#include "Jeep.h"
#include <GameObjectManager.h>

Jeep::Jeep(float x, float y, b2World& world, Player& player, ModelLoader& ml):
	Enemy(x,y,world,player, ml,1.0f)
{
	set_mesh(ml.loadMeshFromFile("jeep.scn"));

	//set up body
	body_->SetLinearDamping(5);
	body_->SetAngularDamping(5);
	body_->SetSleepingAllowed(false);


	b2PolygonShape shape;
	shape.SetAsBox(1.05f, 1.4f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;
	fixture_def.friction = 1.0f;
	fixture_def.restitution = 0.5f;
	fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	fixture_def.filter.groupIndex = static_cast<int>(CollisionGroups::enemy);
	body_->CreateFixture(&fixture_def);
}

void Jeep::update(const float delta_time)
{
	body_->ApplyTorque(10,true);//TODO add ai
	Enemy::update(delta_time);
}

void Jeep::fire()
{
	auto position = body_->GetPosition();
	auto bullet = std::make_unique<Bullet>(position.x, position.y, body_->GetAngle(), CollisionGroups::enemy, ml_, world_);
	bullet->modelOffset_.set_y(1.9f);
	manager_->add_object(move(bullet));
}


