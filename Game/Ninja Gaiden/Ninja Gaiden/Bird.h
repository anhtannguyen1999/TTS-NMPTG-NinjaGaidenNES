#pragma once
#include "Enemy.h"
#include "PointsBag.h"
#include "PointsBagRed.h"
#include "BShurikenItem.h"
#include "SoulBlue.h"
#include "SoulRed.h"
#include "SShurikenItem.h"
#include "FireItem.h"
#include "HealthPot.h"
#include "Hourglass.h"
class Bird :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	int timer = 0;	  //int startX;
	int ItemType;
	int firstY = -1; //Diem Y cham dat

public:
	Bird(int id, int x, int y, int ItemID);
	~Bird();
	CGameObject* item = NULL;
	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);

	bool isItemNamNgoaiCamera();
	int GetItemType() { return this->ItemType; };
	virtual void DeActivate();

};

