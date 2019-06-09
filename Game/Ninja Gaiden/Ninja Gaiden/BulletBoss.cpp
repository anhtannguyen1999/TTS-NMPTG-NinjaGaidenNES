#include "BulletBoss.h"

CBulletBoss::CBulletBoss(int id, int x, int y, int nx, int rootX, int Delay)
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
	this->rootX = rootX;
	this->nx = nx;
	this->Delay = Delay;
	if (nx >= 1)
	{
		vx = 0.1f;//0.05f;
	}
	else
	{
		vx = -0.1f;
	}
	this->rootVX = vx;
	//vy = 0;
	//vx = -0.05f;
	//startX = this->x;
}


CBulletBoss::~CBulletBoss()
{
}

void CBulletBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - prevDelay >= Delay)
	{
		vx = this->rootVX;
	}
	else
	{
		vx = 0;
	}

	x += vx * dt;

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
	//this->RenderBoundingBox();
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
	prevDelay = GetTickCount();

	if (nx < 0)
	{

		this->x = this->rootX;
		//vx =this->rootVX ;
	}
	else
	{
		this->x = this->rootX;
		//vx = this->rootVX;
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
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CBulletBoss::DeActivate()
{
	hp = 0;
	BulletWait();
}
