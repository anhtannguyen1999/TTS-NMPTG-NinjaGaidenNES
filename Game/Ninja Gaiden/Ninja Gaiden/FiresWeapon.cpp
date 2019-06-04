#include "FiresWeapon.h"

//1 ngon lua
#pragma region Fire 
CFireWeapon::CFireWeapon(float vy)
{
	this->x = 30;
	this->y = 100;
	this->width = 35;
	this->height = 33;
	this->mana = 5;
	this->minitypeWeapon = WEAPON_MINITYPE_FIRE;
	//Load resource
	this->AddAnimation(331); //Animation 0
	this->vy = vy;
}

CFireWeapon::~CFireWeapon()
{
}

void CFireWeapon::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (active)
	{
		width = 25;
		height = 15;
		if (nx > 0)
			vx = 0.2f;
		else
			vx = -0.2f;
		//vy = 0.2f;
		if (this->y>=CAMERA_HEIGHT-SPACE_FROM_CAMERA_TO_TOP-20)
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

void CFireWeapon::Render()
{
	if (!active)
		return;
	timer++;
	if (timer >= 15)
		timer = 0;
	//CWeapon::Render();
	D3DXVECTOR3 pos;
	pos.x = this->x-5;
	pos.y = this->y+10;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	if (timer < 5)
	{
		animations[0]->Render(pos.x, pos.y, ALPHA);
		animations[0]->Render(pos.x + 12, pos.y + 15, ALPHA);
		animations[0]->Render(pos.x + 24, pos.y, ALPHA);
		
	}
	else if (timer < 10)
	{
		animations[0]->Render(pos.x+6, pos.y , ALPHA);
		animations[0]->Render(pos.x+24 , pos.y+8, ALPHA);
		animations[0]->Render(pos.x + 6, pos.y + 18, ALPHA);
	}
	else
	{
		animations[0]->Render(pos.x, pos.y + 15, ALPHA);
		animations[0]->Render(pos.x + 12, pos.y, ALPHA);
		animations[0]->Render(pos.x + 24, pos.y + 15, ALPHA);
	}
	//this->RenderBoundingBox(50);
}

void CFireWeapon::SetPosition(float x, float y, int nx)
{
	if (!this->active)//Neu chua ban ra thi moi duoc set
	{
		this->x = this->rootX = x;
		this->y = this->rootY = y;
		this->nx = nx;
	}
}

#pragma endregion




//Nhieu ngon lua
#pragma region FireS
CFiresWeapon * CFiresWeapon::__instance = NULL;
CFiresWeapon * CFiresWeapon::GetInstance()
{
	if (__instance == NULL)
		__instance = new CFiresWeapon();
	return __instance;
}
CFiresWeapon::CFiresWeapon()
{
	this->x = 30;
	this->y = 100;
	this->mana = 5;
	this->minitypeWeapon = WEAPON_MINITYPE_FIRES;
	listFires.push_back(new CFireWeapon(0.15f));
	listFires.push_back(new CFireWeapon(0.17f));
	listFires.push_back(new CFireWeapon(0.19f));
}

CFiresWeapon::~CFiresWeapon()
{
}

void CFiresWeapon::Update(DWORD dt)
{
	if (this->active == false)
		return;
	listFires[0]->Update(dt);
	listFires[1]->Update(dt);
	listFires[2]->Update(dt);
	if (!listFires[0]->GetActive() && !listFires[1]->GetActive() && !listFires[2]->GetActive())
		this->active = false;
}

void CFiresWeapon::Render()
{
	listFires[0]->Render();
	listFires[1]->Render();
	listFires[2]->Render();
}

void CFiresWeapon::SetPosition(float x, float y, int nx)
{
	if (!this->active)//Neu chua ban ra thi moi duoc set
	{
		listFires[0]->SetPosition(x,y,nx);
		listFires[1]->SetPosition(x, y+20, nx);
		listFires[2]->SetPosition(x, y+40, nx);
	}
}

void CFiresWeapon::SetActive(bool active)
{
	this->active = active;
	listFires[0]->SetActive(active);
	listFires[1]->SetActive(active);
	listFires[2]->SetActive(active);
}

#pragma endregion

