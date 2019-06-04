#pragma once
#include "Camera.h"
#include "Grid.h"
#include "Ninja.h"
#include "NinjaSword.h"
#include "Effect.h"

static int score;
class CGameScene
{
protected:
	std::vector<CGameObject*> *listObject;
	vector<CGameObject*> listBackgroundObj;//Luu may cai nhu ground, wall...
	vector<CGameObject*> listOtherObj;
	CCamera *camera = CCamera::GetInstance();
	bool isChangingScene;
	bool canUseKeyboard;
	//static CNinja* ninja;
	CNinja*ninja = CNinja::GetInstance();
	D3DXVECTOR3 ninjaCheckpoint;
	CEffect *effect = CEffect::GetInstance();
	int pauseEnemyTimer = 0; 
public:
	CGameScene();
	~CGameScene();
	virtual void Render() {};
	virtual void Update(DWORD dt);
	virtual void DestroyAll() {};
	
	//2 cai nay dung de chuyen scene
	virtual bool GetIsChangingScene() { return isChangingScene; };
	virtual void SetIsChangingScene(bool status) { isChangingScene = status; }

	//hàm check, lưu vị trí khi ninja đi qua check point

	void KeyDown(unsigned short int const &key);
	void KeyUp(unsigned short int const &key);
};

