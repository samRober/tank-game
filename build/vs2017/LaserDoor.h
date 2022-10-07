#pragma once
#include "Enemy.h"
class LaserDoor :
    public Enemy
{
public:
    LaserDoor(float x, float y,float rotation, b2World& world, Player& player, ModelLoader& ml);
    void handle_collision(ObjectType other_type) override;
    
    void fire()override;
};

