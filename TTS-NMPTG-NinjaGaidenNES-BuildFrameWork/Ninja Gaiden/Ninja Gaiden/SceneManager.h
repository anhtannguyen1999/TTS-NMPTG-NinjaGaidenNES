#pragma once
#include <d3dx9.h>
#include "GameScene.h"
#include "GameSceneStage31.h"
#include "GameSceneStage32.h"
class CSceneManager
{
private:
	int sceneID;
	CGameScene * gameScene;
	static CSceneManager *__instance;
public:
	CSceneManager();
	~CSceneManager();
	//bool Initialize();
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

