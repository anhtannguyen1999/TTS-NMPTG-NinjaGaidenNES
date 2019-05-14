#include "Ninja.h"
#include "debug.h"
//#include "Game.h"
#include <algorithm>
#include "Textures.h"

CNinja::~CNinja()
{
}

void CNinja::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	// Simple fall down

	//vy += NINJA_GRAVITY*dt;

	x += dx;

	y += dy;
	
	if (y > 120.0)//chạm đất
	{
		canJump = true;
		y = 120;
		if (isJump != -1)
			isJump = 0;
		else
			y = 135;
	}
	//DebugOut(L"Ninja: %f , %f \n", x, y); 
}

void CNinja::Render()
{
	int ani = NINJA_ANI_IDLE_RIGHT;

	{
		//Nếu đang nhảy thì render trạng thái đang nhảy
		if (isJump)//jump
		{
			if (isHit)//Nếu đánh
			{
				if (isSpecialHit)//Skill đặc biệt
				{
					//
				}
				else//Danh binh thuong
				{
					//
				}
			}
			else//Nếu k đánh thì nhảy thôi
			{
				//
			}
		}
		else if(isSit)//Nếu đang ngồi thì render trạng thái đang ngồi
		{
			if (isHit)//Ngoi danh
			{

			}
			else//Ngoi binh thuong
			{

			}
		}
		else if (isClimb)//Nếu đang leo thì render 
		{

		}
		else//còn lại render trạng thái đứng
		{
			if (vx != 0)
			{
				
				if (nx > 0)//Render ben phai
				{
					ani = NINJA_ANI_RUN_RIGHT;
				}
				else//Render ben trai
				{
					ani = NINJA_ANI_RUN_LEFT;
				}
			}
			else
			{
				if (nx > 0)//Render ben phai
				{
					ani = NINJA_ANI_IDLE_RIGHT;
				}
				else//Render ben trai
				{
					ani = NINJA_ANI_IDLE_LEFT;
				}
			}
		}
	}

	int alpha = 255;

	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = viewPort->SetPositionInViewPort(pos); //Nhân lại thành tọa độ trong viewport
	animations[ani]->Render(pos.x, pos.y, alpha);

}

//Hàm để set trạng thái khi nhấn phím thôi. Hàm render mới chính
void CNinja::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case NINJA_STATE_IDLE:
		vx = 0;
		break;
	case NINJA_STATE_RUN_RIGHT:
		vx = NINJA_SPEED;
		nx = 1;
		if (isJump == 1)
			isJump = 0;
		break;
	case NINJA_STATE_RUN_LEFT:
		vx = -NINJA_SPEED;
		nx = -1;
		if (isJump == 1)
			isJump = 0;
		break;
	//case NINJA_STATE_JUMP:
	//	if (canJump)
	//	{
	//		vy = -ninjaJumpForce;
	//	}
	//	isJump = 1;
	//	canJump = false;
	//	break;
	//case NINJA_STATE_SITDOWN:
	//	vx = 0;
	//	isJump = -1;
	//	break;
	//case NINJA_STATE_HIT:
	//	//hitStatus = 1;
	//	//timeHit = 0;
	//	break;
	}
}

void CNinja::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_NINJA, L"textures\\Ninja.png", D3DCOLOR_XRGB(255,0, 255));
	LPDIRECT3DTEXTURE9 texNinja = textures->Get(ID_TEX_NINJA);

	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);

	sprites->Add(101, 0, 0, 26, 35, texNinja, zero, zero, zero, 0);		// idle right
	sprites->Add(102, 0, 0, 26, 35, texNinja, zero, zero, scaleNguoc, 0);		// idle left

	//sprites->Add(111, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, zero, 0);	//Run Right 1
	//sprites->Add(112, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, zero, 0);
	//sprites->Add(113, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, zero, 0);

	//sprites->Add(114, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);	//Run Left 1
	//sprites->Add(115, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);
	//sprites->Add(116, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(111, 26, 0, 52, 35 , texNinja, zero, zero, zero, 0);	//Run Right 1
	sprites->Add(112, 52, 0, 52+26, 35 , texNinja, zero, zero, zero, 0);
	sprites->Add(113, 52+26, 0, 52+26+26, 35 , texNinja, zero, zero, zero, 0);

	sprites->Add(114, 26, 0, 52, 35 , texNinja, zero, zero, scaleNguoc, 0);	//Run Left 1
	sprites->Add(115, 52, 0, 52+26, 35 , texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(116, 52+26, 0, 52+26+26, 35 , texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(120, 130-26, 0, 130, 35, texNinja, zero, zero, zero, 0);//climb right
	sprites->Add(121, 130, 0, 130+26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(122, 130-26, 0, 130, 35, texNinja, zero, zero, scaleNguoc, 0);//climb left
	sprites->Add(123, 130, 0, 130 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(130, 156, 0, 156+26, 35, texNinja, zero, zero, zero, 0);//jump right
	sprites->Add(131, 156+26, 0, 156 + 26 + 26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(132, 156+26+26, 0, 156 + 26+26+26, 35, texNinja, zero, zero, zero, 0);
	sprites->Add(133, 156+26+26+26, 0, 156 + 26+26+26+26, 35, texNinja, zero, zero, zero, 0);

	sprites->Add(134, 156, 0, 156 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);//jump left
	sprites->Add(135, 156+26, 0, 156 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(136, 156+26+26, 0, 156 + 26 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(137, 156+26+26+26, 0, 156 + 26 + 26 + 26 + 26, 35, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(140, 0, 35, 26, 70, texNinja, zero, zero, zero, 0);//attack right
	sprites->Add(141, 26, 35,   26 + 26+26, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(142, 52+26, 35,  26 + 26 + 26+26+26, 70, texNinja, zero, zero, zero, 0);

	sprites->Add(143, 0, 35, 26, 70, texNinja, zero, zero, scaleNguoc, 0);//attack left
	sprites->Add(144, 26, 35, 26 + 26 + 26, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(145, 52 + 26, 35, 26 + 26 + 26 + 26 + 26, 70, texNinja, zero, zero, scaleNguoc, 0);
	
	sprites->Add(150, 128, 35, 155, 70, texNinja, zero, zero, zero, 0);//jump attack right
	sprites->Add(151, 156, 35, 180, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(152,181, 35, 208, 70, texNinja, zero, zero, zero, 0);
	sprites->Add(153, 208, 35, 236, 70, texNinja, zero, zero, zero, 0);

	sprites->Add(154, 128, 35, 155, 70, texNinja, zero, zero, scaleNguoc, 0);//jump attack left
	sprites->Add(155, 156, 35, 180, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(156, 181, 35, 208, 70, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(157, 208, 35, 236, 70, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(160,0 , 75, 26, 110, texNinja, zero, zero, zero, 0);//throw right
	sprites->Add(161, 26, 75, 52, 110, texNinja, zero, zero, zero, 0);
	sprites->Add(162, 52, 75, 78, 110, texNinja, zero, zero, zero, 0);

	sprites->Add(163, 0, 75, 26, 110, texNinja, zero, zero, scaleNguoc , 0);//throw left
	sprites->Add(164, 26, 75, 52, 110, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(165, 52, 75, 78, 110, texNinja, zero, zero, scaleNguoc, 0);

	sprites->Add(170, 104, 75, 130, 110, texNinja, zero, zero, zero, 0);//sit attack right
	sprites->Add(171, 130, 75, 156, 110, texNinja, zero, zero, zero, 0);
	sprites->Add(172, 156, 75, 156+26+26, 110, texNinja, zero, zero, zero, 0);
	sprites->Add(173, 156+26+26, 75, 156 + 26 + 26+26+26, 110, texNinja, zero, zero, zero, 0);

	sprites->Add(174, 104, 75, 130, 110, texNinja, zero, zero, scaleNguoc, 0);//sit attack left
	sprites->Add(175, 130, 75, 156, 110, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(176, 156, 75, 156 + 26 + 26, 110, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(177, 156 + 26 + 26, 75, 156 + 26 + 26 + 26 + 26, 110, texNinja, zero, zero, scaleNguoc, 0);
	//animation là 1 mảng
	LPANIMATION ani;
	ani = new CAnimation(100);	// idle right
	ani->Add(101);
	animations->Add(100, ani);

	ani = new CAnimation(100);	// run right
	ani->Add(111);
	ani->Add(112);
	ani->Add(113);
	animations->Add(101, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(102);
	animations->Add(102, ani);

	ani = new CAnimation(100);	// run left
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

	ani = new CAnimation(100);	// jump right
	ani->Add(130);
	ani->Add(131);
	ani->Add(132);
	ani->Add(133);
	animations->Add(106, ani);

	ani = new CAnimation(100);	// jump left
	ani->Add(134);
	ani->Add(135);
	ani->Add(136);
	ani->Add(137);
	animations->Add(107, ani);

	ani = new CAnimation(100);	// attack right
	ani->Add(140);
	ani->Add(141);
	ani->Add(142);
	animations->Add(108, ani);

	ani = new CAnimation(100);	// attack left
	ani->Add(143);
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

	ani = new CAnimation(100);	// throw right
	ani->Add(160);
	ani->Add(161);
	ani->Add(162);
	animations->Add(112, ani);

	ani = new CAnimation(100);	// throw left
	ani->Add(163);
	ani->Add(164);
	ani->Add(165);
	animations->Add(113, ani);

	ani = new CAnimation(100);	// sit attack right
	ani->Add(170);
	ani->Add(171);
	ani->Add(172);
	ani->Add(173);
	animations->Add(114, ani);

	ani = new CAnimation(100);	// sit attack left
	ani->Add(174);
	ani->Add(175);
	ani->Add(176);
	ani->Add(177);
	animations->Add(115, ani);

	this->AddAnimation(100); //Thêm cái ani 100 vào mảng anis của nhân vật ninja => ani 0 = Idle right
	this->AddAnimation(101);	//ani 1 = run
	this->AddAnimation(102);	//ani 2 = idle left
	this->AddAnimation(103);	//ani 3 = run left
	this->AddAnimation(104);   
	this->AddAnimation(105);
	this->AddAnimation(106);
	this->AddAnimation(107);
	this->AddAnimation(108);
	this->AddAnimation(109);
	this->AddAnimation(110);
	this->AddAnimation(111);
	this->AddAnimation(112);
	this->AddAnimation(113);
	this->AddAnimation(114);
	this->AddAnimation(115);
	this->SetPosition(50.0f, 0);

}




