#pragma once
#include "GameScene.h"
#include "TileMap.h"

class CGameSceneStage31 :public CGameScene
{
	CTileMap *tileMap;
	CGrid * gridGame;
	//vector<CGameObject*> listBackgroundObj;//Luu may cai nhu ground, wall...
	//vector<CGameObject*> listOtherObj;
public:
	CGameSceneStage31();
	~CGameSceneStage31();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
	void CheckCollision();
	void CheckCollisionNinjaWithBackGroundObj();
	void CheckCollisionNinjaWidthEnemy();
	void CheckCollisionEnemyWithGroundAndVuKhi();
};

