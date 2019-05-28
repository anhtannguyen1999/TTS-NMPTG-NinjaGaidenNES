#include "GameScene.h"


//CNinja* CGameScene::ninja = NULL;

CGameScene::CGameScene()
{
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
