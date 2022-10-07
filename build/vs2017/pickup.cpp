#include "pickup.h"

Pickup::Pickup(float x, float y, b2World& world, ObjectType type):
	GameObject(x,y,world,type)
{

	b2CircleShape shape;
	shape.m_radius = 1;

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.isSensor = true;
	fixture_def.density = 1.0f;

	body_->CreateFixture(&fixture_def);
	body_->ApplyTorque(200, true);
}

void Pickup::handle_collision(ObjectType other_type)
{
	if (other_type == ObjectType::player) {
		is_alive_ = false;
	}
}
