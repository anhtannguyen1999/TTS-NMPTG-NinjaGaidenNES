#pragma once
#include "Enemy.h"
class CRunner :public CEnemy
{
	bool onGround = false;
	float JumpModifiers = 0.12f;
	int timer;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	//int startX;
	bool vuaKhoiTao = true;//tung cham dat khi vua khoi tao// dung de cho runner roi khi vua sinh ra
	int chamBienGround = 0; //=-1 bien trai, 0: k nam o bien, =1 bien phai

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
	void SetChamBien(int chamBien) { if(timer==0)this->chamBienGround = chamBien; }
};

