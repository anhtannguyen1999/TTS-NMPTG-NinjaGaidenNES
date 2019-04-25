#pragma once
#include "GameObject.h"
#include "define.h"

class CNinja : public CGameObject
{
	bool canJump = true;
	bool isJump = false;
	bool isSit = false;
	bool isClimb = false;
	bool isHit = false;
	bool isSpecialHit = false;
	//float ninjaWalkingSpeed = 2.0f;
	float ninjaJumpForce = 0.6f;
	
	//bool 
public:
	CNinja() : CGameObject()
	{
		this->LoadResource();
		this->x =0;
		this->y = 36+16*2;
	}
	~CNinja();
	void LoadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
};




