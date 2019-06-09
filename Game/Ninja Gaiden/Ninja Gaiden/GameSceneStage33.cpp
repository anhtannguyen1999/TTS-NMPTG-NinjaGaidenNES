#include "GameSceneStage33.h"

CGameSceneStage33::CGameSceneStage33() :CGameScene() //gọi lại cái khởi tạo của gamescene để kt con ninja
{
	//CGameScene::CGameScene();
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
	scoreboard->SetStage(3);
	Sound::getInstance()->play(DirectSound_Background3, true, true);
	//readyForNextScene = false;
	isChangingScene = false;
	boss->Reset();
	ninja->SetPositionX(125);
	ninja->SetPositionY(70);
}


CGameSceneStage33::~CGameSceneStage33()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneStage33::Update(DWORD dt)
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
	//if (!ninja->GetIsDeadth())//chưa chết thì xét va chạm
	{
		CheckCollision();
	}

	if (boss->GetHP() <= 0)
	{
		tick++;
		if (tick % 2 == 0)
		{
			tick = 0;
			scoreboard->PauseTimer(true);
			if (scoreboard->GetTimer() > 0)
			{
				//DebugOut(L"Timer: %d\n", scoreboard->GetTimer());
				ninja->CongDiem(1000);
				//if (scoreboard->GetTimer() - 1 < 0)
				scoreboard->SetTimer(scoreboard->GetTimer() - 1);
			}
			else
			{
				//readyForNextScene = true;
				isChangingScene = true;
			}
		}
		
		
	}
}

void CGameSceneStage33::Render()
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
	CheckCollisionNinjaWithBackGroundObj();
	CheckCollisionEnemyWithGroundAndVuKhi();
	CheckCollisionNinjaWidthBossAndBullet();
}
void CGameSceneStage33::CheckCollisionNinjaWidthBossAndBullet()
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
			if (boss && boss->GetHP()>0) //c != nullptr //downcast thành công
			{
				unsigned short int collisionCheck = ninja->isCollitionObjectWithObject(gameObj);
				if (collisionCheck != OBJ_NO_COLLISION) //Neu co va cham
				{
					ninja->BeAttacked(boss->GetDame(), gameObj->x);
				}
			}
			else{}
			// check voi dan cua boss
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

void CGameSceneStage33::PauseBackgroundSound()
{
	Sound::getInstance()->stop(DirectSound_Background3);
}

