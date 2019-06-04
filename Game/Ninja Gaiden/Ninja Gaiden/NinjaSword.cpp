#include "NinjaSword.h"


CNinjaSword * CNinjaSword::__instance = NULL;

CNinjaSword * CNinjaSword::GetInstance()
{
	if (__instance == NULL)
		__instance = new CNinjaSword();
	return __instance;
}

CNinjaSword::CNinjaSword()
{
	this->x = 0;
	this->y = 0;
	this->width = 22;
	this->height = 12;
	this->minitypeWeapon = WEAPON_MINITYPE_SWORD;
	//Load resource
	//CAnimations * animations = CAnimations::GetInstance();
	
	
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
		width = 22;
		height = 12;

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
	
	//CWeapon::Render();

	
}

