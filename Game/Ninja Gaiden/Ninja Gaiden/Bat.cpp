#include "Bat.h"


CBat::CBat(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_BAT;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 20;
	this->height = 16;
	nx = -1;
	vy = -0.05f;
	vx = 0.05f;

	//Luu diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
}

CBat::~CBat()
{
}

void CBat::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(210);// right
	this->AddAnimation(211);//left
	animations = NULL;

}

void CBat::Render()
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

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	x += dx;
	y = 80 + 10*sin(x/3);
}

void CBat::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CBat::BeAttack(int satThuong)
{
	hp = 0;
	this->ResetVeTrangThaiDau();
	//CBat::~CBat();
}
