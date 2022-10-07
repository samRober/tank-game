#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <graphics/image_data.h>
#include <graphics/mesh.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <Level1LoadState.h>
#include <graphics/font.h>



SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(),
	renderer_3d_(),
	primitive_builder_(),
	in_(),
	state_machine_(),
	fps_(0),
	font(platform),
	options(Options::instance())
{
}

void SceneApp::Init()
{
	//input manager
	in_ = unique_ptr<gef::InputManager>(gef::InputManager::Create(platform_));
	//spriterendererererer
	sprite_renderer_ = unique_ptr<gef::SpriteRenderer>(gef::SpriteRenderer::Create(platform_));

	// create the renderer for draw 3D geometry
	renderer_3d_ = unique_ptr<gef::Renderer3D>(gef::Renderer3D::Create(platform_));
	//audio manager
	audio_manager_ = unique_ptr<gef::AudioManager>(gef::AudioManager::Create());
	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = std::make_unique<PrimitiveBuilder>(platform_);
	
	auto info = std::make_unique<StateInformation>(platform_, *audio_manager_);
	//set up state machine
	state_machine_ = std::make_unique<StateMachine>(new MenuState(move(info)));
	font.Load("comic_sans");
	
	SetupLights();
}

void SceneApp::CleanUp()
{


	 
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	
	HandleInput(frame_time);
	

	return state_machine_->update(frame_time);
}



void SceneApp::HandleInput(const float delta_time)
{
	state_machine_->handle_input(*in_, delta_time);
}

void SceneApp::Render()
{
	// setup camera

	state_machine_->render(*renderer_3d_, *sprite_renderer_);

	sprite_renderer_->Begin(false);
	//font.RenderText(sprite_renderer_.get(), gef::Vector4(0, 0, 0, 1), 1, 0xffffffff, gef::TextJustification::TJ_LEFT, std::to_string(fps_).c_str());//reads the fps in the top left corner of the sceen
	sprite_renderer_->End();
	// start drawing sprites, but don't clear the frame buffer

}


void SceneApp::SetupLights()
{
	
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.97f, 1.0f, 0.72f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}




