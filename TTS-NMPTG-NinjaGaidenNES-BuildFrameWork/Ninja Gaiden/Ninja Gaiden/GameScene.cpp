#include "GameScene.h"


CNinja* CGameScene::ninja = NULL;

CGameScene::CGameScene()
{
	ninja = new CNinja();
	//objects.push_back(ninja);
}


CGameScene::~CGameScene()
{
}

void CGameScene::Update(DWORD dt)
{
	//Xet de xoa toan bo enemy de load enemy man khac
}

void CGameScene::KeyDown(unsigned short int const &key)
{
	switch (key)
	{
	case UP_KEY:
	{
		break;
	}
	case DOWN_KEY:
	{
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

void CGameScene::KeyUp(unsigned short int const &key)
{
	switch (key)
	{
	case UP_KEY:
	{
		break;
	}
	case DOWN_KEY:
	{
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
