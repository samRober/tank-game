#include "ProjectileManager.h"

void ProjectileManager::update(const float delta_time)
{
	for (auto i = projectiles_.begin(); i != projectiles_.end();) {
		std::unique_ptr<Projectile>& p = *i;
		p->update(delta_time);
		b2Body* p_body = p->get_body();
		if (!p_body->IsEnabled()) {
			p_body->GetWorld()->DestroyBody(p_body);
			i = projectiles_.erase(i);
		}
		else {
			i++;
		}
	}
}

std::vector<const GameObject*> ProjectileManager::get_meshs()
{
	auto out = std::vector<const GameObject*>();
	for (auto& i : projectiles_)
	{
		out.push_back(i.get());
	}

	return out;
}

void ProjectileManager::add_projectile(std::unique_ptr<Projectile> new_projectile)
{
	projectiles_.push_back(new_projectile);
}
