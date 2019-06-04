#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Ninja.h"
class Item :public CGameObject
{
protected:
	int typeItem;
	int width, height;
	CNinja *ninja = CNinja::GetInstance();
public:
	Item();
	~Item();

	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void GetBoundingBox(float &x, float &y, float &width, float &height);

	int GetTypeItem();
};

