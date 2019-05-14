#include "SceneManager.h"



CSceneManager::CSceneManager()
{
	sceneID = 1;
}


CSceneManager::~CSceneManager()
{
	sceneID = 1;

}

void CSceneManager::LoadScene(int sceneID)
{
	switch (sceneID)
	{
	case GAME_STAGE_31:
		delete(gameScene);
		gameScene = new CGameSceneStage31();
		break;
	default:
		break;
	}
}

void CSceneManager::Render()
{
	gameScene->Render();
}

void CSceneManager::Update(DWORD dt)
{
	gameScene->Update(dt);
}

void CSceneManager::NextScene()
{
	this->sceneID++;
	this->LoadScene(sceneID);
}

void CSceneManager::PreScece()
{
	this->sceneID--;
	this->LoadScene(sceneID);
}

void CSceneManager::KeyDown(unsigned short int const & key)
{
	gameScene->KeyDown(key);
}

void CSceneManager::KeyUp(unsigned short int const &key)
{
	gameScene->KeyUp(key);
}
