#pragma once
#include "Weapon.h"
//#include"Ninja.h"
class CNinjaSword : public CWeapon
{
	//x,y co roi
	
	static CNinjaSword *__instance;
	//CNinja *ninja = CNinja::GetInstance();
public:
	static CNinjaSword * GetInstance();

	CNinjaSword();
	~CNinjaSword();
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	virtual void BienMatKhiChamEnemy() {};//Khong bi bien mat
	
};

