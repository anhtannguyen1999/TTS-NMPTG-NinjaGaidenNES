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
void CGameSceneStage31::CheckCollisionNinjaWithBackGroundObj()
{
	bool grounded = false,// walled = false, 
		 stopLeft = false, stopRight = false;
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
					if(ninja->vy<0)
						ninja->vy = -0.1f; //cham la bat nguoc

					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);

					//cham 1 it o tren moi tinh
					// &&Nếu có rơi xuống thì mới tin va chạm với đất nhé!!!
					if (ninja->y - NINJA_HEIGHT_TMP > objY - 10&& ninja->vy<0)  
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

		//else if (listBackgroundObj[i]->GetType() == TYPE_WALL)
		//{
		//	CWall* wall = dynamic_cast<CWall*>(gameObj);
		//	unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
		//	if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
		//	{
		//		walled = true;
		//		//DebugOut(L"%d \n", collisionCheck);
		//		if (wall->GetMiniTypeWall() == WALL_MINITYPE_CAN_CLIMB)// Them dieu kien loai ground vao
		//		{
		//			ninja->SetState(NINJA_STATE_ON_CLIMBING_WALL);
		//			if (ninja->y - NINJA_WIDTH_TMP> wall->y)
		//			{
		//				ninja->SetPositionY(wall->y + NINJA_WIDTH_TMP);
		//			}
		//			//DebugOut(L"Cham tuong\n");
		//		}
		//		else if (wall->GetMiniTypeWall() == WALL_MINITYPE_NOT_CLIMB)
		//		{
		//			ninja->SetState(NINJA_STATE_ON_CLING_WALL);
		//		}
		//		if (collisionCheck == OBJ_COLLISION_LEFT)
		//		{
		//			//ninja->nx = -1;
		//			//stopLeft = true;
		//			ninja->SetPositionX(wall->GetRightX());
		//		}
		//		else if (collisionCheck == OBJ_COLLISION_RIGHT)
		//		{
		//			//ninja->nx = 1;
		//			//stopRight = true;
		//			ninja->SetPositionX(wall->x-NINJA_WIDTH_TMP);
		//		}
		//		
		//			
		//	}
		//}

	}
	ninja->SetOnGround(grounded);
	/*if (!walled)
	{
		ninja->SetOnWall(false);
	}*/
	if (stopLeft)
		ninja->SetState(NINJA_STATE_STOP_LEFT);
	else
		ninja->SetState(NINJA_STATE_ACTIVE_LEFT);
	if (stopRight)
		ninja->SetState(NINJA_STATE_STOP_RIGHT);
	else
		ninja->SetState(NINJA_STATE_ACTIVE_RIGHT);
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
			else if (enemy->GetTypeEnemy() == CONTAINER_MINITYPE_BUTTERFLY)
			{
				Butterfly* container = dynamic_cast<Butterfly*>(gameObj);
				if (container) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck;
					if (container->item)
					{
						//Item* item = dynamic_cast<Item*>(container->item);
						switch (container->GetItemType())
						{
							case ITEM_MINITYPE_BAGBLUE:
							{
								PointsBag* PBagBlue = dynamic_cast<PointsBag*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(PBagBlue);
								break;
							}
							case ITEM_MINITYPE_BAGRED:
							{
								PointsBagRed* PBagRed = dynamic_cast<PointsBagRed*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(PBagRed);
								break;
							}
							case ITEM_MINITYPE_SOULBLUE:
							{
								SoulBlue* SBlue = dynamic_cast<SoulBlue*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(SBlue);
								break;
							}
							case ITEM_MINITYPE_SOULRED:
							{
								SoulRed* SRed = dynamic_cast<SoulRed*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(SRed);
								break;
								
							}
							case ITEM_MINITYPE_SMALLSHURIKEN:
							{
								SShurikenItem* SShurikenI = dynamic_cast<SShurikenItem*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(SShurikenI);
								break;
							}
							case ITEM_MINITYPE_BIGSHURIKEN:
							{
								BShurikenItem* BShurikenI= dynamic_cast<BShurikenItem*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(BShurikenI);
								break;
							}
							case ITEM_MINITYPE_FIREITEM:
							{
								FireItem* FireI = dynamic_cast<FireItem*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(FireI);
								if (collisionCheck != OBJ_NO_COLLISION)
								{
									ninja->SetSpecialWeapon(WEAPON_MINITYPE_FIRES);
								}
								break;
								break;
							}
							case ITEM_MINITYPE_HEALTHPOT:
							{
								HealthPot* HPot = dynamic_cast<HealthPot*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(HPot);
								break;
							}
							case ITEM_MINITYPE_HOURGLASS:
							{
								Hourglass* HGlass = dynamic_cast<Hourglass*>(container->item);
								collisionCheck = ninja->isCollitionObjectWithObject(HGlass);
								break;
							}
							
						}
						
						
						if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						{
							//DebugOut(L"Cham Item pointBag\n");
							//Cong mau cho ninja
							//Huy 
							container->~Butterfly();
							SAFE_DELETE(container);
							gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

						}
						else //Neu khong va cham thi xem no co bi danh rot item va nam ngoai khong 
						{
							if (container->isItemNamNgoaiCamera())
							{
								container->~Butterfly();
								SAFE_DELETE(container);
								gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
							}
						}
					}
				}
			}
			else if (enemy->GetTypeEnemy() == CONTAINER_MINITYPE_BIRD)
			{
				Bird* container = dynamic_cast<Bird*>(gameObj);
				if (container) //c != nullptr //downcast thành công
				{
					unsigned short int collisionCheck;
					if (container->item)
					{
						//Item* item = dynamic_cast<Item*>(container->item);
						switch (container->GetItemType())
						{
						case ITEM_MINITYPE_BAGBLUE:
						{
							PointsBag* PBagBlue = dynamic_cast<PointsBag*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(PBagBlue);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->CongDiem(PBagBlue->GetSoDiem());
							}
							break;
						}
						case ITEM_MINITYPE_BAGRED:
						{
							PointsBagRed* PBagRed = dynamic_cast<PointsBagRed*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(PBagRed);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->CongDiem(PBagRed->GetSoDiem());
							}
							break;
						}
						case ITEM_MINITYPE_SOULBLUE:
						{
							SoulBlue* SBlue = dynamic_cast<SoulBlue*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(SBlue);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->CongMana(SBlue->GetLuongMana());
							}
							break;
						}
						case ITEM_MINITYPE_SOULRED:
						{
							SoulRed* SRed = dynamic_cast<SoulRed*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(SRed);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->CongMana(SRed->GetLuongMana());
							}
							break;

						}
						case ITEM_MINITYPE_SMALLSHURIKEN:
						{
							SShurikenItem* SShurikenI = dynamic_cast<SShurikenItem*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(SShurikenI);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->SetSpecialWeapon(WEAPON_MINITYPE_SMALL_SHURIKEN);
							}
							break;
						}
						case ITEM_MINITYPE_BIGSHURIKEN:
						{
							BShurikenItem* BShurikenI = dynamic_cast<BShurikenItem*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(BShurikenI);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->SetSpecialWeapon(WEAPON_MINITYPE_BIG_SHURIKEN);
							}
							break;
						}
						case ITEM_MINITYPE_FIREITEM:
						{
							FireItem* FireI = dynamic_cast<FireItem*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(FireI);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->SetSpecialWeapon(WEAPON_MINITYPE_FIRES);
							}
							break;
						}
						case ITEM_MINITYPE_HEALTHPOT:
						{
							HealthPot* HPot = dynamic_cast<HealthPot*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(HPot);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								ninja->CongHP(HPot->GetSoHP());
							}
							break;
						}
						case ITEM_MINITYPE_HOURGLASS:
						{
							Hourglass* HGlass = dynamic_cast<Hourglass*>(container->item);
							collisionCheck = ninja->isCollitionObjectWithObject(HGlass);
							if (collisionCheck != OBJ_NO_COLLISION)
							{
								this->pauseEnemyTimer = 500;
								
							}
							break;
						}

						}


						if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
						{
							//DebugOut(L"Cham Item pointBag\n");
							//Cong mau cho ninja
							//Huy 
							container->~Bird();
							SAFE_DELETE(container);
							gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

						}
						else //Neu khong va cham thi xem no co bi danh rot item va nam ngoai khong 
						{
							if (container->isItemNamNgoaiCamera())
							{
								container->~Bird();
								SAFE_DELETE(container);
								gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
							}
						}
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
						else if(ninja->specialWeapon)
						{
							if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
							{
								CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
								if (cross->isCollitionObjectWithObject(fires->listFires[2]))
								{
									cross->BeAttack(1);
									fires->listFires[2]->DanhChetEnemy();
								}
								else if (cross->isCollitionObjectWithObject(fires->listFires[1]))
								{
									cross->BeAttack(1);
									fires->listFires[1]->DanhChetEnemy();
								}
								else if (cross->isCollitionObjectWithObject(fires->listFires[0]))
								{
									cross->BeAttack(1);
									fires->listFires[0]->DanhChetEnemy();
								}
							}
							else if (ninja->specialWeapon->GetActive() && cross->isCollitionObjectWithObject(ninja->specialWeapon))
							{
								cross->BeAttack(1);
								//Sau nay xet neu khong phai la boss nua
								ninja->specialWeapon->DanhChetEnemy();
							}
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
						else if (ninja->specialWeapon)
						{
							if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
							{
								CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
								if (BCom->isCollitionObjectWithObject(fires->listFires[2]))
								{
									BCom->BeAttack(1);
									fires->listFires[2]->DanhChetEnemy();
								}
								else if (BCom->isCollitionObjectWithObject(fires->listFires[1]))
								{
									BCom->BeAttack(1);
									fires->listFires[1]->DanhChetEnemy();
								}
								else if (BCom->isCollitionObjectWithObject(fires->listFires[0]))
								{
									BCom->BeAttack(1);
									fires->listFires[0]->DanhChetEnemy();
								}
							}
							else if (ninja->specialWeapon->GetActive() && BCom->isCollitionObjectWithObject(ninja->specialWeapon))
							{
								BCom->BeAttack(1);
								ninja->specialWeapon->DanhChetEnemy();
							}
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
						else if (ninja->specialWeapon)
						{
							if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
							{
								CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
								if (BGun->isCollitionObjectWithObject(fires->listFires[2]))
								{
									BGun->BeAttack(1);
									fires->listFires[2]->DanhChetEnemy();
								}
								else if (BGun->isCollitionObjectWithObject(fires->listFires[1]))
								{
									BGun->BeAttack(1);
									fires->listFires[1]->DanhChetEnemy();
								}
								else if (BGun->isCollitionObjectWithObject(fires->listFires[0]))
								{
									BGun->BeAttack(1);
									fires->listFires[0]->DanhChetEnemy();
								}
							}
							else if (ninja->specialWeapon->GetActive() && BGun->isCollitionObjectWithObject(ninja->specialWeapon))
							{
								BGun->BeAttack(1);
								ninja->specialWeapon->DanhChetEnemy();
							}
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
			else if (enemy->GetTypeEnemy() == CONTAINER_MINITYPE_BUTTERFLY)
			{
				Butterfly* container = dynamic_cast<Butterfly*>(gameObj);
				if (container) //c != nullptr //downcast thành công
				{
					//unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
					
					if (container->item)
					{
						switch (container->GetItemType())
						{
						case ITEM_MINITYPE_BAGBLUE:
						{
							PointsBag* PBagBlue = dynamic_cast<PointsBag*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = PBagBlue->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											PBagBlue->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_BAGRED:
						{
							PointsBagRed* PBagRed = dynamic_cast<PointsBagRed*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = PBagRed->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											PBagRed->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SOULBLUE:
						{
							SoulBlue* SBlue = dynamic_cast<SoulBlue*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SBlue->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SBlue->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SOULRED:
						{
							SoulRed* SRed = dynamic_cast<SoulRed*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SRed->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SRed->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SMALLSHURIKEN:
						{
							SShurikenItem* SShurikenI = dynamic_cast<SShurikenItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SShurikenI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SShurikenI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_BIGSHURIKEN:
						{
							BShurikenItem* BShurikenI = dynamic_cast<BShurikenItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = BShurikenI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											BShurikenI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_FIREITEM:
						{
							FireItem* FireI = dynamic_cast<FireItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = FireI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											FireI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_HEALTHPOT:
						{
							HealthPot* HPot = dynamic_cast<HealthPot*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = HPot->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											HPot->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_HOURGLASS:
						{
							Hourglass* HGlass = dynamic_cast<Hourglass*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = HGlass->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											HGlass->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						}


						//PointsBag* BCom = dynamic_cast<PointsBag*>(container->item);
						//Commando->RefreshListBullet();
						
					}
					
				}
				//else



			}
			else if (enemy->GetTypeEnemy() == CONTAINER_MINITYPE_BIRD)
			{
				Bird* container = dynamic_cast<Bird*>(gameObj);
				if (container) //c != nullptr //downcast thành công
				{
					//unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);

					if (container->item)
					{
						switch (container->GetItemType())
						{
						case ITEM_MINITYPE_BAGBLUE:
						{
							PointsBag* PBagBlue = dynamic_cast<PointsBag*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = PBagBlue->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											PBagBlue->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_BAGRED:
						{
							PointsBagRed* PBagRed = dynamic_cast<PointsBagRed*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = PBagRed->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											PBagRed->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SOULBLUE:
						{
							SoulBlue* SBlue = dynamic_cast<SoulBlue*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SBlue->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SBlue->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SOULRED:
						{
							SoulRed* SRed = dynamic_cast<SoulRed*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SRed->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SRed->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_SMALLSHURIKEN:
						{
							SShurikenItem* SShurikenI = dynamic_cast<SShurikenItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = SShurikenI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											SShurikenI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_BIGSHURIKEN:
						{
							BShurikenItem* BShurikenI = dynamic_cast<BShurikenItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = BShurikenI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											BShurikenI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_FIREITEM:
						{
							FireItem* FireI = dynamic_cast<FireItem*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = FireI->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											FireI->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_HEALTHPOT:
						{
							HealthPot* HPot = dynamic_cast<HealthPot*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = HPot->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											HPot->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						case ITEM_MINITYPE_HOURGLASS:
						{
							Hourglass* HGlass = dynamic_cast<Hourglass*>(container->item);
							for (UINT i = 0; i < listBackgroundObj.size(); i++)
							{
								CGameObject * gameObj = listBackgroundObj[i];
								if (listBackgroundObj[i]->GetType() == TYPE_GROUND)
								{
									unsigned short int collisionCheck = HGlass->isCollitionObjectWithObject(gameObj);
									if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
									{
										if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
										{
											HGlass->SetOnGround(true);
											//DebugOut(L"Got here");
										}
									}
								}
							}
							break;
						}
						}


						//PointsBag* BCom = dynamic_cast<PointsBag*>(container->item);
						//Commando->RefreshListBullet();

					}

				}
				//else
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
			else if (ninja->specialWeapon)
			{
				if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
				{
					CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
					if (enemy->isCollitionObjectWithObject(fires->listFires[2]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(1);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[2]->DanhChetEnemy();
					}
					else if (enemy->isCollitionObjectWithObject(fires->listFires[1]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(1);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[1]->DanhChetEnemy();
					}
					else if (enemy->isCollitionObjectWithObject(fires->listFires[0]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(1);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[0]->DanhChetEnemy();
					}
				}
				else if (ninja->specialWeapon->GetActive() && enemy->isCollitionObjectWithObject(ninja->specialWeapon))
				{
					gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
					enemy->BeAttack(1);
					gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

					//Sau nay xet neu khong phai la boss nua
					ninja->specialWeapon->DanhChetEnemy();
				}
			}
			

		}

		//check va cham voi item
		

	}
}



