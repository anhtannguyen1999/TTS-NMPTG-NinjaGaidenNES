#include "Ground.h"

CGround::CGround(int x, int y, int w, int h,int minitypeGround)
{
	//this->typeObj = TYPE_GROUND;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->hp = 1;
	this->minitypeGround = minitypeGround;
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
	//this->RenderBoundingBox(180);
}

int CGround::GetMiniTypeGround()
{
	return this->minitypeGround;
}
