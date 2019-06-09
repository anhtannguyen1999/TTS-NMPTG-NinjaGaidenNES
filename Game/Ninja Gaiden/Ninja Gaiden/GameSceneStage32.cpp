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
	ninja->SetPosition(5, 60);
	scoreboard->SetStage(2);
	Sound::getInstance()->play(DirectSound_Background2, true, true);
	ninja->SetPositionX(50);
	ninja->SetPositionY(100);
}


CGameSceneStage32::~CGameSceneStage32()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneStage32::Update(DWORD dt)
{
	CGameScene::Update(dt);
	gridGame->GetListObject(listBackgroundObj, listOtherObj, camera); // lấy hết các object "còn Alive" trong vùng camera;

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

void CGameSceneStage32::Render()
{
	CGameScene::Render();
	tileMap->Render();

	for (UINT i = 0; i < listBackgroundObj.size(); i++)
		listBackgroundObj[i]->Render();
	for (UINT i = 0; i < listOtherObj.size(); i++)
		listOtherObj[i]->Render();
	ninja->Render();
	effect->Render();

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
	CheckCollisionNinjaWidthEnemy();
	CheckCollisionNinjaWithBackGroundObj();
	CheckCollisionEnemyWithGroundAndVuKhi();
}

void CGameSceneStage32::PauseBackgroundSound()
{
	Sound::getInstance()->stop(DirectSound_Background2);
}


/*
void CGameSceneStage32::CheckCollisionNinjaWithGround()
{
	bool grounded = false, stopLeft = false, stopRight = false, walled = false;
	//DebugOut(L"Obj collision Size: %d\n", listObj.size());
	CGameObject * gameObj;
	for (UINT i = 0; i < listBackgroundObj.size(); i++)
	{
		gameObj = listBackgroundObj[i];
		if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
		{
			CGround* ground = dynamic_cast<CGround*>(gameObj);
			unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
			if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
			{
				if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
				{
					ninja->vx *= 0.1;
					if (ninja->vy<0)
						ninja->vy = -0.1f; //cham la bat nguoc

					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);

					//cham 1 it o tren moi tinh
					// &&Nếu có rơi xuống thì mới tin va chạm với đất nhé!!!
					if (ninja->y - NINJA_HEIGHT_TMP > objY - 10 && ninja->vy<0)
					{
						ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
						grounded = true;
					}

				}
				//DebugOut(L"%d \n", collisionCheck);
				else if (collisionCheck == OBJ_COLLISION_LEFT&&ground->GetMiniTypeGround() == GROUND_MINITYPE_NOT_MOVE_HORIZONTAL)// Them dieu kien loai ground vao
				{
					stopLeft = true;
				}
				else if (collisionCheck == OBJ_COLLISION_RIGHT&&ground->GetMiniTypeGround() == GROUND_MINITYPE_NOT_MOVE_HORIZONTAL)
				{
					stopRight = true;
				}
				//else if (collisionCheck == OBJ_COLLISION_TOP){}
			}
		}
		else if (listBackgroundObj[i]->GetType() == TYPE_WALL)
		{
			CWall* wall = dynamic_cast<CWall*>(gameObj);
			unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
			if ((collisionCheck == OBJ_COLLISION_LEFT&&ninja->nx<0)|| (collisionCheck == OBJ_COLLISION_RIGHT&&ninja->nx>0)) //Neu co va cham
			{
				walled = true;
				//DebugOut(L"%d \n", collisionCheck);
				if (wall->GetMiniTypeWall() == WALL_MINITYPE_CAN_CLIMB)// Them dieu kien loai ground vao
				{
					ninja->SetState(NINJA_STATE_ON_CLIMBING_WALL);
					if (ninja->y - NINJA_WIDTH_TMP> wall->y)
					{
						ninja->SetPositionY(wall->y + NINJA_WIDTH_TMP);
					}
					//DebugOut(L"Cham tuong\n");
				}
				else if (wall->GetMiniTypeWall() == WALL_MINITYPE_NOT_CLIMB)
				{
					ninja->SetState(NINJA_STATE_ON_CLING_WALL);
				}
				//Neu tuong chi cho phep leo ben phai && va cham o ben phai tuong (trai ninja)
				else if (wall->GetMiniTypeWall() == WALL_MINITYPE_NOT_CLIMB_DEACTIVATE_LEFT &&collisionCheck== OBJ_COLLISION_LEFT)
				{
					ninja->SetState(NINJA_STATE_ON_CLING_WALL);
				}
				else if (wall->GetMiniTypeWall() == WALL_MINITYPE_NOT_CLIMB_DEACTIVATE_RIGHT &&collisionCheck == OBJ_COLLISION_RIGHT)
				{
					ninja->SetState(NINJA_STATE_ON_CLING_WALL);
				}

				//Neu cham ben (trai ninja) phai cua tuong va khong phai la tuong bi deactivate ben phai
				if (collisionCheck == OBJ_COLLISION_LEFT&&wall->GetMiniTypeWall() != WALL_MINITYPE_NOT_CLIMB_DEACTIVATE_RIGHT)
				{
					//ninja->nx = -1;
					//stopLeft = true;
					ninja->SetPositionX(wall->GetRightX());
				}
				//Neu cham ben (phai ninja) trai cua tuong va khong phai la tuong bi deactivate ben trai
				else if (collisionCheck == OBJ_COLLISION_RIGHT && wall->GetMiniTypeWall() != WALL_MINITYPE_NOT_CLIMB_DEACTIVATE_LEFT)
				{
					//ninja->nx = 1;
					//stopRight = true;
					ninja->SetPositionX(wall->x - NINJA_WIDTH_TMP);
				}


			}
		}

	}
	ninja->SetOnGround(grounded);
	if (!walled)
	{
		ninja->SetOnWall(false);
	}
	if (stopLeft)
		ninja->SetState(NINJA_STATE_STOP_LEFT);
	else
		ninja->SetState(NINJA_STATE_ACTIVE_LEFT);
	if (stopRight)
		ninja->SetState(NINJA_STATE_STOP_RIGHT);
	else
		ninja->SetState(NINJA_STATE_ACTIVE_RIGHT);
}
void CGameSceneStage32::CheckCollisionNinjaWidthEnemy()
{
	//Enemy được lưu trong list other obj
	for (UINT i = 0; i < listOtherObj.size(); i++)
	{
		int type = listOtherObj[i]->GetType();
		CGameObject * gameObj = listOtherObj[i];
		//check va cham voi enemy
		if (type = TYPE_ENEMY)
		{
			CEnemy* enemy = dynamic_cast<CEnemy*>(gameObj);
			//Neu la NguoiCamKiem
			if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_NGUOICAMKIEM)
			{
				CNguoiCamKiem* nguoiCamKiem = dynamic_cast<CNguoiCamKiem*>(gameObj);
				if (nguoiCamKiem) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(nguoiCamKiem->GetDame(), gameObj->x);
					}
				}
				//else {}//p ko trỏ tới Child mà có thể là OtherChild khác.
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_HAWK)
			{
				CHawk*hawk = dynamic_cast<CHawk*>(gameObj);
				if (hawk)
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(hawk->GetDame(), gameObj->x);
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_PANTHER)
			{
				CPanther* panther = dynamic_cast<CPanther*>(gameObj);
				if (panther) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(panther->GetDame(), gameObj->x);
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_BAT)
			{
				CBat* bat = dynamic_cast<CBat*>(gameObj);
				if (bat) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(bat->GetDame(), gameObj->x);
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_CLOAK)
			{
				CCloak* cloak = dynamic_cast<CCloak*>(gameObj);
				if (cloak) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(cloak->GetDame(), gameObj->x);
					}
					//Xet va cham voi cross
					for (UINT i = 0; i < cloak->listProjectile.size(); i++)
					{
						CCross* cross = dynamic_cast<CCross*>(cloak->listProjectile[i]);
						cloak->RefreshListCross();
						collisionCheck = ninja->isCollitionObjectWithObject(cross);
						if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						{
							ninja->BeAttacked(cross->GetDame(), cross->x);

						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_COMMANDO)
			{
				CCommando* Commando = dynamic_cast<CCommando*>(gameObj);
				if (Commando) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(Commando->GetDame(), gameObj->x);
					}
					//Xet va cham voi dan cua commando
					for (UINT i = 0; i < Commando->listProjectile.size(); i++)
					{
						CBulletCommando* BCom = dynamic_cast<CBulletCommando*>(Commando->listProjectile[i]);
						Commando->RefreshListBullet();
						collisionCheck = ninja->isCollitionObjectWithObject(BCom);
						if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						{
							ninja->BeAttacked(BCom->GetDame(), BCom->x);

						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_GUNNER)
			{
				CGunner* gunner = dynamic_cast<CGunner*>(gameObj);
				if (gunner) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(gunner->GetDame(), gameObj->x);
					}
					//Xet va cham voi dan cua gunner
					for (UINT i = 0; i < gunner->listProjectile.size(); i++)
					{
						CBulletGunner* BGun = dynamic_cast<CBulletGunner*>(gunner->listProjectile[i]);
						gunner->RefreshListBullet();
						collisionCheck = ninja->isCollitionObjectWithObject(BGun);
						if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						{
							ninja->BeAttacked(BGun->GetDame(), BGun->x);

						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_RUNNER)
			{
				CRunner* CRunner1 = dynamic_cast<CRunner*>(gameObj);
				if (CRunner1) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
					{
						ninja->BeAttacked(CRunner1->GetDame(), gameObj->x);
					}
				}
			}



		}

		//check va cham voi item
	}
}

void CGameSceneStage32::CheckCollisionEnemyWithGroundAndVuKhi()
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
			//Neu la NguoiCamKiem
			if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_NGUOICAMKIEM)
			{
				CNguoiCamKiem* nguoiCamKiem = dynamic_cast<CNguoiCamKiem*>(enemy);
				if (nguoiCamKiem) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = nguoiCamKiem->isCollitionObjectWithObject(gameObj);
							if (collisionCheck == OBJ_COLLISION_BOTTOM) //Neu co va cham voi dat
							{
								grounded = true;
							}
						}

					}

					if (grounded)
					{
						nguoiCamKiem->SetOnGround(true);
						nguoiCamKiem->SetFirstY(gameObj->y);
					}
					else
						nguoiCamKiem->SetOnGround(false);
				}
				//else {}
				//SAFE_DELETE(nguoiCamKiem);
			}
			//Neu la panther
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_PANTHER)
			{
				CPanther* panther = dynamic_cast<CPanther*>(enemy);
				if (panther) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = panther->isCollitionObjectWithObject(gameObj);
							if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
								}

							}
						}

					}
					panther->SetOnGround(grounded);
				}
				//else {} enemy khacs
				//SAFE_DELETE(nguoiCamKiem);
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_CLOAK)
			{
				CCloak* Cloak = dynamic_cast<CCloak*>(enemy);
				if (Cloak) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = Cloak->isCollitionObjectWithObject(gameObj);
							if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
								}
							}
						}

					}
					Cloak->SetOnGround(grounded);

					//Xet va cham cross vs ninjaSWORD 
					Cloak->RefreshListCross();
					for (UINT i = 0; i < Cloak->listProjectile.size(); i++)
					{
						CCross* cross = dynamic_cast<CCross*>(Cloak->listProjectile[i]);
						//unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(cross);
						//if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						//{
						//	ninja->BeAttacked(cross->GetDame(), cross->x);
						//}
						if (ninja->ninjaSword->GetActive() && cross->isCollitionObjectWithObject(ninja->ninjaSword))
						{
							cross->BeAttack(1);
							//Sau nay xet neu khong phai la boss nua
							ninja->ninjaSword->DanhChetEnemy();
						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_COMMANDO)
			{
				CCommando* Commando = dynamic_cast<CCommando*>(enemy);
				if (Commando) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = Commando->isCollitionObjectWithObject(gameObj);
							if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
								}
							}
						}

					}
					Commando->SetOnGround(grounded);
					//Xet va cham bullet commando vs ninjaSWORD 
					Commando->RefreshListBullet();
					for (UINT i = 0; i < Commando->listProjectile.size(); i++)
					{
						CBulletCommando* BCom = dynamic_cast<CBulletCommando*>(Commando->listProjectile[i]);

						if (ninja->ninjaSword->GetActive() && BCom->isCollitionObjectWithObject(ninja->ninjaSword))
						{
							BCom->BeAttack(1);
							ninja->ninjaSword->DanhChetEnemy();
						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_GUNNER)
			{
				CGunner* gunner = dynamic_cast<CGunner*>(enemy);
				if (gunner) //c != nullptr //downcast thành công
				{
					//Xet va cham bullet Gunner vs ninjaSWORD 
					gunner->RefreshListBullet();
					for (UINT i = 0; i < gunner->listProjectile.size(); i++)
					{
						CBulletGunner* BGun = dynamic_cast<CBulletGunner*>(gunner->listProjectile[i]);

						if (ninja->ninjaSword->GetActive() && BGun->isCollitionObjectWithObject(ninja->ninjaSword))
						{
							BGun->BeAttack(1);
							ninja->ninjaSword->DanhChetEnemy();
						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == ENEMY_MINITYPE_RUNNER)
			{
				CRunner* CRunner1 = dynamic_cast<CRunner*>(enemy);
				if (CRunner1) //c != nullptr //downcast thành công
				{
					bool grounded = false;

					for (UINT i = 0; i < listBackgroundObj.size(); i++)
					{
						CGameObject * gameObj = listBackgroundObj[i];
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
						{
							unsigned short int collisionCheck = CRunner1->isCollitionObjectWithObject(gameObj);
							if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
								}
							}
						}

					}
					CRunner1->SetOnGround(grounded);
				}
				//else {}
				//SAFE_DELETE(nguoiCamKiem);
			}

			//else










			//XetVaChamEnemy voi vu khi
			if (ninja->ninjaSword->GetActive() && enemy->isCollitionObjectWithObject(ninja->ninjaSword))
			{
				gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
				enemy->BeAttack(1);
				gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

				//Sau nay xet neu khong phai la boss nua
				ninja->ninjaSword->DanhChetEnemy();
			}


		}

		//check va cham voi item


	}
}
*/



