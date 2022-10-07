
#pragma once
#include "GameState.h"
#include "Level1State.h"
#include <graphics/font.h>
#include <PropMaker.h>
#include <Jeep.h>
#include <TurretBottom.h>
#include <thread>
#include <future>
#include <fstream>
#include <system/debug_log.h>
#include "HealthPickup.h"
#include "double_turret_pickup.h"
#include "LaserTurretPickup.h"
#include "LaserDoor.h"
#include "WinPickup.h"
class Level1LoadState :
    public GameState
{
public:
    Level1LoadState(std::unique_ptr<StateInformation> information);

    bool enter()override;
    void handle_input(gef::InputManager& input, const float delta_time)override;
    std::unique_ptr<GameState> update(const float delta_time)override;
    void render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)override;
private:
    std::unique_ptr<StateInformation> loadLevel();

    std::future<std::unique_ptr<StateInformation>> new_level_;
};

