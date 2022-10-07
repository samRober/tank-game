#include "ModelLoader.h"
#include <system/debug_log.h>
#include <graphics/mesh.h>


ModelLoader::ModelLoader(gef::Platform& platform):
platform_(platform)
{
}

ModelLoader::~ModelLoader()
{
}

gef::Mesh* ModelLoader::loadMeshFromFile(const char* filename)
{
	auto map_model = mesh_map_.find(filename);
	if (map_model != mesh_map_.end()) {
		return map_model->second;
	}
	else {

		gef::Mesh* mesh = NULL;
		if (scene_.ReadSceneFromFile(platform_, filename)) {
			mesh = scene_.CreateMesh(platform_, scene_.mesh_data.back());
			if(scene_.materials.empty()){
				scene_.CreateMaterials(platform_);
			}
			mesh->GetPrimitive(0)->set_material(getMaterial());
		}
		else {
			gef::DebugOut("Scene file %s failed to load\n", filename);
			return NULL;
		}
		mesh_map_.insert({filename,mesh});
		return mesh;
		
	}
}

gef::Material* ModelLoader::getMaterial()
{
	
	return scene_.materials.back();
}
