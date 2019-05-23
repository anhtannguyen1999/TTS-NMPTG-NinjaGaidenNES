#include "Cross.h"
#include "Ninja.h"


Cross::Cross(int id, int x, int y, int nx)
{
	this->id = id;
	LoadResource();
	//this->typeEnemy = 0;
	this->x = x;
	this->y = y + 7;
	this->dame = 1;
	this->hp = 1;
	this->width = 12;
	this->height = 10;
	this->nx = nx;
	vy = 0.5f;
	if (nx >= 1)
	{
		vx = 0.2f;
	}
	else
	{
		vx = -0.2f;
	}
	//vy = 0;
	//vx = -0.05f;
	//startX = this->x;
}


Cross::~Cross()
{
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	

	if (vy >= -0.5f&& timer % 3 == 0)
	{
		vy = vy - 0.1f;
	}
	timer++;
	/*if (daChamDat == 0)
	y += dy;*/
	y += dy;
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void Cross::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(216);// right
	this->AddAnimation(217);//left
	animations = NULL;

}

void Cross::Render()
{
	int ani;
	if (nx > 0)
		ani = 0; //right
	else
		ani = 1;//left
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox();
}


void Cross::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (this->nx >= 1)
	{
		x = this->x - 5;
	}
	else x = this->x + 5;
	y = this->y - 11;
	width = this->width;
	height = this->height;
}

void Cross::BeAttack(int satThuong)
{
	hp = 0;
	Cross::~Cross();
}
