
#include "GameScene.h"

class CGameSceneStage33 :public CGameScene
{
	CBoss* boss = CBoss::GetInstance();
	int tick = 0;
	//bool readyForNextScene = false;
public:
	CGameSceneStage33();
	~CGameSceneStage33();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
	void CheckCollision();
	//void CheckCollisionNinjaWithGround();
	//void CheckCollisionEnemyWithGroundAndVuKhi();
	void CheckCollisionNinjaWidthBossAndBullet();
	//bool GetReadyForNextScene() { return this->readyForNextScene; }
	virtual void PauseBackgroundSound();
};

