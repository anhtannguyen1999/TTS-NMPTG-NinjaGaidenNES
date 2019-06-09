#include "CCommando.h"
#include "Sound.h"


CCommando::CCommando(int id, int x, int y)
{

	this->id = id;
	LoadResource();
	this->typeEnemy = ENEMY_MINITYPE_COMMANDO;
	this->x = x;
	this->y = y;
	this->dame = 1;
	this->hp = 1;
	this->width = 20;
	this->height = 30;
	nx = -1;
	vy = -0.3f;
	vx = -0.05f;
	//startX = this->x;
	//Gan diem ban dau
	this->rootX = this->x;
	this->rootY = this->y;
	this->rootNX = this->nx;
	this->rootVX = this->vx;
	this->rootVY = this->vy;
	this->soDiem = 200;
}


CCommando::~CCommando()
{
}

void CCommando::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hp <= 0)
		return;
	
	CGameObject::Update(dt);
	CEnemy::Update(dt);
	//DebugOut(L"onground: %d, first Y: %d\n", onGround,firstY);

	#pragma region Va cham dat va di chuyen
	if (firstY == -1)
		y += dy;
	if (onGround == true && this->firstY == -1)
		this->firstY = this->y;
	if (this->firstY != -1)//Neu da cai dat firstY
		this->y = this->firstY;

	
	//Huong toi ninja
	if (!isPause)
	{
		if (this->x > ninja->x)
		{
			vx = -0.05f;
			nx = -1;
		}
		else
		{
			vx = 0.05f;
			nx = 1;
		}
	}

	//Neu nam o bien thi dung lai
	if ((chamBienGround == 1 && nx>0)|| (chamBienGround == -1&&nx<0))
	{
		vx = 0;// -0.05f;
	}

	//neu no di ra ngoai cai bien cua no thi quay dau
	//if (!onGround&&firstY != -1)
	//{
	//	//dy = 0;
	//	if (chamBienGround == 1)//Neu nam o bien ben phai thi quay dau di ve ben trai
	//	{
	//		vx = 0;// -0.05f;
	//	}
	//	else if(chamBienGround == -1)
	//	{
	//		vx = 0;//0.05f;
	//	}
	//}



	x += dx;
	#pragma endregion


	if(!isPause)
		timer++;
	if (timer >= 150)
	{
		timer = 0;
	}
	
	//Thoi gian ban sung
	if (timer >= 50 && timer <= 90)
	{
		if (timer == 50)
		{
			CBulletCommando *Cbu = new CBulletCommando(3, this->x, this->y, this->nx);
			listProjectile.push_back(Cbu);
			Sound::getInstance()->play(DIRECTSOUND_ENEMY_COMMANDO);
		}
		else if (timer == 62)
		{
			CBulletCommando *Cbu1 = new CBulletCommando(3, this->x, this->y, this->nx);
			listProjectile.push_back(Cbu1);
		}
		else if (timer == 74)
		{
			CBulletCommando *Cbu2 = new CBulletCommando(3, this->x, this->y, this->nx);
			listProjectile.push_back(Cbu2);
		}
		vx = 0;
	}

	//Update dan
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		listProjectile[i]->Update(dt, &listProjectile);
	}
	//DebugOut(L"So dan: %d \n", listProjectile.size());
}




void CCommando::LoadResource()
{
	//Khong can add hinh vi da add trong class texture lucs khoi tao roi
	//Xem trong cai LoadResource cua S

	CAnimations * animations = CAnimations::GetInstance();

	this->AddAnimation(240);// right
	this->AddAnimation(242);
	this->AddAnimation(241);//left
	this->AddAnimation(243);
	animations = NULL;

}

void CCommando::Render()
{
	if (hp <= 0)
		return;
	int ani;
	/*int ani2;*/
	if (nx > 0)
	{
		ani = 0; //right
		if (timer >= 50 && timer <90)
		{
			ani = 1;
		}
	}
	else
	{
		ani = 2;
		if (timer >= 50 && timer <90)
		{
			ani = 3;
		}
	}
	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos);
	if (isPause)
		animations[ani]->ResetCurrentFrame();
	animations[ani]->Render(pos.x, pos.y, ALPHA);

	//Render dan
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		listProjectile[i]->Render();
		//DebugOut(L"Render sucess");
	}

	//this->RenderBoundingBox();
}

void CCommando::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	if (hp <= 0)
		return;
	x = this->x;
	y = this->y-2;
	width = this->width;
	height = this->height;
}

void CCommando::BeAttack(int satThuong)
{
	CEnemy::BeAttack(satThuong);
	this->effect->RenderEffect(0, this->x, this->y);
	DeActivate();
}

void CCommando::DeActivate()
{
	hp = 0;
	for (UINT i = 0; i < listProjectile.size(); i++)
	{
		SAFE_DELETE(listProjectile[i]);
	}
	listProjectile.clear();
	ResetVeTrangThaiDau();
}

void CCommando::RefreshListBullet()
{
	int i = 0;
	while (i < listProjectile.size())//Neu hp=0 thi huy
	{
		if (listProjectile[i]->GetHP() == 0) {
			listProjectile.erase(listProjectile.begin() + i);
			i--;
		}
		i++;
	}
}

