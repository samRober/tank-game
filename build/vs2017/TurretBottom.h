#pragma once
#include "Enemy.h"
#include <BasicEnemyTurret.h>


class TurretBottom :
    public Enemy
{
public:
    TurretBottom(float x, float y, b2World& world, Player& player, ModelLoader& ml, TurretType type);
    ~TurretBottom();
    void update(const float delta_time)override;
    virtual const std::vector<const GameObject*> get_meshs()const override;
    void fire()override;
    void set_manager(GameObjectManager* manager)override;
    void init_sounds(SoundLoader* sl)override;


private:
    std::unique_ptr<Turret> turret_;
    int death_sound_id_;
};

