#pragma once
#include "Turret.h"
#include <Bullet.h>
#include <Emitter.h>
class Base_player_turret :
    public Turret
{
public:
    Base_player_turret(float x, float y, ModelLoader& ml, b2World& world);
    void setupBody();
    void update(const float delta_time)override;
    void fire()override;
    void set_manager(GameObjectManager* manager)override; 
    void init_sounds(SoundLoader* sl)override;
private:
    Emitter barrel_smoke;
    Emitter barrel_fire;
    float timer = 0;
    const float time_between_shots = 1;
    int fire_sound_id;

};

