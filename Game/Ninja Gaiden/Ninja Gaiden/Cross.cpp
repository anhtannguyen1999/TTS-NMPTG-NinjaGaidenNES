#include "Cross.h"
#include "Ninja.h"


CCross::CCross(int id, int x, int y, int nx,float vx)
{
	this->id = id;
	LoadResource();
	//this->typeEnemy = 0;
	this->x = x;
	this->y = y + 7;
	this->dame = 1;
	this->hp = 1;
	this->width = 8;
	this->height = 13;
	this->nx = nx;
	vy = 0.3f; //0.5f;
	if (nx >= 1)
	{
		this->vx = vx; // (rand() % 5 + 1)*0.03f;
	}
	else
	{
		this->vx = -vx; // -(rand() % 5 + 1)* 0.03f;
	}
	//vy = 0;
	//vx = -0.05f;
	//startX = this->x;
}


CCross::~CCross()
{
}

void CCross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);

	if (vy >= -0.5f&& timer % 3 == 0)
	{
		vy = vy -0.04f ;//0.1f;
	}
	timer++;
	/*if (daChamDat == 0)
	y += dy;*/
	y += dy;
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CCross::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(216);// right
	this->AddAnimation(217);//left
	animations = NULL;

}

void CCross::Render()
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


void CCross::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (this->nx >0)
	{
		x = this->x+8;
	}
	else x = this->x + 5;
	y = this->y - 11;
	width = this->width;
	height = this->height;
}

void CCross::BeAttack(int satThuong)
{
	hp = 0;
	//CCross::~CCross();
}
