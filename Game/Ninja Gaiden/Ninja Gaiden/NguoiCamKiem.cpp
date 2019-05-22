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
	vy = -0.03f;//-0.02f;
	vx = -0.05f;
	//startX = this->x;

	//Luu diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
}


CNguoiCamKiem::~CNguoiCamKiem()
{
}

void CNguoiCamKiem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	if (firstY == -1)
		y += dy;

	if(onGround==true&& this->firstY == -1)
		this->firstY= this->y;
	if (this->firstY != -1)//Neu da cai dat firstY
		this->y = this->firstY;
	
	if (!onGround&&firstY!=-1)//neu no di ra ngoai cai bien cua no thi quay dau
	{
		//dy = 0;
		if (this->x > rootX+1)//Neu nam o bien ben phai thi quay dau di ve ben trai
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
	if (daChamDat<9&&daChamDat!=0) //Neu vua cham dat thi tim thang ninja
	{
		if (this->x > ninja->x)
		{
			this->nx = -1;
			vx = -0.05f;
		}
		else
		{
			vx = 0.05f;
			this->nx = 1;
		}
			
	}
	x += dx;

	//DebugOut(L"cham dat %d; onground %d ; firstY %d\n", daChamDat,onGround,firstY);
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

void CNguoiCamKiem::SetOnGround(bool onGround)
{
	this->onGround = onGround;
	if (onGround&&daChamDat<10) daChamDat++;
}

void CNguoiCamKiem::BeAttack(int satThuong)
{
	/*
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);*/
	hp = 0;
	this->isHit = 0;
	this->daChamDat = 0;
	this->onGround = false;
	this->ResetVeTrangThaiDau();
	//this->firstY = -1;
	//CNguoiCamKiem::~CNguoiCamKiem();
}

void CNguoiCamKiem::SetFirstY(int fY)
{
	if (firstY != -1)
		this->firstY = fY;//this->y;
}
