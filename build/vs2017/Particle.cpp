#include "Particle.h"

Particle::Particle(float max_age) :
	age_(0),
	max_age_(max_age),
	is_alive_(true)
{
}

void Particle::update(const float delta_time)
{

	gef::Transform current_transform;
	current_transform.Linear2TransformBlend(start_transform_, end_transform_, age_/max_age_);//lerp from start to end matrix

	set_transform(current_transform.GetMatrix());
	age_ += delta_time;
	if (age_ > max_age_) {//die
		is_alive_ = false;
	}
}
