#pragma once
#include <Projectile.h>
class ProjectileManager
{
public:
	ProjectileManager();
	void update(const float delta_time);
	std::vector<const GameObject*> get_meshs();
	void add_projectile(std::unique_ptr<Projectile> new_projectile);

private:
	std::list<std::unique_ptr<Projectile>> projectiles_;
};

