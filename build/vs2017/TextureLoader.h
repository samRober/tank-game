#pragma once
#include "graphics/texture.h"
#include "assets/png_loader.h"
#include "graphics/image_data.h"
#include <map>
class TextureLoader
{
public:
	TextureLoader(gef::Platform& platform);
	~TextureLoader();
	gef::Texture* loadTexture(const char* fileName);

private:
	std::map<const char*, gef::Texture*> texture_map;
	gef::Platform& platform_;
};

