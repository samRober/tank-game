#pragma once
#include "pickup.h"
class HealthPickup :
    public Pickup
{
public:
    HealthPickup(float x, float y, b2World& world, ModelLoader& ml);
    ~HealthPickup();
    void init_sounds(SoundLoader* sl)override;
private:
    int repair_sound_id;
};

