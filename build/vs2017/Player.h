#pragma once
#include "GameObject.h"
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <Turret.h>
#include <Base_player_turret.h>
#include "double_player_turret.h"
#include "LaserPlayerTurret.h"
#include <Emitter.h>
class Player :
    public GameObject
{
    public:
    Player(float x, float y, ModelLoader& ml, b2World& world);

    ~Player();
    void update(const float delta_time)override;
    void handle_collision(ObjectType other_type)override;
    const std::vector<const GameObject*> get_meshs()const;
    void handle_input(gef::InputManager &in, const float delta_time);
    void switch_to_laser();
    void switch_to_basic_turret();
    void switch_to_double_barrel();
 	void set_manager(GameObjectManager* manager)override;
    void init_sounds(SoundLoader* sl)override;
    inline const int get_health()const { return health; };
    inline const bool is_double_turret_enabeld()const { return double_turret_enabeld_; };
    inline const bool is_laser_turret_enabeld() const { return laser_turret_enabeld_; };
    inline const bool is_rocket_turret_enabeld() const { return rocket_turret_enabeld_; };

    inline const bool has_won()const { return has_won_; };
private:
    void setup_body();
    float speed_ = 10000.f;
    float health = 10;
    float health_max = 10;
    Turret* current_turret_;
    Base_player_turret base_turret_;
    Double_player_turret double_turret_;
    LaserPlayerTurret laser_turret_;
    Emitter left_smoke_;
    Emitter right_smoke_;
    int engine_sound_id = NULL;
    bool double_turret_enabeld_ = false;
    bool laser_turret_enabeld_ = false;
    bool rocket_turret_enabeld_ = false;

    bool has_won_ = false;
};

 