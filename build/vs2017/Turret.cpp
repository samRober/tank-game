#include "Turret.h"



Turret::Turret(float x, float y, ModelLoader& ml, b2World& world, ObjectType type):
world_(world),
ml_(ml),
GameObject(x, y, world, type)
{
}

Turret::~Turret()
{
	
}

void Turret::set_up_joint(b2Body& joined_body)
{
	b2RevoluteJointDef joint_def;
	joint_def.Initialize(&joined_body, body_, joined_body.GetWorldCenter());
	world_.CreateJoint(&joint_def);
}

const std::vector<const GameObject*> Turret::get_meshs() const
{
	std::vector<const GameObject*> out = {this};

	return out;
}

void Turret::update(const float delta_time)
{
	GameObject::update(delta_time);
	
}

void Turret::fire()
{
}

void Turret::target(gef::Vector2& target_dir, const float delta_time)
{
	if (target_dir.x != 0 || target_dir.y != 0) {
		target_dir.Normalise();
		float angle_to_move = 0;
		if (target_dir.x < 0) {
			float dot = target_dir.DotProduct(gef::Vector2(0, 1));
			float angle = acosf(dot);
			angle_to_move = body_->GetAngle() - angle;
		}
		else {
			float dot = target_dir.DotProduct(gef::Vector2(0, -1));
			float angle = acosf(dot);
			angle_to_move = body_->GetAngle() - angle;
			angle_to_move += 3.14159;
		}
		while (angle_to_move > 3.14159) {
			angle_to_move -= 3.14159 * 2;
		}
		while (angle_to_move < -3.14159) {
			angle_to_move += 3.14159 * 2;
		}
		body_->ApplyTorque(-angle_to_move * turn_speed_ * delta_time, true);
	}
}

void Turret::init_sounds(SoundLoader* sl)
{
	GameObject::init_sounds(sl);
	sl_ = sl;
}

void Turret::handle_collision(ObjectType other_type)
{
	if (other_type == ObjectType::bullet ) {
		hit_ = true;
	}
	if (other_type == ObjectType::laser_beam) {
		laser_hit_ = true;
	}
}
