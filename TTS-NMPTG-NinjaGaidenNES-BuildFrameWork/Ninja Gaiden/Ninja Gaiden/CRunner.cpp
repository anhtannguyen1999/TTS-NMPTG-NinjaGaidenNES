#include "CRunner.h"



CRunner::CRunner(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_RUNNER;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 24;
	this->height = 35;
	nx = -1;
	vy = -0.1f;
	vx = -0.05f;
	startX = this->x;
}


CRunner::~CRunner()
{
}

void CRunner::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (daChamDat == 0)
		y += dy;
	if (!onGround&&daChamDat != 0)//neu no di ra ngoai cai bien cua no
	{
		if (this->x > startX)//Neu nam o bien ben phai thi quay dau di ve ben trai
		{
			vx = -0.1f;
			nx = -1;
		}
		else
		{
			vx = 0.1f;
			nx = 1;
		}
	}
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CRunner::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(202);// right
	this->AddAnimation(203);//left
	animations = NULL;

}

void CRunner::Render()
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


void CRunner::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CRunner::BeAttack(int satThuong)
{
	hp = 0;
	CRunner::~CRunner();
}
