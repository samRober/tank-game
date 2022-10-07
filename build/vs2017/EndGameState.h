#pragma once
#include"GameState.h"
#include <Button.h>
#include <system/platform.h>
#include <quit_state.h>
#include <MenuState.h>
class EndGameState :
    public GameState
{
public:
	EndGameState(std::unique_ptr<StateInformation> information,bool has_won);
	bool enter() override;
	void handle_input(gef::InputManager& input, const float delta_time) override;
	std::unique_ptr<GameState> update(const float delta_time) override;
	void render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer) override;
private:
	enum class button_selection
	{
		menu,
		quit
	};
	button_selection selection_ = button_selection::menu;
	Button quit_button_;
	Button menu_button_;
	gef::Sprite background_;
	std::string win_text_;
	bool won;
	bool menu = false;
	bool quit = false;

};

