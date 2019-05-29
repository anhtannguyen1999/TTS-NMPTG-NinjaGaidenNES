#include "SceneManager.h"


CSceneManager * CSceneManager::__instance = NULL;

CSceneManager::CSceneManager()
{
	LoadResource();
	sceneID = 1;
	//__instance = NULL;
}


CSceneManager::~CSceneManager()
{
	//sceneID = 1;

}

void CSceneManager::LoadScene(int sceneID)
{
	switch (sceneID)
	{
	case GAME_STAGE_31:
		delete(gameScene);
		gameScene = new CGameSceneStage31();
		break;
	case GAME_STAGE_32:
		delete(gameScene);
		gameScene = new CGameSceneStage32();
		break;
	case GAME_STAGE_33:
		delete(gameScene);
		gameScene = new CGameSceneStage33();
		break;
	default:
		break;
	}
}

void CSceneManager::Render()
{
	gameScene->Render();
}

void CSceneManager::Update(DWORD dt)
{
	gameScene->Update(dt);

}

void CSceneManager::NextScene()
{
	this->sceneID++;
	this->LoadScene(sceneID);
}

void CSceneManager::PreScece()
{
	this->sceneID--;
	this->LoadScene(sceneID);
}
int CSceneManager::GetIDScence()
{
	return sceneID;
 }
void CSceneManager::KeyDown(unsigned short int const & key)
{
	gameScene->KeyDown(key);
}

void CSceneManager::KeyUp(unsigned short int const &key)
{
	gameScene->KeyUp(key);
}

CSceneManager * CSceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new CSceneManager();
	return __instance;
}

void CSceneManager::LoadResource()
{
	LoadResouceForNinja();
	LoadResourceForEnemies();
	LoadOtherResource();
}

void CSceneManager::LoadResouceForNinja()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_NINJA, L"textures\\Ninja.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);
	LPANIMATION ani;


	#pragma region Load resource cho Ninja
	LPDIRECT3DTEXTURE9 texNinja = textures->Get(ID_TEX_NINJA);

	sprites->Add(101, 0, 0, 26, 35, texNinja, zero, zero, zero, 0);		// idle right
	sprites->Add(102, 0, 0, 26, 35, texNinja, zero, zero, scaleNguoc, 0);		// idle left

																				//sprites->Add(111, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, zero, 0);	//Run Right 1
																				//sprites->Add(112, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, zero, 0);
																				//sprites->Add(113, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, zero, 0);
																				//sprites->Add(114, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);	//Run Left 1
																				//sprites->Add(115, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);
																				//sprites->Add(116, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(111, 26, 0, 52, 35, texNinja, zero, zero, zero, 0);	//Run Right 1
	sprites->Add(112, 52, 0, 52 + 26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(113, 52 + 26, 0, 52 + 26 + 26, 35, texNinja, zero, zero, zero, 0);

	sprites->Add(114, 26, 0, 52, 35, texNinja, zero, zero, scaleNguoc, 0);	//Run Left 1
	sprites->Add(115, 52, 0, 52 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(116, 52 + 26, 0, 52 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(120, 107, 0, 127, 35, texNinja, zero, zero, zero, 0);//climb right
	sprites->Add(121, 128, 0, 127 + 26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(122, 107, 0, 127, 35, texNinja, zero, zero, scaleNguoc, 0);//climb left
	sprites->Add(123, 128, 0, 127 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(130, 156, 0, 156 + 26, 35, texNinja, zero, zero, zero, 0);//jump right
	sprites->Add(131, 156 + 26, 0, 156 + 26 + 26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(132, 156 + 26 + 26, 0, 156 + 26 + 26 + 26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(133, 156 + 26 + 26 + 26, 0, 156 + 26 + 26 + 26 + 26, 35, texNinja, zero, zero, zero, 0);

	sprites->Add(134, 156, 0, 156 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);//jump left
	sprites->Add(135, 156 + 26, 0, 156 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(136, 156 + 26 + 26, 0, 156 + 26 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(137, 156 + 26 + 26 + 26, 0, 156 + 26 + 26 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(140, 0, 35, 26, 70, texNinja, zero, zero, zero, 0);//attack right
	sprites->Add(141, 26, 35, 26 + 26 + 26, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(142, 52 + 26, 35, 26 + 26 + 26 + 26 + 26, 70, texNinja, zero, zero, zero, 0);

	sprites->Add(143, 0, 35, 26, 70, texNinja, zero, zero, scaleNguoc, 0);//attack left
	sprites->Add(144, 26, 35, 26 + 26 + 26, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(145, 52 + 26, 35, 26 + 26 + 26 + 26 + 26, 70, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(150, 128, 35, 155, 70, texNinja, zero, zero, zero, 0);//jump attack right
	sprites->Add(151, 156, 35, 180, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(152, 181, 35, 208, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(153, 208, 35, 236, 70, texNinja, zero, zero, zero, 0);

	sprites->Add(154, 128, 35, 155, 70, texNinja, zero, zero, scaleNguoc, 0);//jump attack left
	sprites->Add(155, 156, 35, 180, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(156, 181, 35, 208, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(157, 208, 35, 236, 70, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(160, 0, 72, 26, 107, texNinja, zero, zero, zero, 0);//throw right
	sprites->Add(161, 26, 72, 52, 107, texNinja, zero, zero, zero, 0);
	sprites->Add(162, 49, 72, 82, 107, texNinja, zero, zero, zero, 0);

	sprites->Add(163, 0, 72, 26, 107, texNinja, zero, zero, scaleNguoc, 0);//throw left
	sprites->Add(164, 26, 72, 52, 107, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(165, 49, 72, 82, 107, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(170, 104, 75, 130, 110, texNinja, zero, zero, zero, 0);//sit attack right
	sprites->Add(171, 130, 75, 156, 110, texNinja, zero, zero, zero, 0);
	sprites->Add(172, 156, 75, 156 + 26 + 26, 110, texNinja, zero, zero, zero, 0);
	sprites->Add(173, 156 + 26 + 26, 75, 156 + 26 + 26 + 26 + 26, 110, texNinja, zero, zero, zero, 0);

	sprites->Add(174, 104, 75, 130, 110, texNinja, zero, zero, scaleNguoc, 0);//sit attack left
	sprites->Add(175, 130, 75, 156, 110, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(176, 156, 75, 156 + 26 + 26, 110, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(177, 156 + 26 + 26, 75, 156 + 26 + 26 + 26 + 26, 110, texNinja, zero, zero, scaleNguoc, 0);

	//animation là 1 mảng
	ani = new CAnimation(100);	// idle right
	ani->Add(101);
	animations->Add(100, ani);

	ani = new CAnimation(60);	// run right
	ani->Add(111);
	ani->Add(112);
	ani->Add(113);
	animations->Add(101, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(102);
	animations->Add(102, ani);

	ani = new CAnimation(60);	// run left
	ani->Add(114);
	ani->Add(115);
	ani->Add(116);
	animations->Add(103, ani);

	ani = new CAnimation(100);	// climb right
	ani->Add(120);
	ani->Add(121);
	animations->Add(104, ani);

	ani = new CAnimation(100);	// climb left
	ani->Add(122);
	ani->Add(123);
	animations->Add(105, ani);

	ani = new CAnimation(45);	// jump right
	ani->Add(130);
	ani->Add(131);
	ani->Add(132);
	ani->Add(133);
	animations->Add(106, ani);

	ani = new CAnimation(45);	// jump left
	ani->Add(134);
	ani->Add(135);
	ani->Add(136);
	ani->Add(137);
	animations->Add(107, ani);

	ani = new CAnimation(100);	// attack right
								//ani->Add(140);
	ani->Add(141);
	ani->Add(142);
	animations->Add(108, ani);

	ani = new CAnimation(100);	// attack left
								//ani->Add(143);
	ani->Add(144);
	ani->Add(145);
	animations->Add(109, ani);

	ani = new CAnimation(100);	// jump attack right
	ani->Add(150);
	ani->Add(151);
	ani->Add(152);
	ani->Add(153);
	animations->Add(110, ani);

	ani = new CAnimation(100);	// jump attack left
	ani->Add(154);
	ani->Add(155);
	ani->Add(156);
	ani->Add(157);
	animations->Add(111, ani);

	ani = new CAnimation(70);	// throw right
	ani->Add(160);
	ani->Add(161);
	ani->Add(162);
	animations->Add(112, ani);

	ani = new CAnimation(70);	// throw left
	ani->Add(163);
	ani->Add(164);
	ani->Add(165);
	animations->Add(113, ani);

	ani = new CAnimation(100);	// sit attack right
								//ani->Add(170);
								//ani->Add(171);
	ani->Add(172);
	ani->Add(173);
	animations->Add(114, ani);

	ani = new CAnimation(100);	// sit attack left
								//ani->Add(174);
								//ani->Add(175);
	ani->Add(176);
	ani->Add(177);
	animations->Add(115, ani);

	ani = new CAnimation(100);	// sit right
	ani->Add(170);
	animations->Add(116, ani);

	ani = new CAnimation(100);	// sit left
	ani->Add(174);
	animations->Add(117, ani);

	ani = new CAnimation(100);	// on wall right
	ani->Add(120);
	//ani->Add(121);
	animations->Add(118, ani);

	ani = new CAnimation(100);	// on wall left
	ani->Add(122);
	//ani->Add(123);
	animations->Add(119, ani);

	ani = new CAnimation(100);	// attacked right
	ani->Add(130);
	animations->Add(120, ani);

	ani = new CAnimation(100);	// attacked left
	ani->Add(134);
	animations->Add(121, ani);

	#pragma endregion


}

void CSceneManager::LoadResourceForEnemies()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_ENEMY, L"textures\\Enemies.png", D3DCOLOR_XRGB(255, 163, 177));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);
	LPANIMATION ani;

	LPDIRECT3DTEXTURE9	texEnemy = textures->Get(ID_TEX_ENEMY);

	#pragma region Load resouce cho enemy NguoiCamKiem

	sprites->Add(200, 212, 59, 241, 93, texEnemy, zero, zero, zero, 0);		// merc right
	sprites->Add(201, 212 + 30, 59, 241 + 30, 93, texEnemy, zero, zero, zero, 0);
	sprites->Add(202, 212 + 60 + 8, 50, 300, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(203, 212, 59, 241, 93, texEnemy, zero, zero, scaleNguoc, 0);		// merc left
	sprites->Add(204, 212 + 30, 59, 241 + 30, 93, texEnemy, zero, zero, scaleNguoc, 0);
	sprites->Add(205, 212 + 60 + 8, 50, 300, 93, texEnemy, zero, zero, scaleNguoc, 0);

	ani = new CAnimation(100);	// merc right
	ani->Add(200);
	ani->Add(201);
	ani->Add(202);
	animations->Add(200, ani);

	ani = new CAnimation(100);//merc left
	ani->Add(203);
	ani->Add(204);
	ani->Add(205);
	animations->Add(201, ani);

	#pragma endregion
#pragma region Load resource cho Enemy Bat
	sprites->Add(250, 323, 57, 343, 73, texEnemy, zero, zero, zero, 0);		// bat right
	sprites->Add(251, 345, 57, 365, 73, texEnemy, zero, zero, zero, 0);

	sprites->Add(252, 323, 57, 343, 73, texEnemy, zero, zero, scaleNguoc, 0);		// bat left
	sprites->Add(253, 345, 57, 365, 73, texEnemy, zero, zero, scaleNguoc, 0);
	ani = new CAnimation(100); //bat right
	ani->Add(250);
	ani->Add(251);
	animations->Add(210, ani);

	ani = new CAnimation(100); //bat left
	ani->Add(252);
	ani->Add(253);
	animations->Add(211, ani);
#pragma endregion
#pragma region Load resource cho Panther
	sprites->Add(240, 310, 77, 348, 93, texEnemy, zero, zero, zero, 0);		// panther right
	sprites->Add(241, 352, 77, 381, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(242, 310, 77, 348, 93, texEnemy, zero, zero, scaleNguoc, 0);		// panther left
	sprites->Add(243, 352, 77, 381, 93, texEnemy, zero, zero, scaleNguoc, 0);
	ani = new CAnimation(150); //panther right
	ani->Add(240);
	ani->Add(241);
	animations->Add(208, ani);

	ani = new CAnimation(150); //panther left
	ani->Add(242);
	ani->Add(243);
	animations->Add(209, ani);
#pragma endregion
#pragma region Load resource cho Boss

	sprites->Add(290, 352, 252, 388, 302, texEnemy, zero, zero, zero, 0); //boss right
	sprites->Add(291, 352, 252, 388, 302, texEnemy, zero, zero, scaleNguoc, 0); //boss left

	sprites->Add(292, 397, 246, 436, 300, texEnemy, zero, zero, zero, 0); // boss fly right
	sprites->Add(293, 397, 246, 436, 300, texEnemy, zero, zero, scaleNguoc, 0); //boss fly left
	ani = new CAnimation(100); //boss right
	ani->Add(290);
	animations->Add(218, ani);

	ani = new CAnimation(100); // boss left
	ani->Add(291);
	animations->Add(219, ani);

	ani = new CAnimation(100); //boss fly right
	ani->Add(292);
	animations->Add(220, ani);

	ani = new CAnimation(100); //boss fly left
	ani->Add(293);
	animations->Add(221, ani);

#pragma endregion
#pragma region Load resource cho Bullet boss
	sprites->Add(300, 433, 270, 450, 280, texEnemy, zero, zero,zero, 0);//bullet boss

	ani = new CAnimation(100); //bullet boss
	ani->Add(300);
	animations->Add(230, ani);
#pragma endregion


}

void CSceneManager::LoadOtherResource()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BOX, L"textures\\BoxCollision.png", D3DCOLOR_XRGB(255, 163, 177));
	LPDIRECT3DTEXTURE9 texBoxCollision = textures->Get(ID_TEX_BOX);
	CSprites * sprites = CSprites::GetInstance();
	sprites->Add(ID_SPRITE_BOXCOLLISION, 2, 4, 19 + 2, 34 + 4, texBoxCollision, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), 0);
}