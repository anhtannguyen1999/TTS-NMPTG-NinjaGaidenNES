#pragma once
#include "Enemy.h"
#include "Ninja.h"
#include <Windows.h>
#include"BulletGunner.h"

class CGunner :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
//	int startX;
	int timer = 0;
public:
	vector<CGameObject*> listProjectile;

	CGunner(int id, int x, int y);
	~CGunner();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	/*virtual void RenderShoot();*/
	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);

	void RefreshListBullet();

};


