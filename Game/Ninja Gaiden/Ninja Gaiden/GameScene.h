﻿#pragma once
#include "Camera.h"
#include "Grid.h"
#include "Ninja.h"
#include "NinjaSword.h"
#include "Effect.h"
#include "TileMap.h"
#include "ScoreBoard.h"
#include"Sound.h"
static int score;
class CGameScene
{
protected:
	//std::vector<CGameObject*> *listObject;
	vector<CGameObject*> listBackgroundObj;//Luu may cai nhu ground, wall...
	vector<CGameObject*> listOtherObj;
	CCamera *camera = CCamera::GetInstance();
	bool isChangingScene;
	CNinja*ninja = CNinja::GetInstance();
	CEffect *effect = CEffect::GetInstance();
	int pauseEnemyTimer = 0; 
	CGrid * gridGame;
	CTileMap *tileMap;
	int endSceneTimer = 0;
	CScoreBoard *scoreboard = CScoreBoard::GetInstance();
	int resetSceneTimer = 0;//reset khi ninja die
	bool resetScene = false;
	bool keyEntered = false;
public:
	CGameScene();
	~CGameScene();
	virtual void Render();
	virtual void Update(DWORD dt);
	virtual void DestroyAll() {};
	
	//2 cai nay dung de chuyen scene
	virtual bool GetIsChangingScene() { return isChangingScene; };
	virtual void SetIsChangingScene(bool status) { isChangingScene = status; }

	//hàm check, lưu vị trí khi ninja đi qua check point

	void KeyDown(unsigned short int const &key);
	void KeyUp(unsigned short int const &key);
	void CheckCollisionNinjaWithBackGroundObj();
	void CheckCollisionNinjaWidthEnemy();
	void CheckCollisionEnemyWithGroundAndVuKhi();
	void SetEndSceneEffect(bool&done );
	//virtual void ResetScene()=0;
	bool GetResetScene() { return this->resetScene; }
	virtual void PauseBackgroundSound() = 0;
};

