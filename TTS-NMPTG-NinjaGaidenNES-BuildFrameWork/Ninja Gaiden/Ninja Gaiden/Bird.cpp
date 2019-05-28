#include "Bird.h"



Bird::Bird(int id, int x, int y,int ItemId)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = CONTAINER_MINITYPE_BIRD;
	this->x = x;
	this->ItemId = ItemId;
	this->y = y;
	this->dame = 0;
	this->hp = 1;
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


Bird::~Bird()
{
}

void Bird::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);

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




void Bird::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(311);// right
	animations = NULL;

}

void Bird::Render()
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


void Bird::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x + 4;
	y = this->y - 10;
	width = this->width;
	height = this->height;
}

void Bird::BeAttack(int satThuong)
{
	hp = 0;
	//ResetVeTrangThaiDau();
	//this->daChamDat = 0;
	//this->onGround = false;
	//this->ResetVeTrangThaiDau();
	//this->firstY = -1;
	//Bird::~Bird();
}
