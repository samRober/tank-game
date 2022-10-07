#pragma once
#include "GameObject.h"
class Projectile :
    public GameObject
{
    public:
    Projectile(float x, float y, CollisionGroups group, b2World& world, ObjectType type);
    virtual void handle_collision(ObjectType other_type) override;
};

