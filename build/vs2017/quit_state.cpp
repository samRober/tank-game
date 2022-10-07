#include "quit_state.h"

quit_state::quit_state(std::unique_ptr<StateInformation> information):
    GameState(move(information))
{
}

bool quit_state::enter()
{
    return false;//return false from enter quits the game
}

void quit_state::handle_input(gef::InputManager& input, const float delta_time)
{
}

std::unique_ptr<GameState> quit_state::update(const float delta_time)
{
    return std::unique_ptr<GameState>();
}

void quit_state::render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
}
