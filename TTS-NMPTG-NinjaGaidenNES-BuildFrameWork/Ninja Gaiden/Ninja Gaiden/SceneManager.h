#pragma once
#include <d3dx9.h>
#include "GameScene.h"
#include "GameSceneStage31.h"
class CSceneManager
{
private:
	int sceneID;
	CGameScene* gameScene;
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
};

