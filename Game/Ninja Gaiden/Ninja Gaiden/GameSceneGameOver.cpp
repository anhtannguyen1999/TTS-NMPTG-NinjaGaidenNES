#include "GameSceneGameOver.h"



CGameSceneGameOver::CGameSceneGameOver() :CGameScene()
{
	keyEntered = false;
	d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	D3DXCreateFont(d3ddv, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 5, FF_DONTCARE, L"", &font);
	SetRect(&rectFont, 0, 0, 250, 200);
	ninja->SetPosition(50, 100);
}


CGameSceneGameOver::~CGameSceneGameOver()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}

void CGameSceneGameOver::Update(DWORD dt)
{
	//CGameScene::Update(dt);
	if (keyEntered && !isChangingScene)
		isChangingScene = true;
}
void CGameSceneGameOver::Render()
{

	font->DrawTextA(NULL, "Game Over", -1, &rectFont, 7, D3DCOLOR_XRGB(255, 255, 255));
}

void CGameSceneGameOver::PauseBackgroundSound()
{
	//Sound::getInstance()->stop(DirectSound_BACKGROUND1);
}



