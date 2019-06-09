#include "SmallShuriken.h"


CSmallShuriken * CSmallShuriken::__instance = NULL;

CSmallShuriken * CSmallShuriken::GetInstance()
{
	if (__instance == NULL)
		__instance = new CSmallShuriken();
	return __instance;
}

CSmallShuriken::CSmallShuriken()
{
	this->x = 0;
	this->y = 0;
	this->width = 10;
	this->height = 10;
	this->mana = 3;
	this->minitypeWeapon = WEAPON_MINITYPE_SMALL_SHURIKEN;
	//Load resource
	//CAnimations * animations = CAnimations::GetInstance();
	this->AddAnimation(329); //Animation 0

}


CSmallShuriken::~CSmallShuriken()
{
}


void CSmallShuriken::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	//y += dy;
	if (active)
	{
		width = 10;
		height = 10;
		if (nx > 0)
			vx = 0.3f;
		else
			vx = -0.3f;

		if (this->x - this->rootX > 130 || this->x - this->rootX < -130)
		{
			this->active = false;
		}
	}
	else
	{
		width = 0;
		height = 0;
	}
	
}

void CSmallShuriken::Render()
{
	if (!active)
		return;
	//CWeapon::Render();
	D3DXVECTOR3 pos;
	pos.x = this->x-4;
	pos.y = this->y+10;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[0]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox(20);
}

void CSmallShuriken::SetPosition(float x, float y, int nx)
{
	if (!this->active)//Neu chua ban ra thi moi duoc set
	{
		this->x = this->rootX = x;
		this->y = this->rootY = y;
		this->nx = nx;
	}
	
}

