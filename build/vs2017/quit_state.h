#pragma once
#include "GameState.h"
class quit_state :
    public GameState
{
public:
	quit_state(std::unique_ptr<StateInformation> information);
	virtual bool enter();
	virtual void handle_input(gef::InputManager& input, const float delta_time);
	virtual std::unique_ptr<GameState> update(const float delta_time);
	virtual void render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer);
};

