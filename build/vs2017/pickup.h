#pragma once
#include "GameObject.h"
class Pickup :
    public GameObject
{
public:
    Pickup(float x, float y, b2World& world, ObjectType type);
    virtual void handle_collision(ObjectType other_type)override;

};

