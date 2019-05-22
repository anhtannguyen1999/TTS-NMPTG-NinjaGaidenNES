#include "Ground.h"

CGround::CGround(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->hp = 1;
}

CGround::~CGround()
{
}

void CGround::GetBoundingBox(float &x, float &y, float &width, float &height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CGround::Render()
{
	this->RenderBoundingBox(180);
}
