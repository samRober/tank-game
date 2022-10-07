#pragma once
#include "graphics/sprite.h"
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <string>
class Button :
    public gef::Sprite
{
public:
    Button();
    void set_selected(bool selected);
    
private:
};

