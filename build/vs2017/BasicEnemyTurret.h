#pragma once
#include <Turret.h>
#include <Bullet.h>
#include <GameObjectManager.h>
class BasicEnemyTurret
	:public Turret
{
public:
	BasicEnemyTurret(float x, float y, ModelLoader& ml, b2World& world);
	void fire()override;
	void init_sounds(SoundLoader* sl)override;

private:
	bool shoot_left_ = true;
	int fire_sound_id;
};

