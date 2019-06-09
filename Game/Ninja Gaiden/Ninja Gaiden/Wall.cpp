#include "Wall.h"



CWall::CWall(int x, int y, int w, int h, int minitypeWall)
{
	//this->typeObj = TYPE_WALL;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->hp = 1;
	this->minitypeWall = minitypeWall;
}


CWall::~CWall()
{
}

void CWall::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CWall::Render()
{
	//this->RenderBoundingBox(180);
}

int CWall::GetMiniTypeWall()
{
	return this->minitypeWall;
}

int CWall::GetRightX() 
{
	return this->x + this->width;
}