#include "Projectile.h"

Projectile::Projectile(float x, float y, CollisionGroups group, b2World& world, ObjectType type):
GameObject(x, y, world, type)
{
}



void Projectile::handle_collision(ObjectType other_type)
{
	//if collision then get destroyed
	is_alive_ = false;
}
