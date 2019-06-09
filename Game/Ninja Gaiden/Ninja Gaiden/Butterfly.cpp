#include "Butterfly.h"

Butterfly::Butterfly(int id, int x, int y,int ItemType)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = CONTAINER_MINITYPE_BUTTERFLY;
	this->x = x;
	this->ItemType = ItemType;
	this->y = y;
	this->dame = 0;
	this->hp = 10;
	this->width = 15;
	this->height = 15;
	nx = -1;
	
}


Butterfly::~Butterfly()
{
	SAFE_DELETE(item);
}

void Butterfly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	timer++;

	if (item)
	{
		item->Update(dt);
		//Neu da danh ra item roi va di ra ngoai thi item lan container bi huy
		
	}
		
	
}

bool Butterfly::isItemNamNgoaiCamera()
{
	//Neu bi danh rot item va item nam ngoai camera thi se duoc huy het tat ca
	if (item)
	{
		if (this->x < camera->GetX() || this->x > camera->GetX() + camera->GetWidth()
			|| this->y <camera->GetY() - camera->GetHeight() || this->y > camera->GetY())
		{
			return true;

		}
	}
	return false;
}


void Butterfly::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(310);// right
	animations = NULL;

}

void Butterfly::Render()
{
	if (hp > 1)
	{
		int ani;
		ani = 0;//left
		D3DXVECTOR3 pos;
		pos.x = this->x;
		pos.y = this->y;
		pos.z = 0;
		pos = camera->SetPositionInViewPort(pos);
		animations[ani]->Render(pos.x, pos.y, ALPHA);
		//this->RenderBoundingBox();
	}
	else
	{
		if(item)
			item->Render();
	}
}


void Butterfly::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (hp > 1)
	{
		x = this->x + 4;
		y = this->y - 10;
		width = this->width;
		height = this->height;
	}
}

void Butterfly::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void Butterfly::DeActivate()
{
	hp = 1;
	if (this->hp == 1 && timer >= 10)
	{
		switch (ItemType)
		{
		case ITEM_MINITYPE_BAGBLUE:
			//PointsBag * bag = new PointsBag(0, this->x, this->y);
			//listItem.push_back(bag);
			item = new PointsBag(0, this->x, this->y);
			break;
			//DebugOut(L"Da tao");
		case ITEM_MINITYPE_BAGRED:
			item = new PointsBagRed(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_SOULBLUE:
			item = new SoulBlue(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_SOULRED:
			item = new SoulRed(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_SMALLSHURIKEN:
			item = new SShurikenItem(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_BIGSHURIKEN:
			item = new BShurikenItem(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_FIREITEM:
			item = new FireItem(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_HEALTHPOT:
			item = new HealthPot(0, this->x, this->y);
			break;
		case ITEM_MINITYPE_HOURGLASS:
			item = new Hourglass(0, this->x, this->y);
			break;
		}

	}

}
