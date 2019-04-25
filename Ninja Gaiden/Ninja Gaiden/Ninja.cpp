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
	textures->Add(ID_TEX_NINJA, L"textures\\NinjaTex.png", D3DCOLOR_XRGB(255, 163, 177));
	LPDIRECT3DTEXTURE9 texNinja = textures->Get(ID_TEX_NINJA);

	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scaleNguoc = D3DXVECTOR2(-1, 1);

	sprites->Add(101, 2, 4, 19+2, 34+4, texNinja, zero, zero, zero, 0);		// idle right
	sprites->Add(102, 2, 4, 19 + 2, 34 + 4, texNinja, zero, zero, scaleNguoc, 0);		// idle left

	sprites->Add(111, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, zero, 0);	//Run Right 1
	sprites->Add(112, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, zero, 0);
	sprites->Add(113, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, zero, 0);

	sprites->Add(114, 338, 5, 338 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);	//Run Left 1
	sprites->Add(115, 367, 5, 367 + 24, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);
	sprites->Add(116, 399, 5, 399 + 22, 5 + 33, texNinja, zero, zero, scaleNguoc, 0);

	//animation là 1 mảng
	LPANIMATION ani;
	ani = new CAnimation(100);	// idle right
	ani->Add(101);
	animations->Add(100, ani);

	ani = new CAnimation(67);	// run right
	ani->Add(111);
	ani->Add(112);
	ani->Add(113);
	animations->Add(101, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(102);
	animations->Add(102, ani);

	ani = new CAnimation(67);	// run left
	ani->Add(114);
	ani->Add(115);
	ani->Add(116);
	animations->Add(103, ani);

	this->AddAnimation(100); //Thêm cái ani 100 vào mảng anis của nhân vật ninja => ani 0 = Idle right
	this->AddAnimation(101);	//ani 1 = run
	this->AddAnimation(102);	//ani 2 = idle left
	this->AddAnimation(103);	//ani 3 = run left
	this->SetPosition(50.0f, 0);

}




