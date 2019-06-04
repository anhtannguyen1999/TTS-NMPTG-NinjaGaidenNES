#include "BigShuriken.h"


CBigShuriken * CBigShuriken::__instance = NULL;

CBigShuriken * CBigShuriken::GetInstance()
{
	if (__instance == NULL)
		__instance = new CBigShuriken();
	return __instance;
}

CBigShuriken::CBigShuriken()
{
	this->x = 0;
	this->y = 0;
	this->width = 15;
	this->height = 15;
	this->mana = 5;
	this->minitypeWeapon = WEAPON_MINITYPE_BIG_SHURIKEN;
	//Load resource
	this->AddAnimation(330); //Animation 0

}


CBigShuriken::~CBigShuriken()
{
}


void CBigShuriken::Update(DWORD dt, int ninjaX, int ninjaY)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (active)
	{
		width = 15;
		height = 15;
		
		GiaoDongQuanhNinja(ninjaX,ninjaY);

		//Neu no cham vao giua ninja thi huy
		if (this->x>=ninjaX&&this->x<=ninjaX+NINJA_WIDTH_TMP && this->y<=ninjaY-5 && this->y >= ninjaY - NINJA_HEIGHT_TMP)
		{
			this->active = false;
		}
	}
	else
	{
		width = 0;
		height = 0;
		x = ninjaX;
		y = ninjaY;
		bienDoX = (abs(x - ninjaX) + 300) / 2;
		tamGiaoDongX = (x + ninjaX) / 2;
	}

}

void CBigShuriken::Render()
{
	if (!active)
		return;
	//CWeapon::Render();
	D3DXVECTOR3 pos;
	pos.x = this->x - 4;
	pos.y = this->y + 10;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[0]->Render(pos.x, pos.y, ALPHA);
	//this->RenderBoundingBox(70);
}

void CBigShuriken::SetPosition(float x, float y, int nx)
{
	if (!this->active)//Neu chua ban ra thi moi duoc set
	{
		this->x = this->rootX = x;
		this->y = this->rootY = y;
		this->nx = nx;
		if (nx > 0)
			moveLeft = false;
		else
			moveLeft = true;
	}

}


void CBigShuriken::GiaoDongQuanhNinja(int ninjaX, int ninjaY)
{
	
	//Khoi tao tam va bien do A cua giao dong.
	if (!dangGiaoDongX) //Neu o bien thi cho no giao dong vao tam
	{
		dangGiaoDongX = true;
		//Tinh bien do A cua giao dong |  N      | bien do giao dong x neu ninja dung yen se la 150
		bienDoX = (abs(x - ninjaX) + 200) / 2;
		tamGiaoDongX = (x + ninjaX) / 2;
		
	}

	//Tinh van toc
	if (dangGiaoDongX)
	{
		//v= omega*sqrt(A^2 - x^2); van toc cua giao dong lo xo, omega=sqrt(k/m) => tu chinh cho phu hop
		if (moveLeft)//0.0026
			vx = -0.003f*sqrt(abs(bienDoX * bienDoX - (tamGiaoDongX - x)*(tamGiaoDongX - x)));
		else
			vx = 0.003f*sqrt(abs(bienDoX * bienDoX - (tamGiaoDongX - x)*(tamGiaoDongX - x)));
	}

	//Xet trang thai bien de doi chieu giao dong
	//Truc X
	if (x >= tamGiaoDongX + bienDoX || ninjaX<tamGiaoDongX - bienDoX)//Neu xchim vuot qua bien phai hoac ninja chay qua bien trai
	{
		dangGiaoDongX = false;
		moveLeft = true;
	}
	else if (x <= tamGiaoDongX - bienDoX || ninjaX>tamGiaoDongX + bienDoX) //neu chim vuot qua bien trai hoac ninja chay qua bien
	{
		dangGiaoDongX = false;
		moveLeft = false;
	}

	if (y >= ninjaY-5)
		vy = -0.04f;
	else if (y <= ninjaY-5)
		vy = 0.04f;
	else vy = 0;

}



