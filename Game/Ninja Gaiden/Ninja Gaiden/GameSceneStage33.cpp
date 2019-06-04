#include "GameSceneStage33.h"

CGameSceneStage33::CGameSceneStage33() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map3-Matrix.txt", L"ReSource\\Map3-Tiles.png");
	if (camera == NULL)
		camera = CCamera::GetInstance();
	if (gridGame == NULL)
		gridGame = new CGrid();
	gridGame->SetFile("ReSource/Map3-Objects.txt");
	gridGame->LoadGrid();
	ninja->SetPosition(50, 200);

	//Update lại tọa độ camera
	camera->Update(DWORD(15) , 0, 0, tileMap->GetMapWidth(), tileMap->GetMapHeight());

}


CGameSceneStage33::~CGameSceneStage33()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneStage33::Update(DWORD dt)
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
}

void CGameSceneStage33::Render()
{
	tileMap->Render();

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Render();
	for (UINT i = 0; i < listOtherObj.size(); i++)
		listOtherObj[i]->Render();
	ninja->Render();
	effect->Render();

}

bool CGameSceneStage33::GetIsChangingScene()
{
	return CGameScene::GetIsChangingScene();;
}

void CGameSceneStage33::SetIsChangingScene(bool status)
{
	CGameScene::SetIsChangingScene(status);
}

void CGameSceneStage33::DestroyAll()
{
	delete(tileMap);
	//delete(ground);
	//delete(listObject);
	delete(camera);
}

void CGameSceneStage33::CheckCollision()
{
	CheckCollisionNinjaWithGround();
	CheckCollisionEnemyWithGroundAndVuKhi();
	CheckCollisionNinjaWidthEnemy();
}
void CGameSceneStage33::CheckCollisionNinjaWidthEnemy()
{
	//Enemy được lưu trong list other obj
	for (UINT i = 0; i < listOtherObj.size(); i++)
	{
		int type = listOtherObj[i]->GetType();
		CGameObject * gameObj = listOtherObj[i];
		//check va cham voi enemy
		if (type = TYPE_ENEMY)
		{

			CBoss* boss = dynamic_cast<CBoss*>(gameObj);
			if (boss) //c != nullptr //downcast thành công
			{
				unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
				if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
				{
					ninja->BeAttacked(boss->GetDame(), gameObj->x);
				}
			}
			else{}// check voi dan cua boss
			for (UINT i = 0; i < boss->listProjectile.size(); i++)
			{
				CBulletBoss* BBoss = dynamic_cast<CBulletBoss*>(boss->listProjectile[i]);
				//boss->RefreshListBullet(i);
				int collisionCheck = ninja->isCollitionObjectWithObject(BBoss);
				if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
				{	
					//boss->RefreshListBullet(i);
					ninja->BeAttacked(BBoss->GetDame(), BBoss->x);
					BBoss->BeAttack(1);

				}
			}

		}

		//check va cham voi item
	}
}

void CGameSceneStage33::CheckCollisionNinjaWithGround()
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
					ninja->SetPositionX(objX + objW);
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

void CGameSceneStage33::CheckCollisionEnemyWithGroundAndVuKhi()
{
	for (UINT i = 0; i < listOtherObj.size(); i++)
	{
		int type = listOtherObj[i]->GetType();
		CGameObject * gameObj = listOtherObj[i];
		//check va cham voi enemy
		if (type = TYPE_ENEMY)
		{
			//Xet enemy
			CEnemy* enemy = dynamic_cast<CEnemy*>(gameObj);
			//Neu la Boss
			if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_BOSS)
			{
				CBoss* boss = dynamic_cast<CBoss*>(enemy);
				if (boss) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = boss->isCollitionObjectWithObject(gameObj);
							if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
								}
							}
						}

					}
					boss->SetOnGround(grounded);
					for (UINT i = 0; i < boss->listProjectile.size(); i++)
					{
						CBulletBoss* BBoss = dynamic_cast<CBulletBoss*>(boss->listProjectile[i]);

						if (ninja->ninjaSword->GetActive() && BBoss->isCollitionObjectWithObject(ninja->ninjaSword))
						{
							BBoss->BeAttack(1);
							ninja->ninjaSword->DanhChetEnemy();
						}
					}
				}
				//else {}
				//SAFE_DELETE();
			}




			//XetVaChamEnemy voi vu khi
			if (ninja->ninjaSword->GetActive() && enemy->isCollitionObjectWithObject(ninja->ninjaSword))
			{
				enemy->BeAttack(1);
				gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
			}

		}

	}
}



