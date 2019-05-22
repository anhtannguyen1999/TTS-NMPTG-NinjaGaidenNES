#pragma once
#include "GameObject.h"
//#include"Ninja.h"
class CNinjaSword : public CGameObject
{
	//x,y co roi
	int width, height;
	bool active = false;
	int danhChetEnemy = 0;
	static CNinjaSword *__instance;
	//CNinja *ninja = CNinja::GetInstance();
public:
	static CNinjaSword * GetInstance();

	CNinjaSword();
	~CNinjaSword();
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetPosition(float x, float y, int nx);
	void SetActive(bool active) { this->active = active; };
	bool GetActive() { return this->active; };
	void DanhChetEnemy() {this->danhChetEnemy = 1;}
};

