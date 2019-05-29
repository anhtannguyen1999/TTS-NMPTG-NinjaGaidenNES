#include "GameSceneStage32.h"

CGameSceneStage32::CGameSceneStage32() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map2-Matrix.txt", L"ReSource\\Map2-Tiles.png");
	if (camera == NULL)
		camera = CCamera::GetInstance();
	if (gridGame == NULL)
		gridGame = new CGrid();
	gridGame->SetFile("ReSource/Map2-Objects.txt");
	gridGame->LoadGrid();
	ninja->SetPosition(1860, 200);
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
	bool grounded = false;
	//DebugOut(L"Obj collision Size: %d\n", listObj.size());
	CGameObject * gameObj;
	for (UINT i = 0; i < listBackgroundObj.size(); i++)
	{
		gameObj = listBackgroundObj[i];
		if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
		{
			unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
			if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
			{
				if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
				{
					ninja->vx *= 0.1;
					ninja->vy = -0.1f;

					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);
					if (ninja->vy < 0)// Nếu có rơi xuống thì bố mới tin va chạm với đất nhé!!!Thân
						grounded = true;
					if (ninja->y - NINJA_HEIGHT_TMP > objY - 16) //cham 1 it o tren moi tinh
						ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
				}
				//DebugOut(L"%d \n", collisionCheck);
				else if (collisionCheck == OBJ_COLLISION_LEFT)
				{
					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);
					//ninja->SetSpeedX(0);
					ninja->SetPositionX(objX +objW);
				}
				else if (collisionCheck == OBJ_COLLISION_RIGHT)
				{
					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);
					ninja->SetPositionX(objX - NINJA_WIDTH_TMP);
					//ninja->SetSpeedX(0.001f);
				}
				else {}
				if (collisionCheck == OBJ_COLLISION_TOP)
				{
					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);
					//ninja->SetState(NINJA_STATE_JUMP);
				}
			}
		}

	}
	ninja->SetOnGround(grounded);

}



