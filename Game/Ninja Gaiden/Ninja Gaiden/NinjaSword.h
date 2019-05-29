#pragma once
#include "GameObject.h"
class CNinjaSword : public CGameObject
{
	//x,y co roi
	int width, height;
	bool active = false;
public:
	CNinjaSword();
	~CNinjaSword();
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetActive(bool active) { this->active = active; };
	bool GetActive() { return this->active; };
};

