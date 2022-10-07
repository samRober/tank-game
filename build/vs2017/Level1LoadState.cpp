#include "Level1LoadState.h"
#include <system/platform.h>
#include <chrono>
#include <sstream>
#include <maths/math_utils.h>

using namespace std::chrono_literals;




Level1LoadState::Level1LoadState(std::unique_ptr<StateInformation> information):
	GameState(move(information))
{
}


bool Level1LoadState::enter()
{
	info_->audio_manager_.StopMusic();
	auto func = [&]() {
		return loadLevel();
	};
	//set off new thread to load level
	new_level_ = std::async(std::launch::async, func);

	info_->audio_manager_.LoadMusic("Ludum Dare 30 - Track 7.wav", info_->platform_);

	return true;
}

void Level1LoadState::handle_input(gef::InputManager& input, const float delta_time)
{
}

std::unique_ptr<GameState> Level1LoadState::update(const float delta_time)
{
	auto tmp = new_level_.wait_for(0s);
	if (tmp == std::future_status::ready)
	{
		auto new_info = new_level_.get();
		new_info->font_ = move(info_->font_);
		return std::make_unique<Level1State>(move(new_info));
	}
	else{
		return nullptr;
	}
}

void Level1LoadState::render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
	sprite_renderer.Begin();
	info_->font_->RenderText(&sprite_renderer, gef::Vector4(0, 0, 0, 1), 1, 0xffffffff, gef::TextJustification::TJ_LEFT, "Loading");
	sprite_renderer.End();
}

std::unique_ptr<StateInformation> Level1LoadState::loadLevel()
{
	b2Vec2 gravity(0.0f, 0.0f);
	//set up new information for new level

	auto new_info = std::make_unique<StateInformation>( info_->platform_ ,info_->audio_manager_);
	new_info->model_loader_ = std::make_unique<ModelLoader>(info_->platform_);
	new_info->world_ = std::make_unique<b2World>(gravity);
	new_info->object_manager_ = std::make_unique<GameObjectManager>();
	new_info->sound_loader_ = std::make_unique<SoundLoader>(info_->audio_manager_, info_->platform_);
	new_info->texture_loader_ = std::make_unique<TextureLoader>(info_->platform_);
	new_info->texture_loader_->loadTexture("Tank_Health.png");

	//set up basic map grid
	std::ifstream file_map;
	file_map.open("Tank_Game_map.txt");
	int y = 0;
	int x = 0;
	srand(2);

	for (std::string s; std::getline(file_map, s); y++) {
		x = 0;
		for (auto& i : s)
		{
			if (i == 'p') {
				new_info->object_manager_->add_object(PropMaker::addTile(x * 4 , y * 4 , *new_info->model_loader_,  *new_info->world_, 'd'));



				new_info->player_ = std::make_unique<Player>(x * 4 , y * 4 , *new_info->model_loader_, *new_info->world_);


			}
			else {
				new_info->object_manager_->add_object(PropMaker::addTile(x * 4 , y * 4 , *new_info->model_loader_, *new_info->world_, i));

				if (i == 'd') {
					if (rand() % 100 < 25) {
						int y_plus = rand() % 2;
						int x_plus = rand() % 2;
						new_info->object_manager_->add_object(PropMaker::addGrass(x * 4 + x_plus, y * 4 + y_plus, *new_info->model_loader_, *new_info->world_));

					}
				}
			}
			x++;

		}
	}
	file_map.close();

	//set up props (enemies crates trees etc)
	std::ifstream file_props;
	file_props.open("props.txt");
	srand(2);
	for (std::string s; std::getline(file_props, s);) {
		std::stringstream ss = std::stringstream(s);
		std::string type;
		ss >> type;
		if (type == "#") {
			continue;
		}
		float x_pos;
		ss >> x_pos;
		float y_pos;
		ss >> y_pos;
		float rot;
		ss >> rot;
		rot = gef::DegToRad(rot);
		
		if (type == "tree") {
			TreeType tree_type = static_cast<TreeType>(rand() % 3);
			new_info->object_manager_->add_object(PropMaker::addTree(x_pos, y_pos, *new_info->model_loader_, *new_info->world_, tree_type));
		}
		if (type == "crate") {
			new_info->object_manager_->add_object(PropMaker::addCrate(x_pos, y_pos, *new_info->model_loader_, *new_info->world_));
		}
		if (type == "fence") {
			new_info->object_manager_->add_object(PropMaker::addFence(x_pos, y_pos, rot, *new_info->model_loader_, *new_info->world_));
		}
		if (type == "fence_corner") {
			new_info->object_manager_->add_object(PropMaker::addFenceCorner(x_pos, y_pos, rot, *new_info->model_loader_, *new_info->world_));

		}
		if (type == "bridge") {
			new_info->object_manager_->add_object(PropMaker::addBridge(x_pos, y_pos, rot, *new_info->model_loader_, *new_info->world_));

		}
		if (type == "turret") {
			auto turret = std::make_unique<TurretBottom>(x_pos, y_pos, *new_info->world_, *new_info->player_, *new_info->model_loader_, TurretType::basic);
			turret->init_sounds(new_info->sound_loader_.get());
			new_info->object_manager_->add_object(move(turret));
		}
		if (type == "tent") {
			new_info->object_manager_->add_object(PropMaker::addTent(x_pos, y_pos, rot, *new_info->model_loader_, *new_info->world_));

		}
		if (type == "hanger") {
			new_info->object_manager_->add_object(PropMaker::addHanger(x_pos, y_pos, rot, *new_info->model_loader_, *new_info->world_));

		}
		if (type == "health") {
			auto health = std::make_unique<HealthPickup>(x_pos, y_pos, *new_info->world_, *new_info->model_loader_);
			health->init_sounds(new_info->sound_loader_.get());
			new_info->object_manager_->add_object(move(health));
		}
		if (type == "double_barrel") {
			auto pickup = std::make_unique<Double_turret_pickup>(x_pos, y_pos, *new_info->world_, *new_info->model_loader_);
			pickup->init_sounds(new_info->sound_loader_.get());
			new_info->object_manager_->add_object(move(pickup));
		}
		if (type == "laser") {
			auto pickup = std::make_unique<LaserTurretPickup>(x_pos, y_pos, *new_info->world_, *new_info->model_loader_);
			pickup->init_sounds(new_info->sound_loader_.get());
			new_info->object_manager_->add_object(move(pickup));
		}
		if (type == "goal") {
			auto pickup = std::make_unique<WinPickup>(x_pos, y_pos, *new_info->world_, *new_info->model_loader_);

			new_info->object_manager_->add_object(move(pickup));
		}
		if (type == "door") {
			auto door = std::make_unique<LaserDoor>(x_pos, y_pos,rot, *new_info->world_, *new_info->player_, *new_info->model_loader_);
			door->init_sounds(new_info->sound_loader_.get());
			new_info->object_manager_->add_object(move(door));
		}
	}


	new_info->player_->init_sounds(new_info->sound_loader_.get());
	new_info->player_->set_manager(new_info->object_manager_.get());
	return move(new_info);
}
