#include "Hawk.h"


CHawk::CHawk(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_HAWK;
	this->x = x;
	this->y = y;
	this->dame = 3;
	this->hp = 1;
	this->width = 20;
	this->height = 20;
	nx = -1; //ben trai
	vy = -0.026f;
	vx =-0.05f;
	//startX = this->x;
	//startY = this->y;
	tamGiaoDongX = ninja->x;

	//Gan diem ban dau
	this->rootX = x;
	this->rootY = y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
}

CHawk::~CHawk()
{
}

void CHawk::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(212);// right
	this->AddAnimation(213);//left
	animations = NULL;
}

void CHawk::Render()
{
	int ani;
	if (this->x-ninja->x > 0)//Neu nam ben phai ninja
		nx = -1;
	else if(this->x- ninja->x <0) //Neu nam ben trai ninja
		nx = 1;
	if (nx > 0) //quay mat ben phai
		ani = 0; //right
	else
		ani = 1;//left
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox(170);
}

void CHawk::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (vuaKhoiTao)
	{
		vuaKhoiTao = false;
		if (this->x < ninja->x)//Neu o ben trai ninja thi qua phai
			moveLeft = false;
		else 
			moveLeft = true;
	}
	this->GiaoDongQuanhNinja();
	CGameObject::Update(dt);
	CEnemy::Update(dt);

	
	
	x += dx;
	y += dy;
	
	//DebugOut(L"Hawk\n");
}

void CHawk::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y-6;
	width = this->width;
	height = this->height;
}

void CHawk::BeAttack(int satThuong)
{
	hp = 0;
	bienDoX = 100;
	tamGiaoDongX = ninja->x;
	dangGiaoDongX = false;
	vuaKhoiTao = true;
	ResetVeTrangThaiDau();
	moveDown = true;
	//moveLeft = true;
	//CHawk::~CHawk();
	
}

void CHawk::GiaoDongQuanhNinja()
{
	//Khoi tao tam va bien do A cua giao dong.
	if (!dangGiaoDongX) //Neu o bien thi cho no giao dong vao tam
	{
		dangGiaoDongX = true;
		//Tinh bien do A cua giao dong |  N      | bien do giao dong x neu ninja dung yen se la 150
		bienDoX = (abs(x - ninja->x) + 150) / 2; 
		//Xac dinh tam cua giao dong
		tamGiaoDongX = (x + ninja->x) / 2;
	}
	
	//Tinh van toc
	if (dangGiaoDongX)
	{
		//v= omega*sqrt(A^2 - x^2); van toc cua giao dong lo xo, omega=sqrt(k/m) => tu chinh cho phu hop
		if (moveLeft)
			vx = -0.0012f*sqrt(abs(bienDoX * bienDoX - (tamGiaoDongX - x)*(tamGiaoDongX - x)));
		else
			vx = 0.0012f*sqrt(abs(bienDoX * bienDoX - (tamGiaoDongX - x)*(tamGiaoDongX - x)));
	}
	
	//Xet trang thai bien de doi chieu giao dong
	//Truc X
	if (x >= tamGiaoDongX + bienDoX || ninja->x<tamGiaoDongX - bienDoX)//Neu xchim vuot qua bien phai hoac ninja chay qua bien trai
	{
		dangGiaoDongX = false;
		moveLeft = true;
	}
	else if (x <= tamGiaoDongX - bienDoX || ninja->x>tamGiaoDongX + bienDoX) //neu chim vuot qua bien trai hoac ninja chay qua bien
	{
		dangGiaoDongX = false;
		moveLeft = false;
	}

	if (y > ninja->y-8)
		vy = -0.03f;
	else if (y < ninja->y-8)
		vy = 0.03f;
	else vy = 0;

}
