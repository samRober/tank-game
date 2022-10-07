#pragma once
#include "Enemy.h"
class Jeep :
    public Enemy
{
public:
    Jeep(float x,float y,b2World& world, Player& player, ModelLoader& ml);

    void update(const float delta_time) override;
    void fire()override;
private:

};

