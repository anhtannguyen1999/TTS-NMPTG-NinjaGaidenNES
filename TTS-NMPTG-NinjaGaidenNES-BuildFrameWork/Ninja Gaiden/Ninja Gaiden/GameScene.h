﻿#pragma once
#include "ViewPort.h"

//#include <fstream>
//#include <vector>

//#include "Grid.h"
//#include "Sound.h"
//#include "Item.h"
#include "Ninja.h"


static int score;
class CGameScene
{
protected:
	std::vector<CGameObject*> *listObject;
	CViewPort *viewPort = CViewPort::GetInstance();
	bool isChangingScene;
	bool canUseKeyboard;
	static CNinja* ninja;
	D3DXVECTOR3 ninjaCheckpoint;
public:
	CGameScene();
	~CGameScene();
	virtual void Render() {};
	virtual void Update(DWORD dt);
	virtual void DestroyAll() {};
	
	//2 cai nay dung de chuyen scene
	virtual bool GetIsChangingScene() { return isChangingScene; };
	virtual void SetIsChangingScene(bool status) { isChangingScene = status; }

	//hàm check, lưu vị trí khi ninja đi qua check point
	void CheckPoint(DWORD dt, CNinja* ninja, std::vector<CGameObject*> *list)
	{
		//...
	}
	void KeyDown(unsigned short int const &key);
	void KeyUp(unsigned short int const &key);
};

