#include "WinPickup.h"

WinPickup::WinPickup(float x, float y, b2World& world, ModelLoader& ml):
	Pickup(x,y,world,ObjectType::win_pickup)
{
	mesh_ = ml.loadMeshFromFile("flag.scn");
}
