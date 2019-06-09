
#include "GameScene.h"
class CGameSceneGameOver :
	public CGameScene
{
	LPDIRECT3DDEVICE9 d3ddv;
	ID3DXFont *font;
	//CSprites * sprites = CSprites::GetInstance();
	RECT rectFont;// hcn chứa font chữ
public:
	CGameSceneGameOver();
	~CGameSceneGameOver();
	void Update(DWORD dt);
	void Render();
	virtual void PauseBackgroundSound();
	
};
