#include "Level1State.h"
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <system/platform.h>





Level1State::Level1State(std::unique_ptr<StateInformation> information):
	GameState(move(information))
{
}


bool Level1State::enter()
{
	//set up icons
	health_icon_.set_height(76);
	health_icon_.set_width(128);
	health_icon_.set_position(gef::Vector4(info_->platform_.width() / 2, 35, -10));
	health_icon_.set_texture(info_->texture_loader_->loadTexture("Tank_Health.png"));

	buttons_.set_height(40);
	buttons_.set_width(188);
	buttons_.set_position(gef::Vector4(info_->platform_.width() / 2, info_->platform_.height() - 35, -10));
	buttons_.set_texture(info_->texture_loader_->loadTexture("Buttons.png"));

	basic_turret_icon_.set_height(50);
	basic_turret_icon_.set_width(26);
	basic_turret_icon_.set_position(gef::Vector4(info_->platform_.width() / 2 - 75, info_->platform_.height() - 85, -10));
	basic_turret_icon_.set_texture(info_->texture_loader_->loadTexture("Single_Barrel icon.png"));

	double_turret_icon_.set_height(50);
	double_turret_icon_.set_width(26);
	double_turret_icon_.set_position(gef::Vector4(info_->platform_.width() / 2 + 25, info_->platform_.height() - 85, -10));
	double_turret_icon_.set_texture(info_->texture_loader_->loadTexture("Double Barrel icon.png"));

	laser_turret_icon_.set_height(64);
	laser_turret_icon_.set_width(24);
	laser_turret_icon_.set_position(gef::Vector4(info_->platform_.width() / 2 - 25, info_->platform_.height() - 95, -10));
	laser_turret_icon_.set_texture(info_->texture_loader_->loadTexture("Laser Icon.png"));

	rocket_turret_icon_.set_height(64);
	rocket_turret_icon_.set_width(34);
	rocket_turret_icon_.set_position(gef::Vector4(info_->platform_.width() / 2 + 75 , info_->platform_.height() - 85, -10));
	rocket_turret_icon_.set_texture(info_->texture_loader_->loadTexture("Rocket Icon.png"));
	//play music
	info_->audio_manager_.PlayMusic();
	return true;
}

void Level1State::handle_input(gef::InputManager& input, const float delta_time )
{
	info_->player_->handle_input(input, delta_time);
	/*auto controller_manager = input.controller_input();// resets the level for design purposes
	if (controller_manager) {
		auto controller = controller_manager->GetController(0);

		if (controller->buttons_pressed() & gef_SONY_CTRL_L3) {
			reset_ = true;
		}
	}*/
}

std::unique_ptr<GameState> Level1State::update(const float delta_time)
{
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	//box2d simulation
	info_->world_->Step(timeStep, velocityIterations, positionIterations);

	//update models

	info_->player_->update(delta_time);
	info_->object_manager_->update(delta_time);
	//collision
	handle_collisions();
	/*//reset for design purposes
	if (reset_) {
		auto new_info = std::make_unique<StateInformation>(info_->platform_, info_->audio_manager_);
		new_info->font_ = move(info_->font_);
		return std::make_unique<Level1LoadState>(move(new_info));
	}*/
	if (info_->player_->has_won()) {//go to win screen
		auto new_info = std::make_unique<StateInformation>(info_->platform_, info_->audio_manager_);
		new_info->font_ = move(info_->font_);
		return std::make_unique<EndGameState>(move(new_info), true);
	}

	if (info_->player_->get_is_alive()) {//if still alive do nothing
		return nullptr;
	}
	else {//dead go to lose screen
		auto new_info = std::make_unique<StateInformation>(info_->platform_, info_->audio_manager_);
		new_info->font_ = move(info_->font_);
		return std::make_unique<EndGameState>(move(new_info),false);
	}


}

void Level1State::render(gef::Renderer3D& renderer_3d, gef::SpriteRenderer& sprite_renderer)
{
	// setup camera

// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)info_->platform_.width() / (float)info_->platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = info_->platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d.set_projection_matrix(projection_matrix);

	// view
	gef::Vector2 player_dir = info_->player_->get_dir();
	gef::Vector4 camera_eye(info_->player_->get_body()->GetPosition().x + 0.1f, 25.0f, info_->player_->get_body()->GetPosition().y - 5.0f);
	gef::Vector4 camera_lookat(info_->player_->get_body()->GetPosition().x, 1.0f, info_->player_->get_body()->GetPosition().y);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d.set_view_matrix(view_matrix);


	// draw 3d geometry
	renderer_3d.Begin();
	DrawObjects(info_->player_->get_meshs(), renderer_3d);
	DrawObjects(info_->object_manager_->get_meshs(), renderer_3d);
	auto x = info_->object_manager_->get_particles();
	for (auto& i : x)
	{
		renderer_3d.DrawMesh(*i);
	}
	renderer_3d.End();
	//ui rendering
	sprite_renderer.Begin(false);
	/*// display coordinates for level design purposes
	auto pos = info_->player_->get_body()->GetPosition();

	info_->font_->RenderText(&sprite_renderer,gef::Vector4(info_->platform_.width()/2,100, -111),0.5f,0xffffffff,gef::TextJustification::TJ_RIGHT,std::to_string((int)pos.x).c_str());
	info_->font_->RenderText(&sprite_renderer, gef::Vector4(info_->platform_.width() / 2 , 100, -111), 0.5f, 0xffffffff, gef::TextJustification::TJ_LEFT, std::to_string((int)pos.y).c_str());
	*/
	//draw helath and health icon
	sprite_renderer.DrawSprite(health_icon_);
	int player_health = info_->player_->get_health();
	auto player_health_string = std::to_string(player_health);

	info_->font_->RenderText(&sprite_renderer, gef::Vector4(info_->platform_.width() / 2 - 10, 33, -111), 0.5f, 0xffffffff, gef::TextJustification::TJ_CENTRE, player_health_string.c_str());
	//draw buttons at bottom of screen
	sprite_renderer.DrawSprite(buttons_);
	sprite_renderer.DrawSprite(basic_turret_icon_);
	if (info_->player_->is_rocket_turret_enabeld()) {
		sprite_renderer.DrawSprite(rocket_turret_icon_);
	}
	if (info_->player_->is_double_turret_enabeld()) {
		sprite_renderer.DrawSprite(double_turret_icon_);
	}
	if (info_->player_->is_laser_turret_enabeld()) {
		sprite_renderer.DrawSprite(laser_turret_icon_);
	}

	sprite_renderer.End();
}

void Level1State::handle_collisions()
{
	b2Contact* contact = info_->world_->GetContactList();
	for (int contact_num = 0; contact_num < info_->world_->GetContactCount(); contact_num++)
	{
		if (contact->IsTouching())
		{
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
			GameObject* objectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
			GameObject* objectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);
			objectA->handle_collision(objectB->get_type());
			objectB->handle_collision(objectA->get_type());

		}

		// Get next contact point
		contact = contact->GetNext();
	}
}
