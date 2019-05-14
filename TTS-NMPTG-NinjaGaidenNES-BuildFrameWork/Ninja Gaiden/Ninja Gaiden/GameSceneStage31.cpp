#include "GameSceneStage31.h"



CGameSceneStage31::CGameSceneStage31() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map1-Matrix.txt", L"ReSource\\Map1-Tiles.png");
	if (viewPort == NULL)
		viewPort = CViewPort::GetInstance();
}


CGameSceneStage31::~CGameSceneStage31()
{
}

void CGameSceneStage31::Update(DWORD dt)
{
	ninja->Update(dt);
	float ninjaX = 0, ninjaY = 0;
	ninja->GetPosition(ninjaX, ninjaY);
	viewPort->Update(dt, ninjaX, ninjaY, tileMap->GetMapWidth(), tileMap->GetMapHeight());
}

void CGameSceneStage31::Render()
{
	tileMap->Render();
	ninja->Render();
}

bool CGameSceneStage31::GetIsChangingScene()
{
	return CGameScene::GetIsChangingScene();;
}

void CGameSceneStage31::SetIsChangingScene(bool status)
{
	CGameScene::SetIsChangingScene(status);
}

void CGameSceneStage31::DestroyAll()
{
	//delete(ninja);
	delete(tileMap);
	//delete(ground);
	//delete(listObject);
	delete(viewPort);
}
