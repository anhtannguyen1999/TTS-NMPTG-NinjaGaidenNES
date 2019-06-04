#pragma once
#include "Enemy.h"
#include "Ninja.h"
class CHawk :public CEnemy
{
	bool onGround = false;
	//int isHit = 0;
	//int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	int startX;
	int startY;
	

	//Xet giao dong cho hawk
	bool moveLeft = true; //=true la sang trai, false la sang phai
	int bienDoX = 100; //Bien do A cua giao dong lo xo theo truc x
	int tamGiaoDongX=0;
	bool moveDown = true; //=true la di xuong, false la di len
	bool dangGiaoDongX = false;
	bool vuaKhoiTao = true; //Vuawf khoiwr taoj neu vua khoi tao thi xet no move left hay move right

public:
	CHawk(int id, int x, int y);
	~CHawk();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);
	//void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	void GiaoDongQuanhNinja();
	virtual void DeActivate();

};

