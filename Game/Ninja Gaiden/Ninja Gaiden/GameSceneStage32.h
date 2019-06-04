#pragma once
#include "GameScene.h"

class CGameSceneStage32 :public CGameScene
{
public:
	CGameSceneStage32();
	~CGameSceneStage32();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
	void CheckCollision();
	//void CheckCollisionNinjaWithGround();
	//void CheckCollisionNinjaWidthEnemy();
	//void CheckCollisionEnemyWithGroundAndVuKhi();
};

