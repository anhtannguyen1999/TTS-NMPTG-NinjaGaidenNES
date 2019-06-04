#pragma once
#include "Weapon.h"
class CSmallShuriken : public CWeapon
{
	static CSmallShuriken *__instance;
	//int rootX, rootY;
public:

	static CSmallShuriken * GetInstance();
	CSmallShuriken();
	~CSmallShuriken();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetPosition(float x, float y, int nx);
	virtual void BienMatKhiChamEnemy() { this->active = false; }
};

