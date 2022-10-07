#include <GameState.h>
#include <graphics/mesh.h>


GameState::GameState(std::unique_ptr<StateInformation> information):
	info_(move(information))
{
}



void GameState::DrawObjects(std::vector<const GameObject*> objs, gef::Renderer3D& renderer_3d)
{
	//render all objects given
	for (auto& i : objs)
	{
		if (i->get_enabled()) {
			renderer_3d.DrawMesh(*i);
		}
	}
}

void DrawObjects(std::vector<const gef::MeshInstance*> objs, gef::Renderer3D& renderer_3d) {
	//render all mesh instances given
	for (auto& i : objs)
	{
		renderer_3d.DrawMesh(*i);
	}
}
