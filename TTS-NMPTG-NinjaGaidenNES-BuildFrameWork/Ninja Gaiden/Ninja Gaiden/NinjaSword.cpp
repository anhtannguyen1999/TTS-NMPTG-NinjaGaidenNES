#include "NinjaSword.h"



CNinjaSword::CNinjaSword()
{
	width = 25;
	height = 15;	
}


CNinjaSword::~CNinjaSword()
{
}

void CNinjaSword::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CNinjaSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active)
	{
		width = 25;
		height = 15;
	}
	else
	{
		width = 0;
		height = 0;
	}
}

void CNinjaSword::Render()
{
	//this->RenderBoundingBox(180);
}
