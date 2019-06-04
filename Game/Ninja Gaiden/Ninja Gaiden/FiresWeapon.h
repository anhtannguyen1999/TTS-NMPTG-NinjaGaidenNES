#pragma once
#include "Weapon.h"

class CFireWeapon :public CWeapon
{
	int timer=0;
public:
	CFireWeapon(float vy);
	~CFireWeapon();
	void Update(DWORD dt);
	void Render();
	void SetPosition(float x, float y, int nx);
	virtual void BienMatKhiChamEnemy() { this->active = false; };
};



class CFiresWeapon :public CWeapon
{
	
	static CFiresWeapon *__instance;
public:
	vector<CFireWeapon*> listFires;

	static CFiresWeapon * GetInstance();
	CFiresWeapon();
	~CFiresWeapon();

	void Update(DWORD dt);
	void Render();
	void SetPosition(float x, float y, int nx);
	void SetActive(bool active);
	virtual void BienMatKhiChamEnemy() {};
};

