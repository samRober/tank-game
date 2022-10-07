#include "MenuState.h"
#include <system/platform.h>


MenuState::MenuState(std::unique_ptr<StateInformation> information):
	GameState(move(information)),
	options(Options::instance())
{
}

bool MenuState::enter()
{
	info_->texture_loader_ = std::make_unique<TextureLoader>(info_->platform_);
	info_->audio_manager_.SetMasterVolume(options.volume_);
	info_->audio_manager_.LoadMusic("Ludum Dare 38 - Track 1.wav", info_->platform_);
	info_->audio_manager_.PlayMusic();
	gef::VolumeInfo music_vol;
	music_vol.volume = 8.0f;

	info_->audio_manager_.SetMusicVolumeInfo(music_vol);


	info_->font_ = std::make_unique<gef::Font>(info_->platform_);
	info_->font_->Load("1980");

	background_.set_position(gef::Vector4(info_->platform_.width()/2, info_->platform_.height()/2, 0));
	background_.set_height(info_->platform_.height());
	background_.set_width(info_->platform_.width());
	background_.set_texture(info_->texture_loader_->loadTexture("Splash_Screen.png"));

	button_1_.set_width(256);
	button_1_.set_height(68);
	button_1_.set_position(gef::Vector4(info_->platform_.width() / 2, info_->platform_.height() / 2, -1));
	button_1_.set_texture(info_->texture_loader_->loadTexture("Start_Button.png"));

	button_2_.set_width(256);
	button_2_.set_height(68);
	button_2_.set_position(gef::Vector4(info_->platform_.width() / 2, (info_->platform_.height() / 2) + button_2_.height() + 2, -1));
	button_2_.set_texture(info_->texture_loader_->loadTexture("Options_Button.png"));

	button_3_.set_width(256);
	button_3_.set_height(68);
	button_3_.set_position(gef::Vector4(info_->platform_.width() / 2, (info_->platform_.height() / 2) + (button_2_.height()  + 2) * 2, -1));
	button_3_.set_texture(info_->texture_loader_->loadTexture("Quit_button.png"));

	info_->texture_loader_->loadTexture("Empty_Button.png");
	info_->texture_loader_->loadTexture("Volume_Button.png");
	info_->texture_loader_->loadTexture("Back_Button.png");

	return true;
}

void MenuState::handle_input(gef::InputManager& input, const float delta_time)
{
	auto controller_manager = input.controller_input();
	if (controller_manager) {
		controller_manager->Update();
		auto controller = controller_manager->GetController(0);
		
		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS) {
			//basic menu
			if (!options_menu_) {
				switch (selection_)
				{

				case Button_selection::button_1:
					load_level = true;
					break;
				case Button_selection::button_2:
					toggle_options();
					break;
				case Button_selection::button_3:
					quit_ = true;
					break;
				default:
					break;
				}
			}
			//options
			else {
				switch (selection_)
				{
				case Button_selection::button_1:
					break;
				case Button_selection::button_2:
					break;
				case Button_selection::button_3:
					toggle_options();
					break;
				default:
					break;
				}
			}
		}
		if (controller->buttons_pressed() & gef_SONY_CTRL_DOWN) {
			next_selection();
		}
		if (controller->buttons_pressed() & gef_SONY_CTRL_UP) {
			previous_selection();
		}
		if (controller->buttons_pressed() & gef_SONY_CTRL_LEFT) {
			if (options_menu_) {
				switch (selection_)
				{
				case Button_selection::button_1://change volume
					options.volume_ -= 1;
					if (options.volume_ < 0) {
						options.volume_ = 10;
					}
					info_->audio_manager_.SetMasterVolume(options.volume_ * 5);
					break;
				case Button_selection::button_2://change difficulty
					if (options.difficulty_ == Difficulty::easy) {
						options.difficulty_ = Difficulty::hard;
					}
					else {
						int options_int = static_cast<int> (options.difficulty_);
						options.difficulty_ = static_cast<Difficulty>(--options_int);
					}
					break;
				default:
					break;
				}
			}
		}
		if (controller->buttons_pressed() & gef_SONY_CTRL_RIGHT) {
			if (options_menu_) {
				switch (selection_)
				{
				case Button_selection::button_1://change volume
					options.volume_ += 1;
					if (options.volume_ > 10) {
						options.volume_ = 0;
					}
					info_->audio_manager_.SetMasterVolume(options.volume_ * 5);

					break;
				case Button_selection::button_2://change difficulty
					if (options.difficulty_ == Difficulty::hard) {
						options.difficulty_ = Difficulty::easy;
					}
					else {
						int options_int = static_cast<int> (options.difficulty_);
						options.difficulty_ = static_cast<Difficulty>(++options_int);
					}
					break;
				default:
					break;
				}
			}
		}

	}
}

void MenuState::toggle_options()
{
	options_menu_ = !options_menu_;
	if (options_menu_ == true) {
		button_1_.set_texture(info_->texture_loader_->loadTexture("Volume_Button.png"));
		button_2_.set_texture(info_->texture_loader_->loadTexture("Empty_Button.png"));
		button_3_.set_texture(info_->texture_loader_->loadTexture("Back_Button.png"));
	}
	else {
		button_1_.set_texture(info_->texture_loader_->loadTexture("Start_Button.png"));
		button_2_.set_texture(info_->texture_loader_->loadTexture("Options_Button.png"));
		button_3_.set_texture(info_->texture_loader_->loadTexture("Quit_button.png"));
	}
}

void MenuState::previous_selection()
{
	if (selection_ == Button_selection::button_1) {
		selection_ = Button_selection::button_3;
	}
	else {
		int selec_int = static_cast<int> (selection_);
		selection_ = static_cast<Button_selection>(--selec_int);
	}
}

void MenuState::next_selection()
{
	if (selection_ == Button_selection::button_3) {
		selection_ = Button_selection::button_1;
	}
	else {
		int selec_int = static_cast<int> (selection_);
		selection_ = static_cast<Button_selection>(++selec_int);
	}
}

std::unique_ptr<GameState> MenuState::update(const float delta_time)
{
	if (load_level) {
		return std::make_unique<Level1LoadState>(move(info_));
	}
	if (quit_) {
		return std::make_unique<quit_state>(move(info_));
	}
	switch (selection_)
	{
		//chang button selection sprites
	case Button_selection::button_1:
		button_1_.set_selected(true);
		button_2_.set_selected(false);
		button_3_.set_selected(false);
		break;
	case Button_selection::button_2:
		button_1_.set_selected(false);
		button_2_.set_selected(true);
		button_3_.set_selected(false);
		break;
	case Button_selection::button_3:
		button_1_.set_selected(false);
		button_2_.set_selected(false);
		button_3_.set_selected(true);
		break;
	default:
		break;
	}

    return nullptr;
}

void MenuState::render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
	
	sprite_renderer.Begin();
	sprite_renderer.DrawSprite(background_);
	sprite_renderer.DrawSprite(button_1_);
	sprite_renderer.DrawSprite(button_2_);
	sprite_renderer.DrawSprite(button_3_);
	//title
	info_->font_->RenderText(&sprite_renderer, gef::Vector4(info_->platform_.width() / 2, 40, -1), 1.f, 0xffffffff, gef::TextJustification::TJ_CENTRE, "Tank Tops");
	//options menu
	if (options_menu_) {
		//volume
		auto vol_font_pos = button_1_.position();
		float vol_font_y_offset = 12;
		if (selection_ == Button_selection::button_1) {
			vol_font_y_offset += 8;
		}
		vol_font_pos.set_y(vol_font_pos.y() - button_1_.height()/2 + vol_font_y_offset);
		vol_font_pos.set_x(vol_font_pos.x() + button_1_.height() * 4 / 4 + 4);
		info_->font_->RenderText(&sprite_renderer, vol_font_pos, 0.5f, 0xffffffff, gef::TextJustification::TJ_CENTRE, std::to_string(options.volume_).c_str());
		//difficulty
		auto difficulty_pos = button_2_.position();
		float difficulty_y_offset = 12;
		if (selection_ == Button_selection::button_2) {
			difficulty_y_offset += 8;
		}
		difficulty_pos.set_y(difficulty_pos.y() - button_1_.height() / 2 + difficulty_y_offset);
		std::string difficulty_string;
		switch (options.difficulty_)
		{
		case Difficulty::easy:
			difficulty_string = "EASY";
			break;
		case Difficulty::medium:
			difficulty_string = "MEDIUM";
			break;
		case Difficulty::hard:
			difficulty_string = "HARD";
			break;
		default:
			break;
		}
		info_->font_->RenderText(&sprite_renderer, difficulty_pos, 0.5, 0xffffffff, gef::TextJustification::TJ_CENTRE, difficulty_string.c_str());
	}
	sprite_renderer.End();
}
