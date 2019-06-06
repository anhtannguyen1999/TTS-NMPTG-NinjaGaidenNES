#pragma once
#include "Enemy.h"
class CRunner :public CEnemy
{
	bool onGround = false;
	float JumpModifiers = 0.2f;
	int timer;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	//int startX;
	bool vuaKhoiTao = true;//tung cham dat khi vua khoi tao// dung de cho runner roi khi vua sinh ra
	
public:
	CRunner(int id, int x, int y);
	~CRunner();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	virtual void DeActivate();

};

