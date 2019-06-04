#include "SceneManager.h"
#include "Ninja.h"


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
	ninja = CNinja::GetInstance();
	switch (sceneID)
	{
	case GAME_STAGE_31:
		delete(gameScene);
		
		gameScene = new CGameSceneStage31();
		//ninja->SetPositionX(2000);
		break;
	case GAME_STAGE_32:
		delete(gameScene);
		gameScene = new CGameSceneStage32();
		//ninja->SetPositionX(3000);
		ninja->SetPositionY(200);
		break;
	case GAME_STAGE_33:
		delete(gameScene);
		gameScene = new CGameSceneStage33();
		ninja->SetPositionY(200);
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
	if (ninja)
	{
		if (sceneID == GAME_STAGE_31&& ninja->GetPositionX() >= 2020)
		{
			this->NextScene();
		}
		if (sceneID == GAME_STAGE_32&& ninja->GetPositionX() >= 3040)
		{
			this->NextScene();
		}
	}
	
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

	ani = new CAnimation(25);	// throw right
	ani->Add(160);
	ani->Add(161);
	ani->Add(162);
	animations->Add(112, ani);

	ani = new CAnimation(25);	// throw left
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

	sprites->Add(200, 212, 50, 241, 93, texEnemy, zero, zero, zero, 0);		// merc right
	sprites->Add(201, 212 + 30, 50, 241 + 30, 93, texEnemy, zero, zero, zero, 0);
	sprites->Add(202, 212 + 60 + 8, 50, 300, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(203, 212, 50, 241, 93, texEnemy, zero, zero, scaleNguoc, 0);		// merc left
	sprites->Add(204, 212 + 30, 50, 241 + 30, 93, texEnemy, zero, zero, scaleNguoc, 0);
	sprites->Add(205, 212 + 60 + 8, 50, 300, 93, texEnemy, zero, zero, scaleNguoc, 0);

	ani = new CAnimation(300);	// merc right
	ani->Add(200);
	ani->Add(201);
	ani->Add(202);
	animations->Add(200, ani);

	ani = new CAnimation(300);//merc left
	ani->Add(203);
	ani->Add(204);
	ani->Add(205);
	animations->Add(201, ani);

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

	#pragma region Load resource cho enemy Hawk
	sprites->Add(260, 477, 59, 495, 94, texEnemy, zero, zero, zero, 0);		// hawk right
	sprites->Add(261, 504, 59, 523, 85, texEnemy, zero, zero, zero, 0);

	sprites->Add(262, 477, 59, 495, 94, texEnemy, zero, zero, scaleNguoc, 0);		// hawk left
	sprites->Add(263, 504, 59, 523, 85, texEnemy, zero, zero, scaleNguoc, 0);

	ani = new CAnimation(100); //hawk right
	ani->Add(260);
	ani->Add(261);
	animations->Add(212, ani);

	ani = new CAnimation(100); //hawk left
	ani->Add(262);
	ani->Add(263);
	animations->Add(213, ani);
	#pragma endregion

	#pragma region Load resource cho cloak

	sprites->Add(270, 411, 2, 439, 47, texEnemy, zero, zero, zero, 0);		// cloak right
	sprites->Add(271, 446, 2, 476, 47, texEnemy, zero, zero, zero, 0);
	sprites->Add(272, 493, 2, 515, 47, texEnemy, zero, zero, zero, 0);

	sprites->Add(273, 411, 2, 439, 47, texEnemy, zero, zero, scaleNguoc, 0);		// cloak left
	sprites->Add(274, 446, 2, 476, 47, texEnemy, zero, zero, scaleNguoc, 0);
	sprites->Add(275, 493, 2, 515, 47, texEnemy, zero, zero, scaleNguoc, 0);
	ani = new CAnimation(100);	// cloak right
	ani->Add(270);
	ani->Add(271);
	animations->Add(214, ani);

	ani = new CAnimation(100);	// cloak right throw
	ani->Add(272);
	animations->Add(234, ani);

	ani = new CAnimation(100);	// cloak left
	ani->Add(273);
	ani->Add(274);
	animations->Add(215, ani);

	ani = new CAnimation(100);	// cloak left throw
	ani->Add(275);
	animations->Add(235, ani);

	#pragma endregion

	#pragma region Load resource Commando

	sprites->Add(290, 57, 59, 80, 93, texEnemy, zero, zero, zero, 0);		// Commando right
	sprites->Add(291, 81, 59, 104, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(292, 57, 59, 80, 93, texEnemy, zero, zero, scaleNguoc, 0);		// Commando left
	sprites->Add(293, 81, 59, 104, 93, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(294, 131, 59, 162, 93, texEnemy, zero, zero, zero, 0);		// Commando shoot right
	sprites->Add(295, 162, 59, 190, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(296, 131, 59, 162, 93, texEnemy, zero, zero, scaleNguoc, 0);		// Commando shoot left
	sprites->Add(297, 162, 59, 190, 93, texEnemy, zero, zero, scaleNguoc, 0);

	ani = new CAnimation(100);	// commando right
	ani->Add(290);
	ani->Add(291);
	animations->Add(240, ani);

	ani = new CAnimation(100);	// commando left
	ani->Add(292);
	ani->Add(293);
	animations->Add(241, ani);

	ani = new CAnimation(100);	// commando shoot right
	ani->Add(294);
	ani->Add(295);
	animations->Add(242, ani);

	ani = new CAnimation(100);	// commando shoot left
	ani->Add(296);
	ani->Add(297);
	animations->Add(243, ani);
	#pragma endregion

	#pragma region Load resource for gunner and runner
	sprites->Add(210, 0, 59, 21, 93, texEnemy, zero, zero, zero, 0);		// runner right
	sprites->Add(211, 23, 59, 42, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(212, 0, 59, 21, 93, texEnemy, zero, zero, scaleNguoc, 0);		// runner left
	sprites->Add(213, 23, 59, 42, 93, texEnemy, zero, zero, scaleNguoc, 0);


	sprites->Add(220, 388, 66, 416, 93, texEnemy, zero, zero, zero, 0);		// gunner right
	sprites->Add(221, 417, 66, 460, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(222, 388, 66, 416, 93, texEnemy, zero, zero, scaleNguoc, 0);		// gunner left
	sprites->Add(223, 417, 66, 460, 93, texEnemy, zero, zero, scaleNguoc, 0);

	ani = new CAnimation(100); //runner right
	ani->Add(210);
	ani->Add(211);
	animations->Add(202, ani);

	ani = new CAnimation(100);//runner left
	ani->Add(212);
	ani->Add(213);
	animations->Add(203, ani);

	ani = new CAnimation(800); //gunner right
	ani->Add(220);
	animations->Add(204, ani);

	ani = new CAnimation(800); //gunner left
	ani->Add(222);
	animations->Add(205, ani);

	ani = new CAnimation(200); //gunner right shoot
	ani->Add(221);
	animations->Add(224, ani);

	ani = new CAnimation(200); //gunner left shoot
	ani->Add(223);
	animations->Add(225, ani);
	#pragma endregion

	#pragma region Load resource cho cross

	sprites->Add(280, 523, 8, 536, 24, texEnemy, zero, zero, zero, 0);		// cross right
	sprites->Add(281, 523, 8, 536, 24, texEnemy, zero, zero, scaleNguoc, 0);// cross left

	ani = new CAnimation(100);	// cross right
	ani->Add(280);
	animations->Add(216, ani);

	ani = new CAnimation(100);	// cross left
	ani->Add(281);
	animations->Add(217, ani);
	#pragma endregion

	#pragma region Load resource cho Bullet of Commando
	sprites->Add(298, 194, 67, 206, 73, texEnemy, zero, zero, zero, 0); //C-bullet
	sprites->Add(299, 194, 67, 206, 73, texEnemy, zero, zero, scaleNguoc, 0);//C-bullet
	ani = new CAnimation(100);	// C-bullet right
	ani->Add(298);
	animations->Add(244, ani);

	ani = new CAnimation(100);	// C-bullet left
	ani->Add(299);
	animations->Add(245, ani);
	#pragma endregion

	#pragma region Load resource cho bullet gunner
	sprites->Add(230, 460, 65, 475, 78, texEnemy, zero, zero, zero, 0);  // bullet right
	sprites->Add(231, 460, 65, 475, 78, texEnemy, zero, zero, scaleNguoc, 0);// bullet left

	ani = new CAnimation(100); //bullet right
	ani->Add(230);
	animations->Add(206, ani);

	ani = new CAnimation(100); //bullet left
	ani->Add(231);
	animations->Add(207, ani);
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
	sprites->Add(300, 433, 270, 450, 280, texEnemy, zero, zero, zero, 0);//bullet boss

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
	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	//D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);
	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();
	
	sprites->Add(ID_SPRITE_BOXCOLLISION, 2, 4, 19 + 2, 34 + 4, texBoxCollision, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), 0);

	textures->Add(ID_TEX_CONTAINERANDEFFECT, L"textures\\ContainerAndEffectTex.png", D3DCOLOR_XRGB(255, 163, 177));
	//hieu ung no khi danh
	LPDIRECT3DTEXTURE9 effectTex = textures->Get(ID_TEX_CONTAINERANDEFFECT);
	sprites->Add(301, 317, 1, 349, 41, effectTex, zero, zero, D3DXVECTOR2(0.9f, 0.8f), 0);//0.9 0.8
	sprites->Add(303, 317, 1, 349, 41, effectTex, zero, zero, zero, 0); // zero
	//sprites->Add(304, 317, 1, 349, 41, effectTex, zero, zero, D3DXVECTOR2(1.2f, 1), 0);// 1.2 1
	sprites->Add(302, 317, 1, 349, 41, effectTex, zero, zero, D3DXVECTOR2(1.4f, 1.2f), 0);// 1.4 1.2

	ani = new CAnimation(25); //hieu ung no khi danh
	ani->Add(302);
	ani->Add(301);
	ani->Add(303);
	animations->Add(301, ani);

	#pragma region Container and Item

	sprites->Add(310, 79, 50, 96, 70, effectTex, zero, zero, zero, 0);// butterfly 
	sprites->Add(311, 96, 50, 114, 70, effectTex, zero, zero, zero, 0);

	sprites->Add(312, 114, 50, 135, 70, effectTex, zero, zero, zero, 0);// bird 
	sprites->Add(313, 136, 50, 157, 70, effectTex, zero, zero, zero, 0);

	sprites->Add(320, 169, 8, 189, 26, effectTex, zero, zero, zero, 0);// bag 1

	sprites->Add(321, 189, 8, 209, 26, effectTex, zero, zero, zero, 0);//bag 2

	sprites->Add(322, 0, 8, 20, 26, effectTex, zero, zero, zero, 0);// soul 1

	sprites->Add(323, 20, 8, 40, 26, effectTex, zero, zero, zero, 0);// soul 2

	//Tan
	sprites->Add(324, 46, 8, 66, 26, effectTex, zero, zero, zero, 0);// small shuriken item

	sprites->Add(325, 66, 8, 86, 26, effectTex, zero, zero, zero, 0);// big shuriken item

	sprites->Add(326, 106, 8, 126, 26, effectTex, zero, zero, zero, 0);// fire item

	sprites->Add(327, 227, 8, 243, 26, effectTex, zero, zero, zero, 0);// Health pot

	sprites->Add(328, 243, 8, 262, 26, effectTex, zero, zero, zero, 0);// Hour glass

	sprites->Add(329, 263, 13, 273, 23, effectTex, zero, zero, zero, 0);// small shuriken

	sprites->Add(330, 274, 6, 295, 25, effectTex, zero, zero, zero, 0);// big shuriken

	sprites->Add(331, 296, 7, 309, 25, effectTex, zero, zero, zero, 0);// fire 

	ani = new CAnimation(50);//butterfly
	ani->Add(310);
	ani->Add(311);
	animations->Add(310, ani);

	ani = new CAnimation(50);//bird
	ani->Add(312);
	ani->Add(313);
	animations->Add(311, ani);

	ani = new CAnimation(100);//Bag 1
	ani->Add(320);
	animations->Add(320, ani);

	ani = new CAnimation(100);//Bag 2
	ani->Add(321);
	animations->Add(321, ani);

	ani = new CAnimation(100);//soul 1
	ani->Add(322);
	animations->Add(322, ani);

	ani = new CAnimation(100);//soul 2
	ani->Add(323);
	animations->Add(323, ani);

	ani = new CAnimation(100);//small shuriken item
	ani->Add(324);
	animations->Add(324, ani);

	ani = new CAnimation(100);//big shuriken item
	ani->Add(325);
	animations->Add(325, ani);

	ani = new CAnimation(100);//fire item
	ani->Add(326);
	animations->Add(326, ani);

	ani = new CAnimation(100);//health pot
	ani->Add(327);
	animations->Add(327, ani);

	ani = new CAnimation(100);//hour glass
	ani->Add(328);
	animations->Add(328, ani);

	ani = new CAnimation(100);//small shuriken
	ani->Add(329);
	animations->Add(329, ani);

	ani = new CAnimation(100);//big shuriken
	ani->Add(330);
	animations->Add(330, ani);

	ani = new CAnimation(100);//fire
	ani->Add(331);
	animations->Add(331, ani);

	#pragma endregion

}