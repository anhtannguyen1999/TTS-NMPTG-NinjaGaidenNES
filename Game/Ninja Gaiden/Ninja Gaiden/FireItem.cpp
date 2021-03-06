#include "FireItem.h"


FireItem::FireItem(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeItem = 0;
	this->x = x;
	this->y = y;
	this->hp = 1;
	this->width = 15;
	this->height = 15;

	//Luu diem ban dau
	vy = -0.5f;
}

FireItem::~FireItem()
{

}

void FireItem::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(326);// right

	animations = NULL;

}

void FireItem::Render()
{
	int ani;
	ani = 0; //right

	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	//this->RenderBoundingBox();
}

void FireItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Item::Update(dt);
	if (!onGround)
	{
		y += dy;
	}
}

void FireItem::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x + 4;
	y = this->y - 7;
	width = this->width;
	height = this->height;
}

