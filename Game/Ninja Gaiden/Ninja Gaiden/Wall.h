#pragma once
#include "GameObject.h"
class CWall : public CGameObject
{
	//x,y co roi
	int width, height;
	int minitypeWall;

public:
	CWall(int x, int y, int w, int h, int minitypeWall);
	~CWall();
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	void Render();
	int GetMiniTypeWall();
	int GetRightX();
};

