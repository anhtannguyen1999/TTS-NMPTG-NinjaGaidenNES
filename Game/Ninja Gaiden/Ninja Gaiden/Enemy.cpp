#include "Enemy.h"



CEnemy::CEnemy()
{

}


CEnemy::~CEnemy()
{
}


void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Neu nam ngoai camera thi huy
	if (this->x < camera->GetX() || this->x > camera->GetX() + camera->GetWidth()
		|| this->y <camera->GetY() - camera->GetHeight() || this->y > camera->GetY())
	{
		this->BeAttack(1);//hp=0 se duoc loai khoi grid
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

float CEnemy::GetRootX()
{
	return this->rootX;
}

float CEnemy::GetRootY()
{
	return this->rootY;
}

