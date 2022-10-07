#pragma once
#include "pickup.h"
class Double_turret_pickup :
    public Pickup
{
public:
    Double_turret_pickup(float x, float y, b2World& world, ModelLoader& ml);
    ~Double_turret_pickup();
    void init_sounds(SoundLoader* sl)override;
private:
    int sound_id_;
};

