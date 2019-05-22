#include "CCommando.h"



CCommando::CCommando(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_COMMANDO;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 24;
	this->height = 35;
	nx = -1;
	vy = -0.1f;
	vx = -0.05f;
	//startX = this->x;
	//Gan diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
}


CCommando::~CCommando()
{
}

void CCommando::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CNinja *ninja = CNinja::GetInstance();
	CGameObject::Update(dt);
	CEnemy::Update(dt);

	#pragma region Va cham dat va di chuyen
	if (firstY == -1)
		y += dy;

	if (onGround == true && this->firstY == -1)
		this->firstY = this->y;
	if (this->firstY != -1)//Neu da cai dat firstY
		this->y = this->firstY;

	//neu no di ra ngoai cai bien cua no thi quay dau
	if (!onGround&&firstY != -1)
	{
		//dy = 0;
		if (this->x > rootX + 1)//Neu nam o bien ben phai thi quay dau di ve ben trai
		{
			vx = -0.05f;
		}
		else
		{
			vx = 0.05f;
		}
	}

	//Huong toi ninja
	if (this->x > ninja->x)
	{
		vx = -0.05f;
		nx = -1;
	}	
	else
	{
		vx = 0.05f;
		nx = 1;
	}
		

	//if (daChamDat<9 && daChamDat != 0) //Neu vua cham dat thi tim thang ninja
	//{
	//	if (this->x > ninja->x)
	//		vx = -0.05f;
	//	else
	//		vx = 0.05f;
	//}
	x += dx;
	#pragma endregion



	timer++;
	if (timer >= 200)
	{
		timer = 0;
	}

	//Thoi gian ban sung
	if (timer >= 100 && timer < 200)
	{
		//Bullet *bullet = new Bullet(3, this->x, this->y, this->nx);
		/*bullet->Render();*/
		vx = 0;
	}


	//if (daChamDat == 0)
	//	y += dy;
	///*if (ninja->GetPositionX() - this->x >= 0)
	//{
	//nx = 1;
	//}
	//else nx = -1;*/
	//
	//if (!onGround&&daChamDat != 0)//neu no di ra ngoai cai bien cua no
	//{
	//	if (this->x > rootX)//Neu nam o bien ben phai thi quay dau di ve ben trai
	//	{
	//		vx = -0.1f;
	//		nx = -1;
	//	}
	//	else
	//	{
	//		vx = 0.1f;
	//		nx = 1;
	//	}
	//}
	//x += dx;
	//if (timer >= 300 && timer <= 320)
	//{
	//	Bullet *bullet = new Bullet(3, this->x, this->y, this->nx);
	//	/*bullet->Render();*/
	//}
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CCommando::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(240);// right
	this->AddAnimation(242);
	this->AddAnimation(241);//left
	this->AddAnimation(243);
	animations = NULL;

}

void CCommando::Render()
{
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 100 && timer <200)
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
		if (timer >= 100 && timer <200)
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

//void CCommando::RenderShoot()
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


void CCommando::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CCommando::BeAttack(int satThuong)
{
	hp = 0;
	ResetVeTrangThaiDau();
	//CCommando::~CCommando();
}
