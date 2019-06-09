#pragma once
#include "GameScene.h"

class CGameSceneStage31 :public CGameScene
{
	
public:
	CGameSceneStage31();
	~CGameSceneStage31();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
	void CheckCollision();
	virtual void PauseBackgroundSound();
};

