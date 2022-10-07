#include "LaserDoor.h"

LaserDoor::LaserDoor(float x, float y, float rotation, b2World& world, Player& player, ModelLoader& ml):
	Enemy(x,y,world,player,ml,0)
{
	mesh_ = ml.loadMeshFromFile("laser door.scn");
	body_->SetTransform(body_->GetPosition(), rotation);

	b2PolygonShape shape;
	shape.SetAsBox(0.4f, 2.0f);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	body_->CreateFixture(&fixture_def);
}

void LaserDoor::handle_collision(ObjectType other_type)
{
	//only take damage from lasers
	if (other_type == ObjectType::laser_beam) {
		laser_hit_ = true;
	}
	if (health_ <= 0) {
		is_alive_ = false;
	}
}

void LaserDoor::fire()
{
}
