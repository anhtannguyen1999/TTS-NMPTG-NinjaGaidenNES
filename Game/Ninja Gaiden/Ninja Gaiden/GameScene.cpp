#include "GameScene.h"

//CNinja* CGameScene::ninja = NULL;

CGameScene::CGameScene()
{
	
}


CGameScene::~CGameScene()
{
}

void CGameScene::Render()
{
	scoreboard->Render();
}

void CGameScene::Update(DWORD dt)
{
	if (endSceneTimer)
	{
		endSceneTimer--;
		if (endSceneTimer==0)
			CSprites::GetInstance()->SetSamMau(0);
		else if (endSceneTimer<50)
			CSprites::GetInstance()->SetSamMau(80);//130
		else if (endSceneTimer<100)
			CSprites::GetInstance()->SetSamMau(60);
		else if (endSceneTimer<150)
			CSprites::GetInstance()->SetSamMau(5); 
	}
	if (pauseEnemyTimer)
	{
		pauseEnemyTimer--;
		
		for (UINT j = 0; j < listOtherObj.size(); j++)
		{
			//CGameObject * obj = listOtherObj[j];
			if (listOtherObj[j]->GetType() == TYPE_ENEMY)
			{
				CEnemy*ene = dynamic_cast<CEnemy*>(listOtherObj[j]);
				if (ene->GetTypeEnemy() != CONTAINER_MINITYPE_BUTTERFLY&&ene->GetTypeEnemy() != CONTAINER_MINITYPE_BIRD)
				{
					
						ene->SetIsPause(true);
				}
			}

		}
	}
	else
	{
		for (UINT j = 0; j < listOtherObj.size(); j++)
		{
			//CGameObject * obj = listOtherObj[j];
			if (listOtherObj[j]->GetType() == TYPE_ENEMY)
			{
				CEnemy*ene = dynamic_cast<CEnemy*>(listOtherObj[j]);
				if (ene->GetTypeEnemy() != CONTAINER_MINITYPE_BUTTERFLY&&ene->GetTypeEnemy() != CONTAINER_MINITYPE_BIRD)
				{
					ene->SetIsPause(false);
				}
			}

		}
	}
	//Xet de xoa toan bo enemy de load enemy man khac

	scoreboard->Update(dt);
}

void CGameScene::KeyDown(unsigned short int const &key)
{
	if (endSceneTimer != 0)
		return;
	switch (key)
	{
		case UP_KEY:
		{
			ninja->SetState(NINJA_STATE_UP);
			break;
		}
		case DOWN_KEY:
		{
			ninja->SetState(NINJA_STATE_DOWN);
			break;
		}
		case LEFT_KEY:
		{
			ninja->SetState(NINJA_STATE_RUN_LEFT);
			break;
		}
		case RIGHT_KEY:
		{
			ninja->SetState(NINJA_STATE_RUN_RIGHT);
			break;
		}
		case DIK_SPACE:
			ninja->SetState(NINJA_STATE_JUMP);
			break;
		case A_KEY:
			ninja->SetState(NINJA_STATE_HIT);
			break;
		case L_KEY:
			ninja->SetState(NINJA_STATE_ON_CLIMBING_WALL);
			break;
		case D_KEY:
			ninja->SetState(NINJA_STATE_ATTACKED);
			break;
		default:
			ninja->SetState(NINJA_STATE_IDLE);
			break;
	}
	
}

void CGameScene::KeyUp(unsigned short int const &key)
{
	if (endSceneTimer != 0)
		return;
	switch (key)
	{
	case UP_KEY:
	{
		//ninja->SetIsUp(false);
		break;
	}
	case DOWN_KEY:
	{
//		ninja->SetIsDown(false);
		break;
	}
	case LEFT_KEY:
	{
		ninja->SetState(NINJA_STATE_RUN_LEFT);
		break;
	}
	case RIGHT_KEY:
	{
		ninja->SetState(NINJA_STATE_RUN_RIGHT);
		break;
	}
	default:
		ninja->SetState(NINJA_STATE_IDLE);
		break;
	}
}

void CGameScene::CheckCollisionNinjaWithBackGroundObj()
{
	bool grounded = false, walled = false,
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
					if (ninja->vy<0)
						ninja->vy = -0.1f; //cham la bat nguoc

					float objX, objY, objW, objH;
					gameObj->GetBoundingBox(objX, objY, objW, objH);

					//cham 1 it o tren moi tinh
					// &&Nếu có rơi xuống thì mới tin va chạm với đất nhé!!!
					if (ninja->y - NINJA_HEIGHT_TMP > objY - 10 && ninja->vy<0&& ground->GetMiniTypeGround()!= GROUND_MINITYPE_GREEN_SPECIAL)
					{
						ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
						grounded = true;
					}
					//Neu cham vao mieng go mau xanh
					else if (ninja->y - NINJA_HEIGHT_TMP > objY - 10 && ninja->vy < 0 && ground->GetMiniTypeGround() == GROUND_MINITYPE_GREEN_SPECIAL)
					{
						//Neu khong leo tuong thi moi xet cham dat
						if (!ninja->GetOnWall())
						{
							ninja->SetPositionY(objY + NINJA_HEIGHT_TMP);
							grounded = true;
						}
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
			if ((collisionCheck == OBJ_COLLISION_LEFT&&ninja->nx<0) || (collisionCheck == OBJ_COLLISION_RIGHT&&ninja->nx>0)) //Neu co va cham
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
				else if (wall->GetMiniTypeWall() == WALL_MINITYPE_NOT_CLIMB_DEACTIVATE_LEFT &&collisionCheck == OBJ_COLLISION_LEFT)
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
	/*if (!walled)
	{
	ninja->SetOnWall(false);
	}*/
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

void CGameScene::CheckCollisionNinjaWidthEnemy()
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
							if (container->GetItemType() == ITEM_MINITYPE_HEALTHPOT)
							{
								Sound::getInstance()->play(DirectSound_OBTAIN_HEALTHPOT);
							}
							else {
								Sound::getInstance()->play(DirectSound_OBTAIN_ITEM);
							}
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
							if (container->GetItemType() == ITEM_MINITYPE_HEALTHPOT)
							{
								Sound::getInstance()->play(DirectSound_OBTAIN_HEALTHPOT);
							}
							else {
								Sound::getInstance()->play(DirectSound_OBTAIN_ITEM);
							}
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


void CGameScene::CheckCollisionEnemyWithGroundAndVuKhi()
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
								nguoiCamKiem->SetChamBien(nguoiCamKiem->isNamTaiMepGround(gameObj));
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
									panther->SetChamBien(panther->isNamTaiMepGround(gameObj));
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
									Cloak->SetChamBien(Cloak->isNamTaiMepGround(gameObj));
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
						else if (ninja->specialWeapon)
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
									Commando->SetChamBien(Commando->isNamTaiMepGround(gameObj));
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
						CGround *ground = dynamic_cast<CGround*>(gameObj);
						if (listBackgroundObj[i]->GetType() == TYPE_GROUND 
							&& dynamic_cast<CGround*>(gameObj)->GetMiniTypeGround()!= GROUND_MINITYPE_GREEN_SPECIAL)
						{
							unsigned short int collisionCheck = CRunner1->isCollitionObjectWithObject(gameObj);
							if (!collisionCheck == OBJ_NO_COLLISION) //Neu co va cham
							{
								if (collisionCheck == OBJ_COLLISION_BOTTOM) // có va chạm xảy ra với nền đất
								{
									grounded = true;
									CRunner1->SetChamBien(CRunner1->isNamTaiMepGround(gameObj));
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

						else if (ninja->specialWeapon)
						{
							if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
							{
								CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
								if (BBoss->isCollitionObjectWithObject(fires->listFires[2]))
								{
									BBoss->BeAttack(1);
									fires->listFires[2]->DanhChetEnemy();
								}
								else if (BBoss->isCollitionObjectWithObject(fires->listFires[1]))
								{
									BBoss->BeAttack(1);
									fires->listFires[1]->DanhChetEnemy();
								}
								else if (BBoss->isCollitionObjectWithObject(fires->listFires[0]))
								{
									BBoss->BeAttack(1);
									fires->listFires[0]->DanhChetEnemy();
								}
							}
							else if (ninja->specialWeapon->GetActive() && BBoss->isCollitionObjectWithObject(ninja->specialWeapon))
							{
								BBoss->BeAttack(1);
								ninja->specialWeapon->DanhChetEnemy();
							}
						}
					}
				}
			}
			//else










			//XetVaChamEnemy voi vu khi
			if (ninja->ninjaSword->GetActive() && enemy->isCollitionObjectWithObject(ninja->ninjaSword))
			{
				gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
				enemy->BeAttack(1);
				gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

				//Sau nay xet neu khong phai la boss nua
				//if(enemy->GetTypeEnemy!=ENEMY_MINITYPE_BOSS)
				ninja->ninjaSword->DanhChetEnemy();
				ninja->CongDiem(enemy->GetSoDiem());
			}
			else if (ninja->specialWeapon)
			{
				if (ninja->specialWeapon->GetMiniTypeWeapon() == WEAPON_MINITYPE_FIRES&&ninja->specialWeapon->GetActive())
				{
					
					CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(ninja->specialWeapon);
					if (enemy->isCollitionObjectWithObject(fires->listFires[2]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(3);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[2]->DanhChetEnemy();
						ninja->CongDiem(enemy->GetSoDiem());
					}
					else if (enemy->isCollitionObjectWithObject(fires->listFires[1]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(3);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[1]->DanhChetEnemy();
						ninja->CongDiem(enemy->GetSoDiem());
					}
					else if (enemy->isCollitionObjectWithObject(fires->listFires[0]))
					{
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						enemy->BeAttack(3);
						gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
						fires->listFires[0]->DanhChetEnemy();
						ninja->CongDiem(enemy->GetSoDiem());
					}
				}
				else if (ninja->specialWeapon->GetActive() && enemy->isCollitionObjectWithObject(ninja->specialWeapon))
				{
			
					gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);
					enemy->BeAttack(1);
					gridGame->GetListObject(listBackgroundObj, listOtherObj, camera);

					ninja->specialWeapon->DanhChetEnemy();
					ninja->CongDiem(enemy->GetSoDiem());
				}
			}


		}

		//check va cham voi item


	}
}

void CGameScene::SetEndSceneEffect(bool&done)
{
	if (endSceneTimer == 0)
	{
		if (done)
		{
			pauseEnemyTimer = 150;
			endSceneTimer = 150;
			ninja->SetState(NINJA_STATE_IDLE);
		}
		done = !done;
		
	}
	
}
