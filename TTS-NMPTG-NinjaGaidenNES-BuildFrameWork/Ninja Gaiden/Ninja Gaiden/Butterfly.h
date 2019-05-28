#pragma once
#include "Enemy.h"
class Butterfly :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	int timer = 0;	  //int startX;
	int ItemID;
	int firstY = -1; //Diem Y cham dat

public:
	Butterfly(int id, int x, int y,int ItemID);
	~Butterfly();
	vector<CGameObject*> listItem;
	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);

};

