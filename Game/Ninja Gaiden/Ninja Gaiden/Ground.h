#pragma once
#include "GameObject.h"

class CGround : public CGameObject
{
	//x,y co roi
	int width, height;
	int minitypeGround;
public:
	CGround(int x,int y, int w, int h, int minitypeGround = GROUND_MINITYPE_CAN_MOVE_HORIZONTAL);
	~CGround();
	void GetBoundingBox(float & x, float & y, float & width, float & height);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	void Render();
	int GetMiniTypeGround();
};

