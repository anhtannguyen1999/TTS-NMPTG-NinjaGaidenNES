#pragma once
#include "GameObject.h"
class CWeapon : public CGameObject
{
protected:
	int width, height;
	bool active = false;
	//int danhChetEnemy = 0;
	int minitypeWeapon=0;
	int mana=0;
public:
	CWeapon();
	~CWeapon();
	void SetActive(bool active) { this->active = active; };
	bool GetActive() { return this->active; };
	void DanhChetEnemy();
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	void SetPosition(float x, float y, int nx);
	int GetMiniTypeWeapon() { return this->minitypeWeapon; }
	int GetManaTieuHao() { return this->mana; }
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	virtual void BienMatKhiChamEnemy() = 0;
};

