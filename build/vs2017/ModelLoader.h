#pragma once
#include <graphics/scene.h>
#include <map>
class ModelLoader
{
public:
	ModelLoader(gef::Platform &platform);
	~ModelLoader();
	gef::Mesh* loadMeshFromFile(const char* filename);
	gef::Material* getMaterial();
private:
	std::map<const char*,gef::Mesh*> mesh_map_;
	gef::Scene scene_;
	gef::Platform& platform_;

};

