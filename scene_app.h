#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <GameObject.h>
#include <graphics/scene.h>
#include <graphics/texture.h>
#include <box2d/box2d.h>
#include <maths/matrix44.h>
#include <ModelLoader.h>
#include <Player.h>
#include <StateMachine.h>
#include <Level1State.h>
#include <MenuState.h>
#include <graphics/font.h>


// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();

	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:

	void SetupLights();
	void HandleInput(const float delta_time);



    
	unique_ptr<gef::SpriteRenderer> sprite_renderer_;

	unique_ptr <gef::Renderer3D> renderer_3d_;

	unique_ptr<PrimitiveBuilder> primitive_builder_;

	unique_ptr<gef::AudioManager> audio_manager_;
	
	gef::Font font;


	float fps_;

	unique_ptr<gef::InputManager> in_;

	unique_ptr<StateMachine> state_machine_;

	Options options;
};

#endif // _SCENE_APP_H
