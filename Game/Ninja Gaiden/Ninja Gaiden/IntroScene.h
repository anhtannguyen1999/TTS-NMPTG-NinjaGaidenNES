#pragma once
#include "GameScene.h"
#include"SceneManager.h"
class IntroScene :
	public CGameScene
{
	CSprites * sprites = CSprites::GetInstance();
public:
	CGameObject * scene;
	IntroScene();
	~IntroScene();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void PauseBackgroundSound();
};

