#include "CGunner.h"

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

	//Gan diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
}


CGunner::~CGunner()
{
}

void CGunner::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CNinja *ninja = CNinja::GetInstance();
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	/*if (daChamDat==0)
		y += dy;*/
	if (ninja->GetPositionX() - this->x >= 0)
	{
		nx = 1;
	}
	else nx = -1;
	//ban dan
	timer++;
	if (timer >= 150)
	{
		timer = 0;
	}
	if (timer == 95)
	{
		CBulletGunner *bullet = new CBulletGunner(2, this->x, this->y, this->nx);
		listProjectile.push_back(bullet);
	}
	//update dan
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		listProjectile[i]->Update(dt, &listProjectile);
	}
	//DebugOut(L"So dan: %d \n", listProjectile.size());
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
	//Render dan
	for (UINT i = 0; i < listProjectile.size(); i++)
	{

		listProjectile[i]->Render();
		//DebugOut(L"Render sucess");
	}
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 100&&timer <=120)
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
		if (timer >= 100&&timer<=120)
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
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		SAFE_DELETE(listProjectile[i]);
	}
	listProjectile.clear();
	ResetVeTrangThaiDau();
	//CGunner::~CGunner();
}
void CGunner::RefreshListBullet()
{
	int i = 0;
	while (i < listProjectile.size())//Neu hp=0 thi huy
	{
		if (listProjectile[i]->GetHP() == 0) {
			listProjectile.erase(listProjectile.begin() + i);
			i--;
		}
		i++;
	}
}
