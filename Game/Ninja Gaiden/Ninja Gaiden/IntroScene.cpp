#include "IntroScene.h"



IntroScene::IntroScene()
{
	keyEntered = false;
}


IntroScene::~IntroScene()
{
}
void IntroScene::Update(DWORD dt)
{
	//CGameScene::Update(dt);
	if (keyEntered && !isChangingScene)
		isChangingScene = true;
}

void IntroScene::Render()
{
	/*D3DXVECTOR3 pos;
	pos.x = 150.0f;
	pos.y = 80.0f;
	pos.z = 0;
	pos=camera->SetPositionInViewPort(pos);*/
	
	sprites->Get(400)->Draw(150, 150, ALPHA);
}

bool IntroScene::GetIsChangingScene()
{
	return CGameScene::GetIsChangingScene();;
}

void IntroScene::SetIsChangingScene(bool status)
{
	CGameScene::SetIsChangingScene(status);
}

void IntroScene::PauseBackgroundSound()
{
}

