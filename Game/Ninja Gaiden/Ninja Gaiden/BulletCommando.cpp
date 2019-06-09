#include "BulletCommando.h"



CBulletCommando::CBulletCommando(int id, int x, int y, int nx)
{
	this->id = id;
	LoadResource();
	//this->typeEnemy = 0;
	this->x = x;
	this->y = y + 7;
	this->dame = 1;
	this->hp = 1;
	this->width = 12;
	this->height = 5;
	this->nx = nx;
	if (nx >= 1)
	{
		vx = 0.1f;
	}
	else
	{
		vx = -0.1f;
	}
	//vy = 0;
	//vx = -0.05f;
	//startX = this->x;
}


CBulletCommando::~CBulletCommando()
{
}

void CBulletCommando::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	/*if (daChamDat == 0)
	y += dy;*/

	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CBulletCommando::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(244);// right
	this->AddAnimation(245);//left
	animations = NULL;

}

void CBulletCommando::Render()
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
	//this->RenderBoundingBox();
}


void CBulletCommando::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (this->nx >0)
	{
		x = this->x + 5;
	}
	else x = this->x + 5;
	y = this->y - 15;
	width = this->width;
	height = this->height;
}

void CBulletCommando::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CBulletCommando::DeActivate()
{
	hp = 0;
}
