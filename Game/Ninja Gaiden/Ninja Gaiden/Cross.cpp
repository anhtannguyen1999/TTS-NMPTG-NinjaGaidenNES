#include "Cross.h"


CCross::CCross(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_CROSS;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 20;
	this->height = 16;
	nx = -1;
	vy = -0.05f;
	vx = -0.01f;
	startX = this->x;
}

CCross::~CCross()
{
}

void CCross::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(210);// right
	this->AddAnimation(211);//left
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

void CCross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//dx = vx * x*sin(x);
	//dy = y*sin(x);
	
}

void CCross::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CCross::BeAttack(int satThuong)
{
	hp = 0;
	CCross::~CCross();
}
