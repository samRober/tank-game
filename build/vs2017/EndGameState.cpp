#include "EndGameState.h"

EndGameState::EndGameState(std::unique_ptr<StateInformation> information, bool has_won):
	GameState(move(information)),
	won(has_won)
{
}

bool EndGameState::enter()
{
	int sound_effect_id;
	if (!info_->texture_loader_) {
		info_->texture_loader_ = std::make_unique<TextureLoader>(info_->platform_);
	}
	if (!info_->sound_loader_) {
		info_->sound_loader_ = std::make_unique<SoundLoader>(info_->audio_manager_, info_->platform_);
	}
	if (won) {
		background_.set_texture(info_->texture_loader_->loadTexture("Win_Screen.png"));
		win_text_ = "You Win!!!";
		sound_effect_id = info_->sound_loader_->loadSound("win.wav",20.0f);
	}
	else {
		background_.set_texture(info_->texture_loader_->loadTexture("lose_Screen.png"));
		win_text_ = "You Lose";
		sound_effect_id = info_->sound_loader_->loadSound("lose.wav", 20.0f);

	}
	background_.set_position(gef::Vector4(info_->platform_.width() / 2, info_->platform_.height() / 2, 0));
	background_.set_height(info_->platform_.height());
	background_.set_width(info_->platform_.width());


	menu_button_.set_width(256);
	menu_button_.set_height(68);
	menu_button_.set_position(gef::Vector4(info_->platform_.width() / 2, info_->platform_.height() / 2, -1));
	menu_button_.set_texture(info_->texture_loader_->loadTexture("Menu_Button.png"));

	quit_button_.set_width(256);
	quit_button_.set_height(68);
	quit_button_.set_position(gef::Vector4(info_->platform_.width() / 2, (info_->platform_.height() / 2) + quit_button_.height() + 2, -1));
	quit_button_.set_texture(info_->texture_loader_->loadTexture("Quit_button.png"));

	info_->audio_manager_.StopMusic();
	info_->audio_manager_.PlaySample(sound_effect_id);

	return true;
}

void EndGameState::handle_input(gef::InputManager& input, const float delta_time)
{
	auto controller_manager = input.controller_input();
	if (controller_manager) {
		controller_manager->Update();
		auto controller = controller_manager->GetController(0);
		//activate selection
		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS) {
			switch (selection_)
			{
			case EndGameState::button_selection::menu:
				menu = true;
				break;
			case EndGameState::button_selection::quit:
				quit = true;
				break;
			default:
				break;
			}
		}
		// change selection
		if (controller->buttons_pressed() & gef_SONY_CTRL_UP) {
			if (selection_ == button_selection::menu) {
				selection_ = button_selection::quit;
			}
			else {
				selection_ = button_selection::menu;

			}
		}
		if (controller->buttons_pressed() & gef_SONY_CTRL_DOWN) {
			if (selection_ == button_selection::menu) {
				selection_ = button_selection::quit;
			}
			else {
				selection_ = button_selection::menu;

			}
		}

	}
}

std::unique_ptr<GameState> EndGameState::update(const float delta_time)
{
	switch (selection_)
	{
	case EndGameState::button_selection::menu:
		menu_button_.set_selected(true);
		quit_button_.set_selected(false);
		break;
	case EndGameState::button_selection::quit:
		menu_button_.set_selected(false);
		quit_button_.set_selected(true);
		break;
	default:
		break;
	}

	if (quit) {
		return std::make_unique<quit_state>(std::make_unique<StateInformation>(info_->platform_, info_->audio_manager_));
	}
	if (menu) {
		return std::make_unique<MenuState>(std::make_unique<StateInformation>(info_->platform_, info_->audio_manager_));
	}


	return nullptr;
}

void EndGameState::render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
	sprite_renderer.Begin();
	sprite_renderer.DrawSprite(background_);
	info_->font_->RenderText(&sprite_renderer, gef::Vector4(info_->platform_.width() / 2, 40, -1), 1.f, 0xffffffff, gef::TextJustification::TJ_CENTRE, win_text_.c_str());
	sprite_renderer.DrawSprite(quit_button_);
	sprite_renderer.DrawSprite(menu_button_);
	sprite_renderer.End();

}
