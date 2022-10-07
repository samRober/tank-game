#pragma once
#include "pickup.h"
class WinPickup :
    public Pickup
{
public:
    WinPickup(float x, float y, b2World& world, ModelLoader& ml);
};

