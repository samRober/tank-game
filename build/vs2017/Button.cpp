#include "Button.h"



Button::Button()
{
	uv_width_ = 0.5f;
}

void Button::set_selected(bool selected)
{
	if (selected) {//change uv to right half of texture
		uv_position_ = gef::Vector2(0.5f, 0.0f);
	}
	else {
		uv_position_ = gef::Vector2(0.0f, 0.0f);
	}
}




