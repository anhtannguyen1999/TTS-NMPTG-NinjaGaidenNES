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
	CheckCollisionNinjaWithGround();
	CheckCollisionEnemyWithGroundAndVuKhi();
}

void CGameSceneStage31::CheckCollisionNinjaWithGround()
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
					if(ninja->vy<0)// Nếu có rơi xuống thì bố mới tin va chạm với đất nhé!!!Thân
						grounded = true;
					if (ninja->y - NINJA_HEIGHT_TMP > objY - 16) //cham 1 it o tren moi tinh
						ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
				}
				//DebugOut(L"%d \n", collisionCheck);
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
void CGameSceneStage31::CheckCollisionNinjaWidthEnemy()
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
				CHawk*hawk= dynamic_cast<CHawk*>(gameObj);
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

void CGameSceneStage31::CheckCollisionEnemyWithGroundAndVuKhi()
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
			if (ninja->ninjaSword->GetActive()&&enemy->isCollitionObjectWithObject(ninja->ninjaSword))
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



