#pragma once
#include "Enemy.h"
class CNguoiCamKiem :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua de cho enemy theo thang ninja luc khoi tao
	int firstY=-1; //Diem Y cham dat
	int chamBienGround = 0; //=-1 bien trai, 0: k nam o bien, =1 bien phai
public:
	CNguoiCamKiem(int id, int x, int y);
	~CNguoiCamKiem();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround);
	virtual void BeAttack(int satThuong);
	virtual void DeActivate();
	void SetFirstY(int fY);
	void SetChamBien(int chamBien) { this->chamBienGround = chamBien; }
};

