#pragma once
#include <GameState.h>
#include <memory>
class StateMachine
{
public:
	StateMachine(GameState *first_state);
	~StateMachine();
	void handle_input(gef::InputManager& in, const float delta_time);
	bool update(const float delta_time);
	void render(gef::Renderer3D &renderer_3d, gef::SpriteRenderer& sprite_renderer);
private:
	std::unique_ptr<GameState> current_state_;

};

