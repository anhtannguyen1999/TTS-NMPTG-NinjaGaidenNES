#include "Weapon.h"



CWeapon::CWeapon()
{
	//this->AddAnimation(301);//Hieu ung no
}


CWeapon::~CWeapon()
{
}

void CWeapon::DanhChetEnemy()
{
	//this->danhChetEnemy = 1;
	BienMatKhiChamEnemy();
}

void CWeapon::Render()
{
}

void CWeapon::SetPosition(float x, float y, int nx)
{
	this->x = x, this->y = y;
	this->nx = nx;
}

void CWeapon::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}
