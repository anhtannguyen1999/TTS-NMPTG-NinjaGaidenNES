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

	float ninjaJumpForce = NINJA_JUMP_FORCE;
	bool onGround = false;
	int preY = 0;

public:
	CNinja() : CGameObject()
	{
		this->LoadResource();
		this->x =0;
		this->y = 100;
		this->hp = 10;
		this->id = 0;
	}
	~CNinja();
	void LoadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	void SetOnGround(bool onGround) { this->onGround = onGround; }
	bool GetOnGround() { return this->onGround; }

	bool GetIsDeadth() { return this->hp <= 0; };

	void GetBoundingBox(float & x, float & y, float & width, float & height);
	unsigned short int isCollitionObjectWithObject(CGameObject * obj);// kiểm tra bằng AABB và Sweept AABB
	
};




