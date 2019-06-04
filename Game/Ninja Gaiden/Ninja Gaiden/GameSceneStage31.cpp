#include "GameSceneStage31.h"



CGameSceneStage31::CGameSceneStage31() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map1-Matrix.txt", L"ReSource\\Map1-Tiles.png");
	if (camera == NULL)
		camera = CCamera::GetInstance();
	if(gridGame==NULL)
		gridGame = new CGrid();
	gridGame->SetFile("ReSource/Map1-Objects.txt");
	gridGame->LoadGrid();
}


CGameSceneStage31::~CGameSceneStage31()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneStage31::Update(DWORD dt)
{
	CGameScene::Update(dt);
	gridGame->GetListObject(listBackgroundObj,listOtherObj, camera); // lấy hết các object "còn Alive" trong vùng camera;
	
	ninja->Update(dt);
	float ninjaX = 0, ninjaY = 0;
	ninja->GetPosition(ninjaX, ninjaY);

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Update(dt, &listBackgroundObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listOtherObj.size(); i++)
		listOtherObj[i]->Update(dt, &listOtherObj);
	
	CheckCollision();

	//Update lại tọa độ camera
	camera->Update(dt, ninjaX, ninjaY, tileMap->GetMapWidth(), tileMap->GetMapHeight());
	
}

void CGameSceneStage31::Render()
{
	tileMap->Render();

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Render();
	for (UINT i = 0; i < listOtherObj.size(); i++) 
		listOtherObj[i]->Render();
	ninja->Render();
	effect->Render();
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
	delete(tileMap);
	//delete(ground);
	//delete(listObject);
	delete(camera);
}

void CGameSceneStage31::CheckCollision()
{
	CheckCollisionNinjaWidthEnemy();
	CheckCollisionNinjaWithBackGroundObj();
	CheckCollisionEnemyWithGroundAndVuKhi();
}



