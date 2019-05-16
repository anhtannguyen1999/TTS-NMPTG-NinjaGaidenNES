#include "Enemy.h"
#include "debug.h"
#include <algorithm>
#include "Textures.h"





Enemy::~Enemy()
{

}

void Enemy::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_ENEMY, L"textures\\Enemies.png", D3DCOLOR_XRGB(255, 163, 177));

	LPDIRECT3DTEXTURE9	texEnemy = textures->Get(ID_TEX_ENEMY);

	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);

	sprites->Add(200, 212, 59, 241, 93, texEnemy, zero, zero, zero, 0);		// merc right
	sprites->Add(201, 212+30, 59, 241+30, 93, texEnemy, zero, zero, zero, 0);
	sprites->Add(202, 212+60+8, 50, 300, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(203, 212, 59, 241, 93, texEnemy, zero, zero, scaleNguoc, 0);		// merc left
	sprites->Add(204, 212 + 30, 59, 241 + 30, 93, texEnemy, zero, zero, scaleNguoc, 0);
	sprites->Add(205, 212 + 60 + 8, 50, 300, 93, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(210, 0, 59, 21, 93, texEnemy, zero, zero, zero, 0);		// runner right
	sprites->Add(211, 30, 59, 42, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(212, 0, 59, 21, 93, texEnemy, zero, zero, scaleNguoc, 0);		// runner right
	sprites->Add(213, 30, 59, 42, 93, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(220, 388, 66, 416, 93, texEnemy, zero, zero, zero, 0);		// gunner right
	sprites->Add(221, 417, 66, 460, 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(222, 388, 66, 416, 93, texEnemy, zero, zero, scaleNguoc, 0);		// gunner left
	sprites->Add(223, 417, 66, 460, 93, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(230, 462, 69, 473, 74, texEnemy, zero, zero, zero, 0);  // bullet right

	sprites->Add(231, 462, 69, 473, 74, texEnemy, zero, zero, scaleNguoc, 0);// bullet left

	sprites->Add(240, 310, 77, 348, 93, texEnemy, zero, zero, zero, 0);		// panther right
	sprites->Add(241, 352, 77,381 , 93, texEnemy, zero, zero, zero, 0);

	sprites->Add(242, 310, 77, 348, 93, texEnemy, zero, zero, scaleNguoc, 0);		// panther left
	sprites->Add(243, 352, 77, 381, 93, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(250, 323, 57, 343, 73, texEnemy, zero, zero, zero, 0);		// bat right
	sprites->Add(251, 345, 57, 365, 73, texEnemy, zero, zero, zero, 0);

	sprites->Add(252, 323, 57, 343, 73, texEnemy, zero, zero, scaleNguoc, 0);		// bat left
	sprites->Add(253, 345, 57, 365, 73, texEnemy, zero, zero, scaleNguoc, 0);


	sprites->Add(260, 476, 72, 495, 91, texEnemy, zero, zero, zero, 0);		// hawk right
	sprites->Add(261, 500, 58, 524, 87, texEnemy, zero, zero, zero, 0);

	sprites->Add(262, 476, 72, 495, 91, texEnemy, zero, zero, scaleNguoc, 0);		// hawk left
	sprites->Add(263, 500, 58, 524, 87, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(270, 411,13, 439, 47, texEnemy, zero, zero, zero, 0);		// cloak right
	sprites->Add(271, 446, 13, 476, 47, texEnemy, zero, zero, zero, 0);
	sprites->Add(272, 493, 2, 515, 47, texEnemy, zero, zero, zero, 0);

	sprites->Add(273, 411, 13, 439, 47, texEnemy, zero, zero, scaleNguoc, 0);		// cloak left
	sprites->Add(274, 446, 13, 476, 47, texEnemy, zero, zero, scaleNguoc, 0);
	sprites->Add(275, 493, 2, 515, 47, texEnemy, zero, zero, scaleNguoc, 0);

	sprites->Add(280, 523, 8, 536, 24, texEnemy, zero, zero, zero, 0);		// cross right

	sprites->Add(281, 523, 8, 536, 24, texEnemy, zero, zero, scaleNguoc , 0);// cross left
	LPANIMATION ani;
	ani = new CAnimation(50);	// merc right
	ani->Add(200);
	ani->Add(201);
	ani->Add(202);
	animations->Add(200, ani);

	ani = new CAnimation(50);//merc left
	ani->Add(203);
	ani->Add(204);
	ani->Add(205);
	animations->Add(201, ani);

	ani = new CAnimation(50); //runner right
	ani->Add(210);
	ani->Add(211);
	
	animations->Add(202, ani);

	ani = new CAnimation(50);//runner left
	ani->Add(212);
	ani->Add(213);
	animations->Add(203, ani);

	ani = new CAnimation(50); //gunner right
	ani->Add(220);
	ani->Add(221);
	animations->Add(204, ani);

	ani = new CAnimation(50); //gunner left
	ani->Add(222);
	ani->Add(223);
	animations->Add(205, ani);

	ani = new CAnimation(50); //buller right
	ani->Add(230);
	animations->Add(206, ani);

	ani = new CAnimation(50); //bullet left
	ani->Add(231);
	animations->Add(207, ani);

	ani = new CAnimation(50); //panther right
	ani->Add(240);
	ani->Add(241);
	animations->Add(208, ani);

	ani = new CAnimation(50); //panther left
	ani->Add(242);
	ani->Add(243);
	animations->Add(209, ani);

	ani = new CAnimation(50); //bat right
	ani->Add(250);
	ani->Add(251);
	animations->Add(210, ani);

	ani = new CAnimation(50); //bat left
	ani->Add(252);
	ani->Add(253);
	animations->Add(211, ani);

	ani = new CAnimation(50); //hawk right
	ani->Add(260);
	ani->Add(261);
	animations->Add(212, ani);

	ani = new CAnimation(50); //hawk left
	ani->Add(262);
	ani->Add(263);
	animations->Add(213, ani);

	ani = new CAnimation(50);	// cloak right
	ani->Add(270);
	ani->Add(271);
	ani->Add(272);
	animations->Add(214, ani);

	ani = new CAnimation(50);	// cloak left
	ani->Add(273);
	ani->Add(274);
	ani->Add(275);
	animations->Add(215, ani);

	ani = new CAnimation(50);	// cross right
	ani->Add(280);
	animations->Add(216, ani);

	ani = new CAnimation(50);	// cross left
	ani->Add(281);
	animations->Add(217, ani);
}
