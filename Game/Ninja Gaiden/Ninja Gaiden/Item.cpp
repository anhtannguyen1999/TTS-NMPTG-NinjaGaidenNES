#include "Item.h"



Item::Item()
{

}


Item::~Item()
{
}


void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Neu nam ngoai camera thi huy
	//if (this->x < camera->GetX() || this->x > camera->GetX() + camera->GetWidth()
	//	|| this->y <camera->GetY() - camera->GetHeight() || this->y > camera->GetY())
	//{
	//	this->BeAttack(1);//hp=0 se duoc loai khoi grid
	//}
}

void Item::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

int Item::GetTypeItem()
{
	return this->typeItem;
}



