#include "Panther.h"






CPanther::CPanther(int id, int x, int y,int rootNX)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_PANTHER;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 0;
	this->width = 34;
	this->height = 20;
	nx = rootNX;
	vy = -0.1f;
	vx = 0.11f;
	
	//Luu diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
	this->soDiem = 100;
}


CPanther::~CPanther()
{
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hp <= 0)
		return;
	CGameObject::Update(dt);
	CEnemy::Update(dt);
   // if (daChamDat == 0)
	if(!onGround)
		y += dy;

	if (daChamDat<9) //Neu vua cham dat thi tim thang ninja
	{
		if (this->x > ninja->x)
		{
			this->nx = -1;
			vx = -0.11f;
		}
		else
		{
			vx = 0.11f;
			this->nx = 1;
		}

	}
	
	x += dx;
	if (y >= 170)//Bị rơi xuống đất
	{
		//hp = 0;
		this->BeAttack(1);
		 //DebugOut(L"Panther died");
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
	if (hp <= 0)
		return;
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
	if (isPause)
		animations[ani]->ResetCurrentFrame();
	//this->RenderBoundingBox();
}


void CPanther::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (hp <= 0)
		return;
	x = this->x;
	y = this->y-5;
	width = this->width;
	height = this->height;
}

void CPanther::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CPanther::DeActivate()
{
	hp = 0;
	this->isHit = 0;
	this->daChamDat = 0;
	this->onGround = false;
	this->ResetVeTrangThaiDau();
	//DebugOut(L"BiDanh!");
}



