#include "Butterfly.h"
#include "PointsBag.h"


Butterfly::Butterfly(int id, int x, int y,int ItemID)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = CONTAINER_MINITYPE_BUTTERFLY;
	this->x = x;
	this->ItemID = ItemID;
	this->y = y;
	this->dame = 0;
	this->hp = 10;
	this->width = 15;
	this->height = 15;
	nx = -1;
	/*vy = -0.2f;
	vx = -0.1f;*/

	//Gan diem ban dau
	/*this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;*/
}


Butterfly::~Butterfly()
{
}

void Butterfly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	timer++;

	/*if (this->hp == 0&&timer >=10)
	{
		PointsBag *bag = new PointsBag(0, this->x, this->y);
		listItem.push_back(bag);
		DebugOut(L"Da tao");
	}*/
	for (UINT i = 0; i < listItem.size(); i++)
	{
		listItem[i]->Update(dt,&listItem);
	}
#pragma region Va cham dat va di chuyen
	/*if (!onGround)
		y += dy;*/

	//if (onGround == true && this->firstY == -1)
	//	this->firstY = this->y;
	//if (this->firstY != -1 && onGround)//Neu da cai dat firstY
	//	this->y = this->firstY;


	//if (!onGround&&firstY != -1)//neu no di ra ngoai cai bien cua no thi quay dau
	//{
	//	//dy = 0;
	//	if (this->x > rootX + 1)//Neu nam o bien ben phai thi quay dau di ve ben trai
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

	//if (daChamDat<9 && daChamDat != 0) //Neu vua cham dat thi tim thang ninja
	//{
	//	if (this->x > ninja->x)
	//	{
	//		this->nx = -1;
	//		vx = -0.1f;
	//	}
	//	else
	//	{
	//		vx = 0.1f;
	//		this->nx = 1;
	//	}
	//}
	//x += dx;
#pragma endregion


	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void Butterfly::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(310);// right
	animations = NULL;

}

void Butterfly::Render()
{
	if (hp > 1)
	{
		int ani;
		ani = 0;//left
		D3DXVECTOR3 pos;
		pos.x = this->x;
		pos.y = this->y;
		pos.z = 0;
		pos = camera->SetPositionInViewPort(pos);
		animations[ani]->Render(pos.x, pos.y, ALPHA);
		this->RenderBoundingBox();
	}
	else
	{
		for (UINT i = 0; i < listItem.size(); i++)
		{
			listItem[i]->Render();
		}
	}
	
	
}


void Butterfly::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (hp > 1)
	{
		x = this->x + 4;
		y = this->y - 10;
		width = this->width;
		height = this->height;
	}
}

void Butterfly::BeAttack(int satThuong)
{
	hp=1;
	if (this->hp == 1 && timer >= 10)
	{
		switch (ItemID)
		{
		case ITEM_MINITYPE_BAGBLUE:
			{	PointsBag * bag = new PointsBag(0, this->x, this->y);
				listItem.push_back(bag);
				break;
				//DebugOut(L"Da tao");
			}	
		}
		
	}
	//DebugOut(L"Đã đánh");
	//ResetVeTrangThaiDau();
	//this->daChamDat = 0;
	//this->onGround = false;
	//this->ResetVeTrangThaiDau();
	//this->firstY = -1;
	//Butterfly::~Butterfly();
}
