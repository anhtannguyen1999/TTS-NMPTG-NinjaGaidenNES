
#include "GameScene.h"

class CGameSceneStage33 :public CGameScene
{
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
};

