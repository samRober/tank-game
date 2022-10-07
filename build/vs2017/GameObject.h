#pragma once
#include "graphics/mesh_instance.h"
#include <box2d/Box2D.h>
#include <maths/vector2.h>
#include <ModelLoader.h>
#include <vector>
#include <SoundLoader.h>

//forward declaration
class GameObjectManager;

enum class ObjectType {
	player,
	enemy,
	bullet,
	laser_beam,
	prop,
	scenery,
	health_picup,
	double_turret_pickup,
	laser_turret_pickup,
	win_pickup
};
enum class CollisionGroups {
	player = -1,
	enemy = -2
};
enum class CollisionLayers {
	ground = 0x0001,
	air = 0x0002
};

class GameObject :
    public gef::MeshInstance
{
public:

	GameObject(float x, float y,b2World& world, ObjectType type);
	virtual ~GameObject();
	virtual void update(const float delta_time);
	virtual void handle_collision(ObjectType other_type);
	virtual const std::vector<const GameObject*> get_meshs()const;
	inline const bool get_enabled() const {return is_enabled_;}
	inline b2Body* get_body() const {return body_;}
	inline const ObjectType get_type() const {return type_;}
	inline const bool get_is_alive()const { return is_alive_; }
	inline const gef::Vector2 get_dir()const { return dir_; }
	virtual void set_manager(GameObjectManager* manager);
	virtual void init_sounds(SoundLoader* sl);

	gef::Vector4 modelOffset_ ={0,0,0};
	float scale_ = 1.0f;
protected:
	ObjectType type_;
	b2Body* body_ = nullptr;
	GameObjectManager* manager_;
	bool is_alive_ = true;
	gef::AudioManager* audio_manager_ = nullptr;
private:
	void update_model();
	bool is_enabled_ = true;
	gef::Vector2 dir_ = { 1,0 };


};

