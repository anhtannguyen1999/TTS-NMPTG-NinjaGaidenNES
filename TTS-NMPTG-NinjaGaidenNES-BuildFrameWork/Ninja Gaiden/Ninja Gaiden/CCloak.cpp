#include "CCloak.h"



CCloak::CCloak(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_CLOAK;
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


CCloak::~CCloak()
{
}

void CCloak::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CNinja *ninja = CNinja::GetInstance();
	CGameObject::Update(dt);

	if (daChamDat == 0)
		y += dy;
	/*if (ninja->GetPositionX() - this->x >= 0)
	{
		nx = 1;
	}
	else nx = -1;*/
	timer++;
	if (timer == 400)
	{
		timer = 0;
	}
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
	//if (timer >= 300 && timer <= 320)
	//{
	//	Bullet *bullet = new Bullet(3, this->x, this->y, this->nx);
	//	/*bullet->Render();*/
	//}
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CCloak::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(214);// right
	this->AddAnimation(234);
	this->AddAnimation(215);//left
	this->AddAnimation(235);
	animations = NULL;

}

void CCloak::Render()
{
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 300 && timer <= 320)
		{
			ani = 1;
		}
	}
	else
	{
		ani = 2;//left
				/*for (int t = 0; t < 2000000; t++)
				{
				if (t == 199999)
				{
				ani = 3;
				t = 0;
				}
				}*/
		if (timer >= 300 && timer <= 320)
		{
			ani = 3;
		}
	}
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	/*animations[ani2]->Render(pos.x, pos.y, ALPHA);*/
	this->RenderBoundingBox();
}

//void CCloak::RenderShoot()
//{
//	int ani;
//	/*int ani2;*/
//	if (nx > 0)
//	{
//		ani = 1; //right
//				 /*for (int t = 0; t < 2000000; t++)
//				 {
//				 if (t == 199999)
//				 {
//				 ani = 1;
//				 t = 0;
//				 }
//				 }*/
//	}
//	else
//	{
//		ani = 3;//left
//				/*for (int t = 0; t < 2000000; t++)
//				{
//				if (t == 199999)
//				{
//				ani = 3;
//				t = 0;
//				}
//				}*/
//	}
//	D3DXVECTOR3 pos;
//	pos.x = this->x;
//	pos.y = this->y;
//	pos.z = 0;
//	pos = camera->SetPositionInViewPort(pos);
//	animations[ani]->Render(pos.x, pos.y, ALPHA);
//	/*animations[ani2]->Render(pos.x, pos.y, ALPHA);*/
//	this->RenderBoundingBox();
//}


void CCloak::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CCloak::BeAttack(int satThuong)
{
	hp = 0;
	CCloak::~CCloak();
}
