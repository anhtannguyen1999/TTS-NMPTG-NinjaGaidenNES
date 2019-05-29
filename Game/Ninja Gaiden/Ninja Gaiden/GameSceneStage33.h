
#include "GameScene.h"
#include "TileMap.h"

class CGameSceneStage33 :public CGameScene
{
	CTileMap *tileMap;
	CGrid * gridGame;
	vector<CGameObject*> listBackgroundObj;//Luu may cai nhu ground, wall...
	vector<CGameObject*> listOtherObj;
public:
	CGameSceneStage33();
	~CGameSceneStage33();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
	void CheckCollision();
	void CheckCollisionNinjaWithGround();
	void CheckCollisionEnemyWithGroundAndVuKhi();
	void CheckCollisionNinjaWidthEnemy();
};

