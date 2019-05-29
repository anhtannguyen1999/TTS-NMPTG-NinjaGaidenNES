#include "Enemy.h"



CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
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

