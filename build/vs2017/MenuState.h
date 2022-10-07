#pragma once
#include "GameState.h"
#include <Level1LoadState.h>
#include <graphics/sprite.h>
#include <Button.h>
#include <quit_state.h>
#include <Options.h>

class MenuState :
    public GameState
{
public:
	MenuState(std::unique_ptr<StateInformation> information);
	bool enter()override;
	void handle_input(gef::InputManager& input, const float delta_time)override;
	void toggle_options();
	std::unique_ptr<GameState> update(const float delta_time)override;
	void render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)override;
private:
	enum class Button_selection
	{
		button_1,
		button_2,
		button_3
	};

	bool load_level = false;
	gef::Sprite background_;
	Button button_1_;
	Button button_2_;
	Button button_3_;

	Button_selection selection_ = Button_selection::button_1;
	void next_selection();
	void previous_selection();
	bool quit_ = false;
	bool options_menu_ = false;
	Options& options;
};

