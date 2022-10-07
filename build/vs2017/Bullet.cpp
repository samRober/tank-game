#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, CollisionGroups group, ModelLoader& ml, b2World& world):
	Projectile(x, y, group,world, ObjectType::bullet),
	smoke_emitter(x,y,world)
{
	set_mesh(ml.loadMeshFromFile("bullet.scn"));

	modelOffset_ = gef::Vector4(-0.1f, 1.f, 0);

	setup_body(angle, group);
	
	//set up emmiter
	smoke_emitter.set_mesh(ml.loadMeshFromFile("smoke.scn"));
	smoke_emitter.scale_ = 0.4f;
	smoke_emitter.modelOffset_.set_y(1.2f);
	smoke_emitter.direction_ = gef::Vector4(0, 0, 0);
	smoke_emitter.max_age_ = 0.2f;
	smoke_emitter.start_varience_ = 0.5f;
	smoke_emitter.target_varience_ = 1.0f;
	smoke_emitter.emission_rate_ = 0.05f;

	//join emitter to body
	auto smoke_emitter_body = smoke_emitter.get_body();
	b2DistanceJointDef smoke_emitter_def;
	smoke_emitter_def.Initialize(smoke_emitter_body, get_body(), smoke_emitter_body->GetWorldCenter(), get_body()->GetWorldPoint(b2Vec2(0.f, 1.6f)));
	world.CreateJoint(&smoke_emitter_def);
	//apply force
	const float bullet_speed = 12;
	Projectile::update(0.0f);
	gef::Vector2 dir = get_dir();
	body_->ApplyLinearImpulseToCenter(b2Vec2(-dir.x * bullet_speed, -dir.y * bullet_speed), true);

	
}

void Bullet::setup_body(float angle, CollisionGroups group)
{
	body_->SetBullet(true);
	body_->SetTransform(body_->GetPosition(), angle + 3.14159);

	b2PolygonShape bullet_shape;
	bullet_shape.SetAsBox(0.25f, 0.35f);


	b2FixtureDef bullet_fixture_def;
	bullet_fixture_def.shape = &bullet_shape;
	bullet_fixture_def.density = 1.5f;
	bullet_fixture_def.friction = 1.0f;
	bullet_fixture_def.restitution = 0.5f;
	bullet_fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::air);
	bullet_fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::air);
	bullet_fixture_def.filter.groupIndex = static_cast<int>(group);
	body_->CreateFixture(&bullet_fixture_def);
}

void Bullet::set_manager(GameObjectManager* manager)
{
	Projectile::set_manager(manager);
	smoke_emitter.set_manager(manager);
}

void Bullet::update(const float delta_time)
{
	Projectile::update(delta_time);
	smoke_emitter.update(delta_time);
}

void Bullet::init_sounds(SoundLoader* sl)
{
	Projectile::init_sounds(sl);
	hit_sound_id_ = sl->loadSound("Bullet_hit_sound.wav", 25.0f);
}

Bullet::~Bullet()
{
	//change the emitter
	smoke_emitter.target_varience_ = 5.0f;
	smoke_emitter.max_age_ = 0.5f;
	audio_manager_->PlaySample(hit_sound_id_);
	//emit 30 particles
	for (int i = 0; i < 30; i++)
	{
		smoke_emitter.emit();
	}

}


