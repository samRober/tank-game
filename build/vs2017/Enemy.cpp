#include "Enemy.h"

Enemy::Enemy(float x, float y, b2World& world, Player& player, ModelLoader& ml, float shot_timer):
GameObject(x,y,world,ObjectType::enemy),
player_(player),
shot_timer_reset(shot_timer),
shot_timer(shot_timer),
world_(world),
ml_(ml)
{
	//set health based on difficulty
	Options& options = Options::instance();
	switch (options.difficulty_)
	{
	case Difficulty::easy:
		health_ = 1;
		break;
	case Difficulty::medium:
		health_ = 1;
		break;
	case Difficulty::hard:
		health_ = 2;
		break;
	default:
		break;
	}
}

Enemy::~Enemy()
{
	
	audio_manager_->PlaySample(death_sound_id_);
	GameObject::~GameObject();
}

void Enemy::update(const float delta_time)
{
	GameObject::update(delta_time);
	if (laser_hit_) {// if hit by laser
		health_ -= 1.1f * delta_time;
		laser_hit_ = false;
	}
}

void Enemy::handle_collision(ObjectType other_type)
{
	if (other_type == ObjectType::bullet) {
		health_-= 1.0f;
	}
	if (other_type == ObjectType::laser_beam) {
		laser_hit_ = true;
	}
	if (health_ <= 0) {//dead
		is_alive_ = false;
	}
}

void Enemy::init_sounds(SoundLoader* sl)
{
	GameObject::init_sounds(sl);
	death_sound_id_ = sl->loadSound("Enemy death.ogg", 3.0f);
}

void Enemy::shot_timer_tick(float delta_time)
{
	shot_timer -= delta_time;
	if (shot_timer < 0) {
		fire();
		shot_timer = shot_timer_reset;
	}
}
