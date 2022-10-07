#include "LaserTurretPickup.h"

LaserTurretPickup::LaserTurretPickup(float x, float y, b2World& world, ModelLoader& ml):
	Pickup(x,y,world,ObjectType::laser_turret_pickup)
{
	mesh_ = ml.loadMeshFromFile("laser_barrel.scn");
}

LaserTurretPickup::~LaserTurretPickup()
{
	audio_manager_->PlaySample(sound_id_);
}

void LaserTurretPickup::init_sounds(SoundLoader* sl)
{
	Pickup::init_sounds(sl);
	sound_id_ = sl->loadSound("Repair.ogg", 100.0f);
}
