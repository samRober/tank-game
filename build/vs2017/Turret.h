#pragma once
#include "GameObject.h"
#include <Projectile.h>
enum class TurretType
{
    basic
};

class Turret :
    public GameObject
{
public:
    Turret(float x, float y, ModelLoader& ml, b2World& world, ObjectType type);
    ~Turret();
    void set_up_joint(b2Body& joined_body);
    const std::vector<const GameObject*> get_meshs()const;
    virtual void update(const float delta_time);
    virtual void fire() = 0;
    virtual void target(gef::Vector2& target_dir, const float delta_time);
    virtual void init_sounds(SoundLoader* sl)override;
    void handle_collision(ObjectType other_type)override;
    bool hit_ = false;
    bool laser_hit_ = false;
protected:
    b2World& world_;
    ModelLoader& ml_;
    SoundLoader* sl_;
    float turn_speed_ = 80.f;
};

