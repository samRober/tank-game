#pragma once
#include "pickup.h"
class LaserTurretPickup :
    public Pickup
{
public:
    LaserTurretPickup(float x, float y, b2World& world, ModelLoader& m);
    ~LaserTurretPickup();
    void init_sounds(SoundLoader* sl);
private:
    int sound_id_;
};

