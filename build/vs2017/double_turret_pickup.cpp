
#include "double_turret_pickup.h"

Double_turret_pickup::Double_turret_pickup(float x, float y, b2World& world, ModelLoader& ml):
	Pickup(x,y,world,ObjectType::double_turret_pickup)
{
	mesh_ = ml.loadMeshFromFile("double_barrel.scn");
}

Double_turret_pickup::~Double_turret_pickup()
{
	audio_manager_->PlaySample(sound_id_);
}

void Double_turret_pickup::init_sounds(SoundLoader* sl)
{
	Pickup::init_sounds(sl);
	sound_id_ = sl->loadSound("Repair.ogg", 100.0f);
}
