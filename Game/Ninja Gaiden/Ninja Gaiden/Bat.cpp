#include "Bat.h"


CBat::CBat(int id, int x, int y,int rootNX)
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
	nx = rootNX;
	vy = -0.05f;
	vx = 0.05f;

	//Luu diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;

	this->soDiem = 100;
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
	if (hp <= 0)
		return;
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
	if (isPause)
		animations[ani]->ResetCurrentFrame();
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox();
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hp <= 0)
		return;
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	if (!isPause)
	{
		x += dx;
		y = 80 + 10 * sin(x / 3);
	}
}

void CBat::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (hp <= 0)
		return;
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CBat::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CBat::DeActivate()
{
	hp = 0;
	this->ResetVeTrangThaiDau();
}
