#pragma once
#include "GameScene.h"
#include "TileMap.h"
class CGameSceneStage31 :public CGameScene
{
	CTileMap *tileMap;

	/*CSprite *sprite;
	Sprite	*castleSprite;

	GameObject *ground;
	GameObject *cameraObject;
	GameObject *leftCamera;
	GameObject *rightCamera;

	QuadTree *quadTree;
	UI *ui;

	std::vector<GameObject*> *list;
	std::vector<Item*> *listItem;
	LPDIRECT3DDEVICE9 gDevice;*/

public:
	CGameSceneStage31();
	~CGameSceneStage31();
	void Update(DWORD dt);
	void Render();
	bool GetIsChangingScene();
	void SetIsChangingScene(bool status);
	void DestroyAll();
};

