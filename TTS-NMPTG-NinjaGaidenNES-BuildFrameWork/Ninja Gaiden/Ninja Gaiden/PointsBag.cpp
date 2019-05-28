#include "PointsBag.h"


PointsBag::PointsBag(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeItem = 0;
	this->x = x;
	this->y = y;
	this->hp = 1;
	this->width = 20;
	this->height = 16;

	//Luu diem ban dau
	vy = -0.5f;
}

PointsBag::~PointsBag()
{
	
}

void PointsBag::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(320);// right
	
	animations = NULL;

}

void PointsBag::Render()
{
	int ani;
		ani = 0; //right
	
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox();
}

void PointsBag::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Item::Update(dt);
	if (!onGround)
	{
		y += dy;
	}
}

void PointsBag::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

