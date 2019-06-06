#pragma once
#include "Game.h"
#include<string>
#include "Ninja.h"
#include "Sprites.h"
#include "Textures.h"
#include "Boss.h"

class CScoreBoard
{
private:
	static CScoreBoard *__instance;

	LPDIRECT3DDEVICE9 d3ddv;
	ID3DXFont *font, *font2;
	CNinja *ninja = CNinja::GetInstance();
	//CBoss *boss = CBoss::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	RECT rectFont, rectFont2;// hcn chứa font chữ
	RECT rectItem;// hcn chứa item

	std::string messenge,messenge2, stageInGame;
	int score = 0, timer = 150;
	int prevTimer = GetTickCount();
	

public:

	CScoreBoard();
	void Update(DWORD dt);
	static CScoreBoard * CScoreBoard::GetInstance();
	void Render();
	void SetStage(int stage);
	void LoadResourceHp();

	~CScoreBoard();
};

