#pragma once
#include "GameScene.h"
class OuttroScene :
	public CGameScene
{
	LPDIRECT3DDEVICE9 d3ddv;
	ID3DXFont *font;
	RECT rectFont;//hcn chua font chu
public:
	OuttroScene();
	~OuttroScene();
	void Update(DWORD dt);
	void Render();
	virtual void PauseBackgroundSound();
};

