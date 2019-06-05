#pragma once
#include <d3dx9.h>
#include "GameScene.h"
#include "GameSceneStage31.h"
#include "GameSceneStage32.h"
#include "GameSceneStage33.h"
class CSceneManager
{
private:
	int sceneID;
	CGameScene * gameScene;
	static CSceneManager *__instance;
	CNinja*ninja=NULL;
public:
	CSceneManager();
	~CSceneManager();
	void LoadScene(int sceneID);
	void Render();
	void Update(DWORD dt);
	void NextScene();
	void PreScece();

	void KeyDown(unsigned short int const &key);
	void KeyUp(unsigned short int const &key);
	static CSceneManager * GetInstance();
	void LoadResource();
	void LoadResouceForNinja();
	void LoadResourceForEnemies();
	void LoadOtherResource();
};

