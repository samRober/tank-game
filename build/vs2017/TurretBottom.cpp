#include "TurretBottom.h"

TurretBottom::TurretBottom(float x, float y, b2World& world, Player& player, ModelLoader& ml, TurretType type):
	Enemy(x,y,world,player,ml,1.0f)
{
	set_mesh(ml.loadMeshFromFile("enemy_turret_base.scn"));
	switch (type)
	{
	case TurretType::basic:
		turret_ = std::make_unique<BasicEnemyTurret>(x, y, ml, world);
		break;
	default:
		break;
	}
	turret_->set_up_joint(*body_);
	turret_->set_manager(manager_);
}

TurretBottom::~TurretBottom()
{
	turret_->get_body()->GetWorld()->DestroyBody(turret_->get_body());
	audio_manager_->PlaySample(death_sound_id_);
}

void TurretBottom::update(const float delta_time)
{
	Enemy::update(delta_time);
	b2Vec2 player_pos = player_.get_body()->GetPosition();
	b2Vec2 turret_pos = body_->GetPosition();
	gef::Vector2 target_vector{ player_pos.x - turret_pos.x, player_pos.y - turret_pos.y };
	turret_->update(delta_time);

	// if player nearby then shoot
	if (target_vector.Length() < 15) {

		shot_timer_tick(delta_time);
	}
	if (turret_->hit_) {// if turret has been hit the the bottom should be hit
		
		handle_collision(ObjectType::bullet);
		turret_->hit_ = false;
	}
	if (turret_->laser_hit_) {//same as above but for the laser
		handle_collision(ObjectType::laser_beam);
		turret_->laser_hit_ = false;
	}
	target_vector.Normalise();
	turret_->target(target_vector, delta_time);//target player

}

const std::vector<const GameObject*> TurretBottom::get_meshs() const
{
	std::vector<const GameObject*> out{ this,turret_.get() };
	return out;
}



void TurretBottom::fire()
{
	turret_->fire();
}

void TurretBottom::set_manager(GameObjectManager* manager)
{
	turret_->set_manager(manager);
}

void TurretBottom::init_sounds(SoundLoader* sl)
{
	Enemy::init_sounds(sl);
	turret_->init_sounds(sl);
	death_sound_id_ = sl->loadSound("Enemy death.ogg",25.0f);
}

