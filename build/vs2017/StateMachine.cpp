#include "StateMachine.h"

StateMachine::StateMachine(GameState* first_state) :
	current_state_(first_state)
{
	first_state->enter();
}

StateMachine::~StateMachine()
{

}

void StateMachine::handle_input(gef::InputManager &in, const float delta_time)
{
	current_state_->handle_input(in,delta_time);
}

bool StateMachine::update(const float delta_time)
{
	auto new_state = current_state_->update(delta_time);
	if (new_state != nullptr) {//change state
		current_state_ = move(new_state);
		return current_state_->enter();
	}
	return true;
}

void StateMachine::render(gef::Renderer3D &renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
	current_state_->render(renderer_3d, sprite_renderer);
}
