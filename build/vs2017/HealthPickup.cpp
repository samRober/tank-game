#include "HealthPickup.h"

HealthPickup::HealthPickup(float x, float y, b2World& world, ModelLoader& ml):
	Pickup(x,y,world,ObjectType::health_picup)
{
	mesh_ = ml.loadMeshFromFile("spanner.scn");
}

HealthPickup::~HealthPickup()
{
	audio_manager_->PlaySample(repair_sound_id);
}

void HealthPickup::init_sounds(SoundLoader* sl)
{
	Pickup::init_sounds(sl);
	repair_sound_id = sl->loadSound("Repair.ogg",100.0f);
}
