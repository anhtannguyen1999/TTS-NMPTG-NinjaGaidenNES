#include "Panther.h"






CPanther::CPanther(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_PANTHER;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 34;
	this->height = 15;
	nx = 1;
	vy = -0.03f;
	vx = 0.15f;
	startX = this->x;
}


CPanther::~CPanther()
{
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

    if (daChamDat == 0)
		y += dy;
	if (!onGround&&daChamDat != 0)//neu no di ra ngoai cai bien cua no
	{
		y += dy;
	}
	if (startX==890 || startX==1260)//con panther thu 2 va thu 4
	{
		nx = -1;
		vx = -0.1f;
		vy = -0.08f;
	}
	if (startX==940) //con panther thu 3
		vx = 0.1;
	/*if (!onGround&&daChamDat != 0)//neu no di ra ngoai cai bien cua no
	{
		if (this->x > startX)//Neu nam o bien ben phai thi quay dau di ve ben trai
		{
			vx = -0.05f;
			nx = -1;
		}
		else
		{
			vx = 0.05f;
			nx = 1;
		}
	}*/
	x += dx;
	if (y >= 170)//Bị rơi xuống đất

	{
		hp = 0;
		 DebugOut(L"Panther died");
	}
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CPanther::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(208);// right
	this->AddAnimation(209);//left
	animations = NULL;

}

void CPanther::Render()
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


void CPanther::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CPanther::BeAttack(int satThuong)
{
	hp = 0;
	CPanther::~CPanther();
}



