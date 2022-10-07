#include "TextureLoader.h"

TextureLoader::TextureLoader(gef::Platform& platform):
	platform_(platform)
{
}

TextureLoader::~TextureLoader()
{
	for (auto& i : texture_map)
	{
		delete i.second;
	}
}

gef::Texture* TextureLoader::loadTexture(const char* file_name)
{
	auto map_texture = texture_map.find(file_name);
	if (map_texture != texture_map.end()) {
		return map_texture->second;
	}
	else {
		gef::PNGLoader loader;
		gef::ImageData image_data;
		loader.Load(file_name, platform_, image_data);
		auto texture = gef::Texture::Create(platform_, image_data);
		texture_map.insert({ file_name,texture });
		return texture;
	}

}
