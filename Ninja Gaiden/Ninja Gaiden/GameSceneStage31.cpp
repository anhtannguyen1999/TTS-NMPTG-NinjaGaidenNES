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
	gridGame->GetListObject(listObj, camera); // lấy hết các object "còn Alive" trong vùng camera;
	
	ninja->Update(dt);
	float ninjaX = 0, ninjaY = 0;
	ninja->GetPosition(ninjaX, ninjaY);

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Update(dt, &listObj);  // đã kiểm tra "Alive" lúc lấy từ lưới ra

	if (!ninja->GetIsDeadth())//chưa chết thì xét va chạm
	{
		CheckCollision();
	}

	//Update lại tọa độ camera
	camera->Update(dt, ninjaX, ninjaY, tileMap->GetMapWidth(), tileMap->GetMapHeight());

}

void CGameSceneStage31::Render()
{
	tileMap->Render();

	for (UINT i = 0; i < listObj.size(); i++)
		listObj[i]->Render();

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
	delete(tileMap);
	//delete(ground);
	//delete(listObject);
	delete(camera);
}

void CGameSceneStage31::CheckCollision()
{
	CheckCollisionNinjaWithGround();

}

void CGameSceneStage31::CheckCollisionNinjaWithGround()
{
	bool grounded = false;
	//DebugOut(L"Obj Size: %d\n", listObj.size());

	for (UINT i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == TYPE_GROUND)
		{
			CGameObject * gameObj = listObj[i];
			unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
			if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
			{
				float objX, objY, objW, objH;
				gameObj->GetBoundingBox(objX, objY, objW, objH);
				
				if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
				{
					grounded = true;
					if (ninja->y - NINJA_HEIGHT_TMP>objY - 15) //cham 1 it o tren moi tinh
						ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
					//ninja->SetSpeedY(0);
				}

				//else if (collisionCheck == OBJ_COLLISION_LEFT)
				//{
				//	//ninja->SetSpeedX(0);
				//	//ninja->SetPositionX(objX +objW);
				//}
				//else if (collisionCheck == OBJ_COLLISION_RIGHT)
				//{
				//	//ninja->SetPositionX(objX - NINJA_WIDTH_TMP);
				//	//ninja->SetSpeedX(0);
				//}
				//else if (collisionCheck == OBJ_COLLISION_TOP){}
			}
		}
	}
	ninja->SetOnGround(grounded);

}



