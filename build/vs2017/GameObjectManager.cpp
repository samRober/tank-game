#include "GameObjectManager.h"


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::update(const float delta_time)
{
	//update objects
	for (auto i = objects_.begin(); i != objects_.end();)
	{
		auto& o = *i;
		if (o->get_is_alive()) {
			o->update(delta_time);

			i++;
		}
		else {//destroy object if dead
			o->get_body()->GetWorld()->DestroyBody(o->get_body());

			i = objects_.erase(i);
		}
	}
	//update particles
	for (auto i = particles_.begin(); i != particles_.end();)
	{
		auto& o = *i;
		if (o->is_alive()) {
			o->update(delta_time);

			i++;
		}
		else {//delete particle if dead
			i = particles_.erase(i);
		}
	}
}

std::vector<const GameObject*> GameObjectManager::get_meshs()
{
	std::vector<const GameObject*> out;
	for (auto& i : objects_)
	{
		auto meshs = i->get_meshs();
		out.insert(out.end(), meshs.begin(),meshs.end());
	}
	for (auto& i : scenery_)
	{
		out.push_back(i.get());
	}
	return out;
}

std::vector<const MeshInstance*> GameObjectManager::get_particles()
{
	std::vector<const MeshInstance*> out;
	for (auto& i : particles_)
	{
		out.push_back(i.get());
	}
	return out;
}

void GameObjectManager::add_object(std::unique_ptr<GameObject> new_object)
{
	
	if (new_object->get_type() == ObjectType::scenery) {//scenery should not be updated every frame
		new_object->update(1.0f);
		scenery_.push_back(move(new_object));
	}
	else {
		new_object->set_manager(this);
		if (new_object->get_type() == ObjectType::bullet) {
			objects_.push_front(move(new_object));
		}
		else {
			objects_.push_back(move(new_object));
		}
	}
}

void GameObjectManager::add_particle(std::unique_ptr<Particle> new_particle)
{
	particles_.push_back(move(new_particle));
}


