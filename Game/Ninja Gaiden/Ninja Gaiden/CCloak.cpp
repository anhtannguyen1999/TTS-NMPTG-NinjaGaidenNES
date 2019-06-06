#include "CCloak.h"



CCloak::CCloak(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_CLOAK;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 0;
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
	this->soDiem = 100;
}


CCloak::~CCloak()
{
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		SAFE_DELETE(listProjectile[i]);
	}
}


float vxCross = 0;
void CCloak::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hp <= 0)
		return;
	//CNinja *ninja = CNinja::GetInstance();
	CGameObject::Update(dt);
	CEnemy::Update(dt);

	#pragma region Va cham dat va di chuyen
	if (firstY == -1)
		y += dy;

	if (onGround == true && this->firstY == -1)
		this->firstY = this->y;
	if (this->firstY != -1)//Neu da cai dat firstY
		this->y = this->firstY;

	
	if (chamBienGround==1)//Neu nam o bien ben phai thi quay dau di ve ben trai
	{
		vx = -0.05f;
	}
	else if(chamBienGround==-1)
	{
		vx = 0.05f;
	}

	//if (!onGround&&firstY != -1)//neu no di ra ngoai cai bien cua no thi quay dau
	//{
	//	//dy = 0;
	//	if (this->x > rootX + 1)//Neu nam o bien ben phai thi quay dau di ve ben trai
	//	{
	//		vx = -0.05f;
	//	}
	//	else
	//	{
	//		vx = 0.05f;
	//	}
	//}
	
	
	x += dx;
	#pragma endregion

	#pragma region Ban dan- cross
	if(!isPause)
		timer++;
	//DebugOut(L"timer: %d \n", timer);
	if (timer >= 130)
	{
		timer = 0;
	}

	if (timer == 100) //Neu timmer= 100 thi ban dan
	{
		vxCross = (rand() % 5 + 1)*0.03f;
		CCross *cross = new CCross(3, this->x, this->y, this->nx, vxCross);
		listProjectile.push_back(cross);
	}

	int soLuongCrossThem = (rand() % 10<7)?0: (rand() % 10<9)?1 :2;//random so luong cross them 70% la khong them, 20% them 1, 10% them 2
	if (timer == 110 && soLuongCrossThem >0) // Neu them hon 0 cross // tu 1-2 cross
	{
		CCross *cross = new CCross(3, this->x, this->y, this->nx, vxCross);
		listProjectile.push_back(cross);
	}
	if (timer == 120 && soLuongCrossThem >1) // Neu them hon 1 cross//them hon 2 cross
	{
		CCross *cross = new CCross(3, this->x, this->y, this->nx, vxCross);
		listProjectile.push_back(cross);
	}

	#pragma endregion

	//update Cross
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		if(listProjectile[i]!=NULL)
			listProjectile[i]->Update(dt, &listProjectile);
	}

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
	if (hp <= 0)
		return;
	if (!isPause)
	{
		if (this->x > ninja->x) //Quay mat ve ninja
		{
			this->nx = -1;
		}
		else
		{
			this->nx = 1;
		}
	}
	
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 100 && timer <= 120)
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
		if (timer >= 100 && timer <= 120)
		{
			ani = 3;
		}
	}
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	if (isPause)
		animations[ani]->ResetCurrentFrame();
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	/*animations[ani2]->Render(pos.x, pos.y, ALPHA);*/

	//Render dan
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		if (listProjectile[i] != NULL)
			listProjectile[i]->Render();
	}

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
	if (hp <= 0)
		return;
	x = this->x+3;
	y = this->y-5;
	width = this->width-3;
	height = this->height;
}

void CCloak::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}
void CCloak::DeActivate()
{
	hp = 0;
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		SAFE_DELETE(listProjectile[i]);
	}
	listProjectile.clear();
	ResetVeTrangThaiDau();
}

void CCloak::ClearListCross()
{
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		SAFE_DELETE(listProjectile[i]);
	}
	listProjectile.clear();
}

void CCloak::RefreshListCross()
{

	int i = 0;
	while (i < listProjectile.size())//Neu hp=0 thi huy
	{
		if (listProjectile[i]->GetHP() == 0) {
			listProjectile.erase(listProjectile.begin()+i);
			i--;
		}
		i++;
	}

	//DebugOut(L"Size: %d \n", listProjectile.size());

}


