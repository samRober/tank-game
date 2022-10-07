#pragma once 
#include <GameObject.h>
#include <Player.h>
#include <Particle.h>
class GameObjectManager
{
public:
	~GameObjectManager();
	void update(const float delta_time);
	std::vector<const GameObject*> get_meshs();
	std::vector<const MeshInstance*> get_particles();
	void add_object(std::unique_ptr<GameObject> new_object);
	void add_particle(std::unique_ptr<Particle> new_particle);
private:

	std::list<std::unique_ptr<GameObject>> scenery_;
	std::list<std::unique_ptr<Particle>> particles_;
	std::list<std::unique_ptr<GameObject>> objects_;
};

