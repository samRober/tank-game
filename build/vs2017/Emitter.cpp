#include "Emitter.h"
#include <GameObjectManager.h>

Emitter::Emitter(float x,float y, b2World& world):
	direction_(gef::Vector4(0,1,0)),
	max_age_(1.0f),
	emission_rate_(1.0f),
	start_varience_(1.0f),
	target_varience_(1.0f),
	scale_change_(0.0f),
	GameObject(x,y,world,ObjectType::prop),
	timer_(0)
{// float emission_rate = 1.0f,float start_variance = 1.0f, float target_varience = 1, float end_scale = 0 
	b2PolygonShape shape;
	shape.SetAsBox(0.01, 0.01);

	b2FixtureDef fix_def;
	fix_def.density = 0.01f;
	fix_def.shape = &shape;
	fix_def.filter.categoryBits = 0;
	fix_def.filter.maskBits = 0;
	get_body()->CreateFixture(&fix_def);

}

void Emitter::update(const float delta_time)
{
	GameObject::update(delta_time);


	timer_ += delta_time;
	int remainder = timer_ / emission_rate_;//remainter is the number of particles to be emitted
	while(remainder >= 1) {
		emit();
		timer_ -= emission_rate_;
		remainder = timer_ / emission_rate_;
	}
}

void Emitter::emit()
{
	//make new particle
	auto particle = std::make_unique<Particle>(max_age_);
	particle->set_mesh(mesh());
	gef::Transform start_transform;
	start_transform.Set(transform());
	auto start_translation = start_transform.translation();
	//set starting translation to be random based on start_variance varible
	float x_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / start_varience_)) - start_varience_ / 2;
	float y_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / start_varience_)) - start_varience_ / 2;
	float z_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / start_varience_)) - start_varience_ / 2;
	//set start matrix of variable
	start_translation = gef::Vector4(start_translation.x() + x_var, start_translation.y() + y_var, start_translation.z() + z_var);
	start_transform.set_translation(start_translation);
	particle->set_start_transform(start_transform.GetMatrix());

	gef::Transform end_transform;
	end_transform.Set(transform());
	auto end_translation = end_transform.translation();
	//randomise the translation of the end matrix of the particle based on target_varience
	x_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / target_varience_)) - target_varience_ / 2;
	y_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / target_varience_)) - target_varience_ / 2;
	z_var = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / target_varience_)) - target_varience_ / 2;
	//move end translation based on the direction vector
	end_translation += gef::Vector4(direction_.x() + x_var, direction_.y() + y_var, direction_.z() + z_var);
	end_transform.set_translation(end_translation);
	//set scale
	end_transform.set_scale(gef::Vector4(scale_change_, scale_change_, scale_change_));
	//set end transform
	particle->set_end_transform(end_transform.GetMatrix());
	manager_->add_particle(move(particle));
}
