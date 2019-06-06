#include "ScoreBoard.h"
#include<fontsub.h>
CScoreBoard * CScoreBoard::__instance = NULL;

CScoreBoard::CScoreBoard()
{
	d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LoadResourceHp();
	
		
	D3DXCreateFont(d3ddv, 11, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 5, FF_DONTCARE, L"Arial", &font);
	D3DXCreateFont(d3ddv, 11, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 5, FF_DONTCARE, L"", &font2);
	SetRect(&rectFont, 0, 0, 100, 100);
	SetRect(&rectFont2, 83, 0, 200, 200);
	messenge = " Score is: " + std::to_string(score) +"\tSTAGE: " +stageInGame+ "\n" + "Timer: " + std::to_string(timer);


}
CScoreBoard * CScoreBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CScoreBoard();
	return __instance;
}

void CScoreBoard::Update(DWORD dt)
{
	//score = ninja->GetHP();
	if (GetTickCount() - prevTimer >= 1000)
	{
		timer--;
		prevTimer = GetTickCount();
	}
	score = ninja->GetPoint();
	int Mana = ninja->GetMana();
	messenge = " SCORE - " + std::to_string(score)
		+ "\n" + " TIMER - " + std::to_string(timer)

		+ "\n P0-2      "+std::to_string(Mana);

	messenge2= "STAGE: " + stageInGame + "\n" +"NINJA -"   + "\nENEMY-";
	
}

void CScoreBoard::Render()
{
	
		font->DrawTextA(NULL, messenge.c_str(), -1, &rectFont, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		font2->DrawTextA(NULL, messenge2.c_str(), -1, &rectFont2, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));

		sprites->Get(502)->Draw(32, 27, 255);
		for (int k = 0; k < ninja->GetHP(); k++)
		{
			sprites->Get(501)->Draw(k*6+120, 16, 255);
		}
		for (int i = ninja->GetHP(); i < 16; i++)
		{
			sprites->Get(500)->Draw(i * 6+120, 16, 255);
		}


		if (stageInGame != "3-3")
		{
			for (int k = 0; k < 16; k++)
			{
				sprites->Get(501)->Draw(k * 6 + 120, 28, 255);
			}
			
		}
		else
		{
			int HPBoss = CBoss::GetInstance()->GetHP();
			if (HPBoss <= 0)
			{
				HPBoss = 0;
			}
			for (int k = 0; k < HPBoss; k++)
			{
				sprites->Get(501)->Draw(k * 6 + 120, 28, 255);
			}
			for (int i = HPBoss; i < 16; i++)
			{
				sprites->Get(500)->Draw(i * 6 + 120, 28, 255);
			}
		}
		if (ninja->GetTypeItem() != 0)
		{
			switch (ninja->GetTypeItem())
			{
			case WEAPON_MINITYPE_SMALL_SHURIKEN:
				sprites->Get(324)->Draw(70, 22, 255);
				break;
			case WEAPON_MINITYPE_BIG_SHURIKEN:
				sprites->Get(325)->Draw(70, 22, 255);
				break;
			case WEAPON_MINITYPE_FIRES:
				sprites->Get(326)->Draw(70, 22, 255);
				break;
			default:
				break;
			}
		}
	    
	

}

void CScoreBoard::SetStage(int stage)
{
	timer = 150;
	if (stage == 1)
		stageInGame = "3-1";
	else if(stage==2)
		stageInGame = "3-2";
	else if(stage==3)
		stageInGame = "3-3";
}
void CScoreBoard::LoadResourceHp()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_HP, L"textures\\HPNinja_Boss.png", D3DCOLOR_XRGB(255, 0, 0));

	
	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	LPDIRECT3DTEXTURE9	texHP = textures->Get(ID_TEX_HP);
	sprites->Add(500, 39, 0, 45, 10, texHP, zero, zero, zero, 0);//HP trắng
	sprites->Add(501, 27, 0, 32, 10, texHP, zero, zero, zero, 0);//HP đỏ
	sprites->Add(502, 60, 5, 74, 20, texHP, zero, zero, zero, 0);//icon mana
}
CScoreBoard::~CScoreBoard()
{
}
