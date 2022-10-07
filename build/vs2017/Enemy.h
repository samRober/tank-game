#pragma once
#include "GameObject.h"
#include <Projectile.h>
#include <Player.h>
#include <Options.h>
class Enemy :
    public GameObject
{
public:
    Enemy(float x, float y, b2World& world, Player& player, ModelLoader& ml, float shot_timer);
    virtual ~Enemy();
    virtual void update(const float delta_time)override;
    virtual void handle_collision(ObjectType other_type) override;
    virtual void init_sounds(SoundLoader* sl)override;
protected:
    virtual void fire() = 0;
    void shot_timer_tick(float delta_time);
    ModelLoader& ml_;
    b2World& world_;
    Player& player_;
    bool laser_hit_;
    float health_;

private:
    float shot_timer;
    const float shot_timer_reset;
    int death_sound_id_;
};

