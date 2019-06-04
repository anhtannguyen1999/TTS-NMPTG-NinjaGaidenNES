#include "Boss.h"



CBoss::CBoss(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_BOSS;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1000;
	this->width = 30;
	this->height = 40;
	nx = -1;
	vy = -0.05f;
	vx = -0.1f;
	startX = this->x;
	TimePrevFly = GetTickCount();
	CBulletBoss *bullet0 = new CBulletBoss(2, -50, 85, 1);
	CBulletBoss *bullet1 = new CBulletBoss(2, -50, 70, 1);
	CBulletBoss *bullet2 = new CBulletBoss(2, -50, 60, 1);

	//CBulletBoss *bullet3 = new CBulletBoss(2, 280, 70, -1);
	//CBulletBoss *bullet4 = new CBulletBoss(2, 280, 60, -1);
	//CBulletBoss *bullet5 = new CBulletBoss(2, 280, 50, -1);

	CBulletBoss *bullet3 = new CBulletBoss(2, 280, 85, -1);
	CBulletBoss *bullet4 = new CBulletBoss(2, 280, 70, -1);
	CBulletBoss *bullet5 = new CBulletBoss(2, 280, 60, -1);
	listProjectile.push_back(bullet0);
	listProjectile.push_back(bullet1);
	listProjectile.push_back(bullet2);
	listProjectile.push_back(bullet3);
	listProjectile.push_back(bullet4);
	listProjectile.push_back(bullet5);
}


CBoss::~CBoss()
{
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//Bi danh
	if (timerRefreshAttack > 0)//doi tru mau
	{
		timerRefreshAttack--;
		if (timerRefreshAttack == 0)
			hp--;
		if (hp <= 0)
		{
			//render effect no
			CBoss::~CBoss();
		}
	}
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		listProjectile[i]->Update(dt, &listProjectile);
	}
	if (daChamDat == 0 && !onGround)
	{
		y += dy;
		// nx = -nx;
		//y = 70;
	}
	
	if (onGround == 1)
	{ 
		//y = 70;
		dx = 0;
		//dy = 0;
		//vx = -vx;
		DWORD now = GetTickCount();
		if (TimePerFly <= now - TimePrevFly)
		{
			nx = -nx;
			vx = -vx;
			TimePrevFly = now;
			CanFly = 1;
			dx = vx * dt;
			
		
		}
		else
		{
			CanFly = 0;
		}
	
	}
	else
	{
		/*DWORD now = GetTickCount();
		if (TimePerFly <= now - TimePrevFly)
		{
			TimePrevFly = now;
			CanFly = 1;
			dx = vx * dt;
		}*/

	}
	

	if ( CanFly==1)
	{
		
		{
			
			x += dx;
			y = -0.015*(x - 125)*(x - 125) + 160;
		}
	
		//SetOnGround(0);
	}
	else
	{
		
	

	}
	
	BanBullet(1);
	DebugOut(L"HP= %d, timer= %d\n", hp,timerRefreshAttack);
	//DebugOut(L"cham dat %d; onground %d ; vx %f ; nx %d\n; x:%f; y:%f", daChamDat,onGround,vx,nx,x,y);
}




void CBoss::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(218);// right
	this->AddAnimation(219);//left
	this->AddAnimation(220);// fly right
	this->AddAnimation(221);//fly left
	animations = NULL;

}

void CBoss::Render()
{
	for (UINT i = 0; i < listProjectile.size(); i++)
	{

		listProjectile[i]->Render();
		//DebugOut(L"Render sucess");
	}
	int ani;
	if (onGround)
	{
		if (nx > 0)
			ani = 0; //right
		else
			ani = 1;//left
	}
	else
	{
		if (nx > 0)
			ani = 2; //right fly
		else
			ani = 3;//left fly
	}

	
	
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	animations[ani]->Render(pos.x, pos.y, ALPHA);
	this->RenderBoundingBox(180);
}


void CBoss::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (nx > 0)
	{
		x = this->x - 5;
		width = this->width-10;
	}
	else
	{
		x = this->x +5;
		width = this->width-8;
	}
	y = this->y;
	height = this->height;
}
void CBoss::BanBullet(int x)
{
	
	if (GetTickCount() - TimePrevShoot >= 8000&& this->x<100)
	{
		if (onGround)
		{
			RefreshListBullet(0);
			RefreshListBullet(1);
			RefreshListBullet(2);
			TimePrevShoot = GetTickCount();
			return;
		}
	}
	if (GetTickCount() - TimePrevShoot >= 8000 && this->x > 100)
	{
		if (onGround)
		{
			RefreshListBullet(3);
			RefreshListBullet(4);
			RefreshListBullet(5);
			TimePrevShoot = GetTickCount();
			return;
		}
	}
}
void CBoss::BeAttack(int satThuong)
{
	
	timerRefreshAttack = 10;
}

void CBoss::DeActivate()
{
}

void CBoss::RefreshListBullet(int x)
{
		
	CBulletBoss *bullet =  dynamic_cast<CBulletBoss*>(listProjectile[x]);
	bullet->Reset();
}


	

