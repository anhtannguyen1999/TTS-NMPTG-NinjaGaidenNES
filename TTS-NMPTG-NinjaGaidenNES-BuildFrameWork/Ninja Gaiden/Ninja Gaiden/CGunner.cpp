#include "CGunner.h"
#include"Bullet.h"


CGunner::CGunner(int id,int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_GUNNER;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 24;
	this->height = 35;
	nx = -1;
	vy = 0;
	vx = 0;
	startX = this->x;
}


CGunner::~CGunner()
{
}

void CGunner::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CNinja *ninja = CNinja::GetInstance();
	CGameObject::Update(dt);
	
	if (daChamDat==0)
		y += dy;
	if (ninja->GetPositionX() - this->x >= 0)
	{
		nx = 1;
	}
	else nx = -1;
	timer++;
	if (timer == 400)
	{
		timer = 0;
	}
	if (timer >=300&&timer <=320)
	{
		Bullet *bullet = new Bullet(3, this->x, this->y, this->nx);
		/*bullet->Render();*/
	}
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CGunner::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(204);// right
	this->AddAnimation(224);
	this->AddAnimation(205);//left
	this->AddAnimation(225);
	animations = NULL;
	
}

void CGunner::Render()
{
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 300&&timer <=320)
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
		if (timer >= 300&&timer<=320)
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

//void CGunner::RenderShoot()
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


void CGunner::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CGunner::BeAttack(int satThuong)
{
	hp = 0;
	CGunner::~CGunner();
}