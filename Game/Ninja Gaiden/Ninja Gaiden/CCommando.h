#pragma once
#include "Enemy.h"
#include "Ninja.h"
#include <Windows.h>
#include "BulletCommando.h"
class CCommando :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	//int startX;
	int timer = 0;
	int firstY = -1; //Diem Y cham dat
	CNinja *ninja = CNinja::GetInstance();
	int chamBienGround = 0; //=-1 bien trai, 0: k nam o bien, =1 bien phai
public:
	vector<CGameObject*> listProjectile;

	CCommando(int id, int x, int y);
	~CCommando();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	/*virtual void RenderShoot();*/
	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	void RefreshListBullet();
	virtual void DeActivate();
	void SetChamBien(int chamBien) { this->chamBienGround = chamBien; }
};


