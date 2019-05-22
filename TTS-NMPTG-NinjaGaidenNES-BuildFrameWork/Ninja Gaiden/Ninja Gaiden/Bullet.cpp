#include "Bullet.h"



Bullet::Bullet(int id, int x, int y,int nx)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = 0;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 25;
	this->height = 34;
	this->nx = nx;
	vy = 0;
	vx = -0.05f;
	startX = this->x;
}


Bullet::~Bullet()
{
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	/*if (daChamDat == 0)
		y += dy;*/
	if (nx >= 1)
	{
		vx = 0.05f;
	}
	else
	{
		vx = -0.05f;
	}
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void Bullet::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(206);// right
	this->AddAnimation(207);//left
	animations = NULL;

}

void Bullet::Render()
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


void Bullet::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void Bullet::BeAttack(int satThuong)
{
	hp = 0;
	Bullet::~Bullet();
}
