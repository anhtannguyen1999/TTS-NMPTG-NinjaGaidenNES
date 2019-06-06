#include "Enemy.h"



CEnemy::CEnemy()
{
	isPause = false;
}


CEnemy::~CEnemy()
{
}


void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isPause)
	{
		dx = 0;
		dy = 0;
	}
	//Neu nam ngoai camera thi huy
	if (this->x < camera->GetX() || this->x > camera->GetX() + camera->GetWidth()
		|| this->y <camera->GetY() - camera->GetHeight() || this->y > camera->GetY())
	{
		//this->BeAttack(1);
		this->DeActivate();
		//hp=0 se duoc loai khoi grid
		//Khong can xet o duoi vi bird vs butter se khong goi ham update cua enemy
		////Neu khong phai la bird hay butter
		//if (!(this->typeEnemy == CONTAINER_MINITYPE_BIRD || this->typeEnemy == CONTAINER_MINITYPE_BUTTERFLY))
		//{
		//	this->BeAttack(1);//hp=0 se duoc loai khoi grid
		//}
		
	}
}

void CEnemy::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

int CEnemy::GetTypeEnemy()
{
	return this->typeEnemy;
}

int CEnemy::GetDame()
{
	return this->dame;
}

void CEnemy::BeAttack(int satThuong)
{
	Sound::getInstance()->play(DirectSound_ENEMY_ATTACKED);
}

float CEnemy::GetRootX()
{
	return this->rootX;
}

float CEnemy::GetRootY()
{
	return this->rootY;
}

void CEnemy::SetIsPause(bool isPause)
{
	if (this->isPause != isPause) this->isPause = isPause;
}

int CEnemy::isNamTaiMepGround(CGameObject * ground)
{
	float gX, gY, gW, gH;
	ground->GetBoundingBox(gX, gY, gW, gH);
	if (this->x > gX - this->width && this->x <= gX) //Sat mep trai
	{
		return -1;
	}
	else if (this->x >= gX + gW - this->width && this->x < gX + gW)//mep phai
		return 1;
	else 
		return 0;
}

