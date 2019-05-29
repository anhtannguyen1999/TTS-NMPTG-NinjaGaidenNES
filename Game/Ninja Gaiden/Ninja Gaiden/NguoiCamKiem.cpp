#include "NguoiCamKiem.h"



CNguoiCamKiem::CNguoiCamKiem(int id,int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_NGUOICAMKIEM;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 25;
	this->height = 34;
	nx = -1;
	vy = -0.1f;
	vx = -0.05f;
	startX = this->x;
}


CNguoiCamKiem::~CNguoiCamKiem()
{
}

void CNguoiCamKiem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	
	if (daChamDat==0)
		y += dy;
	if (!onGround&&daChamDat!=0)//neu no di ra ngoai cai bien cua no
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
	}
	
	if (startX == 1450)
	{
		vx = 0;
		nx = -1;
	}
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n", daChamDat,onGround,vx,nx);
}




void CNguoiCamKiem::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(200);// right
	this->AddAnimation(201);//left
	animations = NULL;
	
}

void CNguoiCamKiem::Render()
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


void CNguoiCamKiem::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CNguoiCamKiem::BeAttack(int satThuong)
{
	hp = 0;
	CNguoiCamKiem::~CNguoiCamKiem();
}
