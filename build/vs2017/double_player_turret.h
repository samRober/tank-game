#pragma once
#include "Turret.h"
#include "Bullet.h"
class Double_player_turret :
    public Turret
{
public:
    Double_player_turret(float x, float y, ModelLoader& ml, b2World& world);
    void setupBody();
    void update(const float delta_time)override;
    void fire()override;
    void set_manager(GameObjectManager* manager)override;
    void init_sounds(SoundLoader* sl)override;
private:

    float timer = 0;
    const float time_between_shots = 0.5;
    bool shoot_left;
    int fire_sound_id;
};

