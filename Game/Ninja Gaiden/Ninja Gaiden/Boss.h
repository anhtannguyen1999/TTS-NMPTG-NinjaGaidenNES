#pragma once
#include "Enemy.h"
#include "BulletBoss.h"
class CBoss :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	int startX;
	int CanFly=1;
	DWORD TimePerFly = 3000 ;
	DWORD TimePrevFly=0;
	DWORD TimePrevShoot = 0;//thời gian bắn lần trước
	int timerRefreshAttack = 0;
	static CBoss *__instance;
public:
	CBoss(int id, int x, int y);
	~CBoss();
	static CBoss * GetInstance(int id=2, int x=190, int y=100);
	vector<CGameObject*> listProjectile;
	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat < 10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	void BanBullet(int x);
	void RefreshListBullet(int x);
	virtual void DeActivate();
	
};

