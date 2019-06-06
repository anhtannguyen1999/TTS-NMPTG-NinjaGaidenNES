#pragma once
#include "GameObject.h"
#include "define.h"
#include "NinjaSword.h"
#include "SmallShuriken.h"
#include "BigShuriken.h"
#include "FiresWeapon.h"
class CNinja : public CGameObject
{
	static CNinja *__instance;
	bool canMove = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canJump = true;
	bool isJump = false;
	bool isSit = false;
	bool canClimbUpDown = false; //Co 2 loai wall, 1 loai cho leo 1 loai k cho leo
	bool isOnWall = false;
	bool canClingOnClimbWall = true;// khi nhay xong co the bam len tuong, khi ngoi xuong thi k the
	bool isUp = false;//is KeyUp
	bool isDown = false;
	int isHit = 0;
	int attacked = 0; //attacked =0 la k bi danh => co the bi danh; attack 0->12: trang thai bay khi bi danh, 12->40: trang thai nhap nhay sau do
	bool huongAttacked = true; // false la huong con enemy di nguoc Ox => ninja bay ve phia trai
	//int resetAttackedTime = 0;
	//bool canBeAttacked = true;
	//bool isSpecialHit = isUp&&isHit
	bool onGround = false;
	int preY = 0;
	int hpMax = 16;
	int mana = 0;
	int timeResetHit = 0;
	int point;//So diem 
public:
	static CNinja * GetInstance();
	CNinjaSword *ninjaSword=CNinjaSword::GetInstance();
	CWeapon *specialWeapon=NULL;
	CNinja() : CGameObject()
	{
		this->LoadResource();
		this->x = 10;
		this->y = 200;
		this->hp = hpMax;
		this->id = 0;
		this->mana = 1000;
		this->point = 0;
		//ninjaSword = new CNinjaSword();
		SetSpecialWeapon(WEAPON_MINITYPE_SMALL_SHURIKEN);

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

	void SetOnGround(bool onGround);
	bool GetOnGround() { return this->onGround; }
	void SetOnWall(bool onWall);
	bool GetOnWall() { return this->isOnWall; }
	bool GetIsDeadth() { return this->hp <= 0; };

	void GetBoundingBox(float & x, float & y, float & width, float & height);
	
	void CalNinjaSword();
	float GetPositionX();
	void BeAttacked(int dame,int xObj);
	void CongHP(int luongHP);
	void CongMana(int luongMana);
	void CongDiem(int luongPoint);
	void SetSpecialWeapon(int minitype);
	int GetMana() { return this->mana; }
	int GetPoint() { return this->point; }
	int GetTypeItem();
};




