#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Ninja.h"
#include "Effect.h"
class CEnemy :public CGameObject
{
protected:
	int typeEnemy;
	int width, height;
	int dame;
	CNinja *ninja = CNinja::GetInstance();
	CEffect *effect = CEffect::GetInstance();
	bool isPause;
public:
	CEnemy();
	~CEnemy();
	
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);

	int GetTypeEnemy();
	int GetDame();
	virtual void BeAttack(int satThuong) =0;
	virtual void DeActivate() =0;
	float GetRootX();
	float GetRootY();
	void SetIsPause(bool isPause);
};

