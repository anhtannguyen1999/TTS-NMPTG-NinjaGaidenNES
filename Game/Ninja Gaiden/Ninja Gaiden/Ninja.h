#pragma once
#include "GameObject.h"
#include "define.h"
#include "NinjaSword.h"

class CNinja : public CGameObject
{
	static CNinja *__instance;
	bool canMove = true;
	bool canJump = true;
	bool isJump = false;
	bool isSit = false;
	bool canClimbUpDown = false; //Co 2 loai wall, 1 loai cho leo 1 loai k cho leo
	bool isOnWall = false;
	bool isUp = false;//is KeyUp
	bool isDown = false;
	int isHit = 0;
	int attacked = 0; //attacked =0 la k bi danh => co the bi danh; attack 0->12: trang thai bay khi bi danh, 12->40: trang thai nhap nhay sau do
	bool huongAttacked = true; // false la huong con enemy di nguoc Ox => ninja bay ve phia trai
	//int resetAttackedTime = 0;
	//bool canBeAttacked = true;
	//bool isSpecialHit = isUp&&isHit
	
	float ninjaJumpForce = NINJA_JUMP_FORCE;
	bool onGround = false;
	int preY = 0;

public:
	static CNinja * GetInstance();
	CNinjaSword *ninjaSword;
	CNinja() : CGameObject()
	{ 

		this->LoadResource();
		this->x =800;
		this->y = 100;
		this->hp = 20;
		this->id = 0;
		ninjaSword = new CNinjaSword();
	}
	~CNinja();
	void LoadResource();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	//Animation
	void Jump(int &ani); //Jump or Jump Hit
	void Sit(int &ani);
	void OnWall(int &ani);
	void Stand(int &ani); //Stand Idle, Stand Hit, Stand Throw, Run
	void Attacked(int &ani);

	void SetOnGround(bool onGround) { this->onGround = onGround; }
	bool GetOnGround() { return this->onGround; }

	bool GetIsDeadth() { return this->hp <= 0; };

	void GetBoundingBox(float & x, float & y, float & width, float & height);
	
	void CalNinjaSword();
	float GetPositionX();
	void BeAttacked(int dame,int xObj);
	void CongHP(int luongHP);
	
};




