#pragma once
#include "Enemy.h"
#include "Ninja.h"
#include <Windows.h>
#include "Cross.h"

class CCloak :public CEnemy
{
	bool onGround = false;
	int isHit = 0;
	int daChamDat = 0;//Xet xem no da cham dat lan dau tien chua (de xet di chuyen cho enemy nay quanh cai ground)
	//int startX;
	int timer = 0;
	int firstY = -1; //Diem Y cham dat

public:
	vector<CGameObject*> listProjectile; //list cac cross

	CCloak(int id, int x, int y);
	~CCloak();

	void LoadResource();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	/*virtual void RenderShoot();*/
	void GetBoundingBox(float &x, float &y, float &width, float &height);
	void SetOnGround(bool onGround) { this->onGround = onGround; if (onGround&&daChamDat<10) daChamDat++; }
	virtual void BeAttack(int satThuong);
	void ClearListCross();
	void RefreshListCross();
};


