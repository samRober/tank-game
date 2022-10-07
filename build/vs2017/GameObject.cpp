#include "GameObject.h"
#include <GameObjectManager.h>




GameObject::GameObject(float x, float y, b2World& world, ObjectType type):
type_(type),
manager_(NULL)
{
	b2BodyDef def;
	def.type = b2BodyType::b2_dynamicBody;
	def.position = b2Vec2(x, y);
	def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body_ = world.CreateBody(&def);
}

GameObject::~GameObject()
{

}

void GameObject::update(float delta_time)
{
	update_model();

}

void GameObject::handle_collision(ObjectType other_type)
{
}

const std::vector<const GameObject*> GameObject::get_meshs() const
{
	std::vector<const GameObject*> out ={this};
	return out;
}

void GameObject::set_manager(GameObjectManager* manager)
{
	manager_ = manager;
}

void GameObject::init_sounds(SoundLoader* sl)
{
	audio_manager_ = &sl->get_audio_manager();
}



void GameObject::update_model()
{
	if (body_)
	{
		if (body_->IsEnabled()) {
			is_enabled_ = true;
			// setup object rotation
			gef::Matrix44 object_rotation;
			object_rotation.RotationY(-body_->GetAngle());
			dir_ = gef::Vector2(0, 1);
			dir_ = dir_.Rotate(body_->GetAngle());
			dir_.Normalise();

			// setup the object translation
			gef::Vector2 tmp(modelOffset_.x(), modelOffset_.z());
			tmp = tmp.Rotate(body_->GetAngle());
			
			gef::Vector4 object_translation(body_->GetPosition().x + tmp.x, 0.0f + modelOffset_.y(), body_->GetPosition().y + tmp.y);

			// build object transformation matrix
			gef::Matrix44 object_transform = object_rotation;
			gef::Matrix44 object_scale;
			gef::Vector4 scale = { scale_,scale_,scale_ ,1.0f };
			object_scale.Scale(scale);
			object_transform = object_transform * object_scale;
			object_transform.SetTranslation(object_translation);
			set_transform(object_transform);
		}
		else {
			is_enabled_ = false;
		}
	}
}
