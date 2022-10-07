#pragma once
#include "Turret.h" 
#include "particle.h"
#include "LaserRaycastCallback.h"
class LaserPlayerTurret:
	public Turret
{
public:
	LaserPlayerTurret(float x, float y, ModelLoader& ml, b2World& world);
	void update(const float delta_time)override;
	void fire()override;
	void set_manager(GameObjectManager* manager)override;
	void init_sounds(SoundLoader* sl)override;
private:
	float fire_time = 3.f;
	const float max_fire_time = 2.5f;
	float timer = 0;
	const float time_between_shots = 5.0f;
	int fire_sound_id;
};

