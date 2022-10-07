#pragma once
#include "Projectile.h"
#include <Emitter.h>
class Bullet :
    public Projectile
{
public:
    Bullet(float x, float y, float angle, CollisionGroups group, ModelLoader& ml, b2World& world);
    void setup_body(float angle, CollisionGroups group);
    void set_manager(GameObjectManager* manager)override;
    void update(const float delta_time)override;
    void init_sounds(SoundLoader* sl)override;
    ~Bullet();
private:
    Emitter smoke_emitter;
    int hit_sound_id_;
};

