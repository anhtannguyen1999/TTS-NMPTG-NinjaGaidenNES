#include "GameSceneStage32.h"

CGameSceneStage32::CGameSceneStage32() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map2-Matrix.txt", L"ReSource\\Map2-Tiles.png");
	if (camera == NULL)
		camera = CCamera::GetInstance();
	if (gridGame == NULL)
		gridGame = new CGrid();
	gridGame->SetFile("ReSource/Map1-Objects.txt");
	gridGame->LoadGrid();
	ninja->SetPosition(5, 60);
}


CGameSceneStage32::~CGameSceneStage32()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneStage32::Update(DWORD dt)
{
	gridGame->GetListObject(listBackgroundObj, listOtherObj, camera); // lấy hết các object "còn Alive" trong vùng camera;

	ninja->Update(dt);
	float ninjaX = 0, ninjaY = 0;
	ninja->GetPosition(ninjaX, ninjaY);

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Update(dt, &listBackgroundObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	for (UINT i = 0; i < listOtherObj.size(); i++)
		listOtherObj[i]->Update(dt, &listOtherObj);
	//if (!ninja->GetIsDeadth())//chưa chết thì xét va chạm
	{
		CheckCollision();
	}

	//Update lại tọa độ camera
	camera->Update(dt, ninjaX, ninjaY, tileMap->GetMapWidth(), tileMap->GetMapHeight());

}

void CGameSceneStage32::Render()
{
	tileMap->Render();

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Render();
	for (UINT i = 0; i < listOtherObj.size(); i++)
		listOtherObj[i]->Render();
	ninja->Render();
}

bool CGameSceneStage32::GetIsChangingScene()
{
	return CGameScene::GetIsChangingScene();;
}

void CGameSceneStage32::SetIsChangingScene(bool status)
{
	CGameScene::SetIsChangingScene(status);
}

void CGameSceneStage32::DestroyAll()
{
	delete(tileMap);
	//delete(ground);
	//delete(listObject);
	delete(camera);
}

void CGameSceneStage32::CheckCollision()
{
	CheckCollisionNinjaWithGround();

}

void CGameSceneStage32::CheckCollisionNinjaWithGround()
{
	

}



