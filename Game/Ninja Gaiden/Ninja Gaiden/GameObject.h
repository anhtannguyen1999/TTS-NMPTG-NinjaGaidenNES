#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"

#include "Camera.h"

using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

#pragma region Collison vs SweptAABB
struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;	//nx, ny để xác định hướng bị va chạm: nx =-1 là ở trái,0 : k có chạm ngang, 1: chạm ở phải
						//ny=-1: chạm trên, 0: k chạm, 1: chạm ở dưới
						// t sẽ lấy thời gian va chạm (t_entry)

	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	//so sánh xem thằng nào va chạm trước (để xét trước thôi mà CGameObject::CalcPotentialCollisions)
	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};
#pragma endregion

class CGameObject
{
public:
	int id; //Luu id obj ninja id=0
	float x;
	float y;
	float rootX, rootY, rootVX, rootVY; //Diem ban dau
	int rootNX;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;

	DWORD dt;

	int hp; //Máu
	int typeObj=0;
	vector<LPANIMATION> animations;



	//LPDIRECT3DTEXTURE9 texBoxCollision;
	CCamera *camera = CCamera::GetInstance();
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetSpeedX(float vx) { this->vx = vx; };
	void SetSpeedY(float vy) { this->vy = vy; };
	void SetPositionX(int x) { this->x = x; this->rootX = x; }
	void SetPositionY(int y) { this->y = y; this->rootY = y;}

	int GetState() { return this->state; }

	void AddAnimation(int aniId);
	int GetHP() { return this->hp; };
	int GetType() { return this->typeObj; };
	void SetType(int type) { this->typeObj = type; };
	CGameObject();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	int checkAABB(CGameObject * obj);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	~CGameObject();

	
	void SetId(int id) { this->id = id; }
	int GetID() { return this->id; }

	#pragma region Collison vs SweptAABB
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//Xét xem cái này có va chạm với vật thể khác k
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float & t, float & nx, float & ny);
	//void FilterCollision(
	//	vector<LPCOLLISIONEVENT> &coEvents,
	//	vector<LPCOLLISIONEVENT> &coEventsResult,
	//	float &min_tx,
	//	float &min_ty,
	//	float &nx,
	//	float &ny);
	////Tính toán khả năng va chạm và trả ra mảng coEvent
	//void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void RenderBoundingBox(int alpha=70);
	virtual void GetBoundingBox(float &x, float &y, float &width, float &height)=0;
	unsigned short int isCollitionObjectWithObject(CGameObject * obj);// kiểm tra bằng AABB và Sweept AABB

	

	void SetHP(int HP) { this->hp = HP; }

	void ResetVeTrangThaiDau();
	#pragma endregion
};

