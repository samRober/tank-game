#pragma once
#include "GameObject.h"
#include <Particle.h>
class Emitter:
	public GameObject
{
public:
	Emitter(float x, float y, b2World& world );
	void update(const float delta_time)override;
	void emit();
	gef::Vector4 direction_;
	float emission_rate_;
	float start_varience_;
	float target_varience_;
	float scale_change_;
	float max_age_;
private:
	float timer_;

};

