#include "BulletBoss.h"

CBulletBoss::CBulletBoss(int id, int x, int y, int nx)
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
	if (nx >= 1)
	{
		vx = 0.05f;//0.05f;
	}
	else
	{
		vx = -0.05f;
	}
	//vy = 0;
	//vx = -0.05f;
	//startX = this->x;
}


CBulletBoss::~CBulletBoss()
{
}

void CBulletBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	//CEnemy::Update(dt);
	/*if (daChamDat == 0)
	y += dy;*/

	x += vx*dt;
	//y += dy;
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
	if (x < 0)
		x = -50;
	if (x > 255)
		x = 265;
}




void CBulletBoss::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(230);
	
	animations = NULL;

}

void CBulletBoss::Render()
{
	/*int ani;
	if (nx > 0)
		ani = 0; //right
	else
		ani = 1;//left*/

	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[0]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox();
}


void CBulletBoss::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (this->nx >= 1)
	{
		x = this->x + 5;
	}
	else x = this->x + 5;
	y = this->y - 11;
	width = this->width;
	height = this->height;
}
void CBulletBoss::Reset()
{
	if (nx < 0)
	{
		x = 200;
		vx = -0.15f;
	}
	else
	{
		x = 50;
		vx = 0.15f;
	}
}
void CBulletBoss::BulletWait()
{
	x = -50;
	vx = 0;
	
	/*if (x < 0)
		x = -50;
	if (x > 255)
		x = 265;*/
}
void CBulletBoss::BeAttack(int satThuong)
{
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CBulletBoss::DeActivate()
{
	hp = 0;
	BulletWait();
}
