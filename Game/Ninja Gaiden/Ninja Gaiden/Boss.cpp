#include "Boss.h"

int satThuongNhanVao = 0;
CBoss *CBoss::__instance = NULL;
CBoss *CBoss::GetInstance(int id, int x, int y)
{
	if (__instance == NULL) __instance = new CBoss(id,x,y);
	return __instance;
}

CBoss::CBoss(int id, int x, int y)
{
	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_BOSS;
	this->x = x;
	this->y = y;
	this->dame = 2;
	this->hp = 16;
	this->width = 30;
	this->height = 40;
	nx = -1;
	vy = -0.05f;
	vx = -0.25f;//-0.15f;
	startX = this->x;
	rootX = this->x;
	rootY = this->y;

	TimePrevFly = GetTickCount();
	CBulletBoss *bullet0 = new CBulletBoss(2, -50, 85, 1, 50, 400);
	CBulletBoss *bullet1 = new CBulletBoss(2, -50, 70, 1, 40, 600);
	CBulletBoss *bullet2 = new CBulletBoss(2, -50, 60, 1, 30, 800);

	//CBulletBoss *bullet3 = new CBulletBoss(2, 280, 70, -1);
	//CBulletBoss *bullet4 = new CBulletBoss(2, 280, 60, -1);
	//CBulletBoss *bullet5 = new CBulletBoss(2, 280, 50, -1);

	CBulletBoss *bullet3 = new CBulletBoss(2, 280, 85, -1, 195, 400);
	CBulletBoss *bullet4 = new CBulletBoss(2, 280, 70, -1, 205, 600);
	CBulletBoss *bullet5 = new CBulletBoss(2, 280, 60, -1, 215, 800);
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
		{
			hp-=satThuongNhanVao;
			Sound::getInstance()->play(DirectSound_ENEMY_ATTACKED);
		}
			
		if (hp <= 0)
		{
			//render effect no
			DeActivate();
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
	if (hp <= 0)
		return;

	if (x < 47.54f)
	{
		x = 47.54f;
		y = 70;
	}
	if (x > 202.46f)
	{
		x = 202.46f;
		y = 70;
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
	
	//BanBullet(1);
	BanBullet(8000);
	//DebugOut(L"HP= %d, timer= %d\n", hp,timerRefreshAttack);
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
	this->AddAnimation(302);//hieu ung no khi die
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
	//this->RenderBoundingBox(180);

	
	if (hp == -100)
	{

		//pos = camera->SetPositionInViewPort(pos);
		D3DXVECTOR3 pos0, pos1, pos2, pos3;

		pos0.x = this->x - 10;
		pos0.y = this->y + 13;

		pos1.x = this->x + 14;
		pos1.y = this->y + 10;

		pos2.x = this->x - 8;
		pos2.y = this->y - 10;

		pos3.x = this->x + 14;
		pos3.y = this->y - 10;
		pos0.z = pos1.z = pos2.z = pos3.z = 0;
		pos0 = camera->SetPositionInViewPort(pos0);
		pos1 = camera->SetPositionInViewPort(pos1);
		pos2 = camera->SetPositionInViewPort(pos2);
		pos3 = camera->SetPositionInViewPort(pos3);

		animations[4]->Render(pos0.x, pos0.y, ALPHA);
		animations[ani]->Render(pos.x, pos.y, ALPHA);
		animations[4]->Render(pos1.x, pos1.y, ALPHA);

		animations[ani]->Render(pos.x, pos.y, ALPHA);

		animations[4]->Render(pos2.x, pos2.y, ALPHA);
		animations[ani]->Render(pos.x, pos.y, ALPHA);
		animations[4]->Render(pos3.x, pos3.y, ALPHA);
		//animations[4]->Render(pos.x, pos.y, ALPHA);
		//this->RenderBoundingBox();
	}


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
	
	if (GetTickCount() - TimePrevShoot >= x && this->x<100)
	{
		if (onGround&&this->nx >= 0)
		{
			RefreshListBullet(0);
			RefreshListBullet(1);
			RefreshListBullet(2);
			TimePrevShoot = GetTickCount();
			return;
		}
	}
	if (GetTickCount() - TimePrevShoot >= x && this->x > 100)
	{
		if (onGround&&this->nx<0)
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
	
	timerRefreshAttack = 10;//dung cai nay de -hp
	satThuongNhanVao = satThuong;
}

void CBoss::DeActivate()
{
	hp = -100;
	ninja->CongDiem(1000);
	//CBoss::~CBoss();
}

void CBoss::Reset()
{
	onGround = false;
	isHit = 0;
	daChamDat = 0;
	CanFly = 1;
	TimePerFly = 3000;
	TimePrevFly = 0;
	TimePrevShoot = 0;
	timerRefreshAttack = 0;
	this->x = rootX;
	this->y = rootY;
	//this->dame = 1;
	this->hp = 16;
	nx = -1;
	vy = -0.05f;
	vx = -0.15f;
}

void CBoss::RefreshListBullet(int x)
{
		
	CBulletBoss *bullet =  dynamic_cast<CBulletBoss*>(listProjectile[x]);
	bullet->Reset();
}


	

