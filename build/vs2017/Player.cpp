#include "Player.h"
#include <Options.h>

Player::Player(float x, float y, ModelLoader& ml, b2World& world):
GameObject(x,y,world,ObjectType::player),
base_turret_(x,y,ml,world),
double_turret_(x,y,ml,world),
laser_turret_(x,y,ml,world),
current_turret_(&base_turret_),
left_smoke_(x + 0.5f, y - 1.6f, world),
right_smoke_(x - 0.35f, y - 1.6f, world)
{
	scale_ = 1.4f;
	base_turret_.scale_ = scale_;
	double_turret_.scale_ = scale_;
	laser_turret_.scale_ = scale_;
	
	set_mesh(ml.loadMeshFromFile("tank_body.scn"));
	setup_body();
	//set up emitters
	base_turret_.set_up_joint(*body_);
	double_turret_.set_up_joint(*body_);
	laser_turret_.set_up_joint(*body_);
	left_smoke_.set_mesh(ml.loadMeshFromFile("smoke.scn"));
	left_smoke_.scale_ = 0.3f;
	left_smoke_.modelOffset_.set_y(1.2f);
	left_smoke_.direction_ = gef::Vector4(0, 1.5f, 0);
	left_smoke_.max_age_ = 1.2f;
	left_smoke_.emission_rate_ = 0.1f;
	left_smoke_.start_varience_ = 0.1f;
	left_smoke_.target_varience_ = 0.5f;

	//join left emitter
	auto left_body = left_smoke_.get_body();
	b2DistanceJointDef left_joint_def;
	left_joint_def.Initialize(left_body, get_body(), left_body->GetWorldCenter(), get_body()->GetWorldPoint(b2Vec2(0.5f,-1.6f)));
	world.CreateJoint(&left_joint_def);

	right_smoke_.set_mesh(ml.loadMeshFromFile("smoke.scn"));
	right_smoke_.scale_ = 0.3f;
	right_smoke_.modelOffset_.set_y(1.2f);
	right_smoke_.direction_ = gef::Vector4(0, 1.5f, 0);
	right_smoke_.max_age_ = 1.2f;
	right_smoke_.emission_rate_ = 0.1f;
	right_smoke_.start_varience_ = 0.1f;
	right_smoke_.target_varience_ = 0.5f;
	//join right emitter
	auto right_body = right_smoke_.get_body();
	b2DistanceJointDef right_joint_def;
	right_joint_def.Initialize(right_body, get_body(), right_body->GetWorldCenter(), get_body()->GetWorldPoint(b2Vec2(-0.35f, -1.6f)));
	world.CreateJoint(&right_joint_def);

	Options& options = Options::instance();
	//hp based on difficulty
	switch (options.difficulty_)
	{
	case Difficulty::easy:
		health = 20;
		health_max = 20;
		break;
	case Difficulty::medium:
		health = 10;
		health_max = 10;
		break;
	case Difficulty::hard:
		health = 5;
		health = 5;
		break;
	default:
		break;
	}
	double_turret_.get_body()->SetEnabled(false);


}


Player::~Player()
{

}

void Player::update(const float delta_time)
{
	GameObject::update(delta_time);
	current_turret_->update(delta_time);
	right_smoke_.update(delta_time);
	left_smoke_.update(delta_time);
	if (current_turret_->hit_) {//if turret hit then body should be hit
		handle_collision(ObjectType::bullet);
		current_turret_->hit_ = false;
	}

}

void Player::handle_collision(ObjectType other_type)
{
	switch (other_type)
	{

	case ObjectType::bullet:
		health -= 1.0f;
		if (health <= 0) {
			is_alive_ = false;
		}
		break;
	case ObjectType::laser_beam:
		health -= 0.1f;
		if (health <= 0) {
			is_alive_ = false;
		}
		break;

	case ObjectType::health_picup:
		health = health_max;
		break;
	case ObjectType::double_turret_pickup:
		double_turret_enabeld_ = true;
		switch_to_double_barrel();
		break;
	case ObjectType::laser_turret_pickup:
		laser_turret_enabeld_ = true;
		switch_to_laser();
		break;
	case ObjectType::win_pickup:
		has_won_ = true;
		break;
	default:
		break;
	}
	
}

const std::vector<const GameObject*> Player::get_meshs() const
{
	std::vector<const GameObject*> out = {this,current_turret_ };
	return out;
}

void Player::handle_input(gef::InputManager& in, const float delta_time)
{
	auto controller_manager = in.controller_input();
	if (controller_manager) {
		controller_manager->Update();
		auto controller = controller_manager->GetController(0);
		b2Vec2 left_stick(controller->left_stick_x_axis(), -controller->left_stick_y_axis());
		gef::Vector2 right_stick(-controller->right_stick_x_axis(), -controller->right_stick_y_axis());

		gef::Vector2 dir = get_dir();
		b2Vec2 forward = b2Vec2(dir.x, dir.y);
		forward *= left_stick.y * speed_ * scale_ * delta_time;
		float turn = left_stick.x * speed_/3.0f * scale_ * delta_time;

		//move forward and turn
		body_->ApplyForceToCenter(forward, true);
		body_->ApplyTorque(turn, true);

		//aim turret
		current_turret_->target(right_stick, delta_time);

		auto buttons = controller->buttons_down();
		//fire
		if (buttons & gef_SONY_CTRL_R1) {
			current_turret_->fire();
		}
		//enable double turret
		if (controller->buttons_pressed() & gef_SONY_CTRL_TRIANGLE && double_turret_enabeld_) {
			switch_to_double_barrel();
		}
		//enable basic turret
		if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS) {
			switch_to_basic_turret();
		}
		//enable laser turret
		if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE && laser_turret_enabeld_) {
			switch_to_laser();
		}
		
	}
}

void Player::switch_to_laser()
{
	auto current_turret_body = current_turret_->get_body();
	current_turret_body->SetEnabled(false);
	laser_turret_.get_body()->SetTransform(current_turret_body->GetPosition(), current_turret_body->GetAngle());
	current_turret_ = &laser_turret_;
	laser_turret_.get_body()->SetEnabled(true);
}

void Player::switch_to_basic_turret()
{
	auto current_turret_body = current_turret_->get_body();
	current_turret_body->SetEnabled(false);
	base_turret_.get_body()->SetTransform(current_turret_body->GetPosition(), current_turret_body->GetAngle());
	current_turret_ = &base_turret_;
	base_turret_.get_body()->SetEnabled(true);
}

void Player::switch_to_double_barrel()
{
	auto current_turret_body = current_turret_->get_body();
	current_turret_body->SetEnabled(false);
	double_turret_.get_body()->SetTransform(current_turret_body->GetPosition(), current_turret_body->GetAngle());
	current_turret_ = &double_turret_;
	double_turret_.get_body()->SetEnabled(true);
}

void Player::set_manager(GameObjectManager* manager)
{
	manager_ = manager;
	base_turret_.set_manager(manager);
	double_turret_.set_manager(manager);
	laser_turret_.set_manager(manager);
	left_smoke_.set_manager(manager);
	right_smoke_.set_manager(manager);
}

void Player::init_sounds(SoundLoader* sl)
{
	GameObject::init_sounds(sl);
	base_turret_.init_sounds(sl);
	double_turret_.init_sounds(sl);
	laser_turret_.init_sounds(sl);
	engine_sound_id = sl->loadSound("Tank_Engine_running.wav", 5.5f);
	if (audio_manager_) {
		audio_manager_->PlaySample(engine_sound_id, true);

	}
}


void Player::setup_body()
{
	//player box2d body

	body_->SetLinearDamping(5);
	body_->SetAngularDamping(5);
	body_->SetSleepingAllowed(false);


	b2PolygonShape shape;
	shape.SetAsBox(0.95f * scale_, 1.15f * scale_);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1.0f;
	fixture_def.friction = 1.0f;
	fixture_def.restitution = 0.5f;
	fixture_def.filter.categoryBits = static_cast<int>( CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	fixture_def.filter.groupIndex = static_cast<int>(CollisionGroups::player);
	body_->CreateFixture(&fixture_def);
}