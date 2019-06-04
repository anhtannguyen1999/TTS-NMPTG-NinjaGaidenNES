#pragma once
#include "Enemy.h"
class CBulletBoss :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	int startX;
public:
	CBulletBoss(int id, int x, int y, int nx);
	~CBulletBoss();
	void Reset();
	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void BulletWait();//đạn đang chờ để bắn
	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat < 10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	virtual void DeActivate();

};

