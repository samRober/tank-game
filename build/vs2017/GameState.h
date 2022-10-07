#pragma once
#include <input/input_manager.h>
#include <graphics/renderer_3d.h>
#include <graphics/sprite_renderer.h>
#include <GameObject.h>
#include <memory>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include "Player.h"
#include <GameObjectManager.h>
#include <graphics/font.h>
#include "TextureLoader.h"

struct StateInformation {
	StateInformation(gef::Platform& platform,gef::AudioManager& audio_manager):platform_(platform),audio_manager_(audio_manager) {};
	std::unique_ptr<Player> player_;
	std::unique_ptr<b2World> world_;
	std::unique_ptr<ModelLoader> model_loader_;
	std::unique_ptr<SoundLoader> sound_loader_;
	std::unique_ptr<TextureLoader> texture_loader_;
	std::unique_ptr<GameObjectManager> object_manager_;
	std::unique_ptr<gef::Font> font_;
	gef::Platform& platform_;
	gef::AudioManager& audio_manager_;
};

class GameState
{
public:
	GameState(std::unique_ptr<StateInformation> information);
	virtual bool enter() = 0;
	virtual void handle_input(gef::InputManager &input, const float delta_time) = 0;
	virtual std::unique_ptr<GameState> update(const float delta_time) = 0;
	virtual void render(gef::Renderer3D &renderer_3d,  gef::SpriteRenderer &sprite_renderer) = 0;
protected:
	void DrawObjects(std::vector<const GameObject*> objs, gef::Renderer3D& renderer_3d);
	void DrawObjects(std::vector<const gef::MeshInstance*> objs, gef::Renderer3D& renderer_3d);

	std::unique_ptr<StateInformation> info_;

};

