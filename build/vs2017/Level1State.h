#pragma once
#include "GameState.h"
#include <Player.h>
#include <GameObjectManager.h>
#include <SoundLoader.h>
#include <memory>
#include <EndGameState.h>

using std::unique_ptr;


class Level1State :
    public GameState
{
public:
    Level1State(std::unique_ptr<StateInformation> information);
    bool enter()override;
    void handle_input(gef::InputManager& input, const float delta_time)override;
    std::unique_ptr<GameState> update(const float delta_time)override;
    void render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)override;
private:
    gef::Sprite health_icon_;
    gef::Sprite buttons_;
    gef::Sprite basic_turret_icon_;
    gef::Sprite rocket_turret_icon_;
    gef::Sprite double_turret_icon_;
    gef::Sprite laser_turret_icon_;

    void handle_collisions();
    bool reset_ = false;

};

