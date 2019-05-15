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
	preY = y;
	
	y += dy;
	if(!(isHit!=0 && !isJump && !isSit) && !isOnWall)
		x += dx;

	if (onGround)//chạm đất
	{
		
		//isOnWall = false;
		canJump = true;
		//if(preY>y) //Neu bay xuong thi y=0
			//vy = 0;
		if (isJump != -1)
			isJump = 0;
		//DebugOut(L"Ninja Cham dat\n");
		
	}
	else
	{
		// Simple fall down
		if(!isOnWall)
			vy -= NINJA_GRAVITY*dt;
		//DebugOut(L"Ninja Khong Cham dat\n");
	}
	if (this->y < 8) //xet cho khoi rot gay bug thoi 9
	{
		//this->y = 8;
		SetPosition(30, 100);
		vy = 0; dy = 0;
	}
	
	//DebugOut(L"%f \n", vy);
}
#pragma region Render


void CNinja::Render()
{

	int ani = NINJA_ANI_IDLE_RIGHT;
	//Xét các trạng thái cơ bản
	//		+ các trạng thái đi kèm nằm trong trong cơ bản: Hit
	// Jump: (JumpHit, JumpSpecialHit=Jumpthrow), Jump
	// Sit: (SitHit,SitSpecialHit=SitThrow),Sit
	// Climb: (ClimbIdle,ClimbMove)
	// Attacked: 
	// Còn lại là trạng thái đứng bình thường dưới đất:
	//
	//
	//Nếu đang nhảy thì render trạng thái đang nhảy
	if (isJump)//jump
	{
		Jump(ani);
	}
	else if (isSit)//Nếu đang ngồi thì render trạng thái đang ngồi
	{
		Sit(ani);
	}
	else if (isOnWall)//Nếu đang leo thì render 
	{
		OnWall(ani);
	}
	else//còn lại render trạng thái đứng
	{
		Stand(ani);
	}

	int alpha = 255;

	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos); //Nhân lại thành tọa độ trong viewport
											  //Canh số lại để vẽ vì đứa cắt hình bị lệnh
	if (ani == NINJA_ANI_ATTACK_RIGHT || ani == NINJA_ANI_SITATTACK_RIGHT)
		pos.x += 12;
	else if (ani == NINJA_ANI_ATTACK_LEFT || ani == NINJA_ANI_SITATTACK_LEFT)
		pos.x -= 12;
	if (isSit)
		pos.y += 5;

	if (attacked != 0) //Nếu bị đánh thì render nhấp nháy
	{
		Attacked(ani);
		if (attacked % 2 == 0)
		{
			animations[ani]->Render(pos.x, pos.y, alpha);
		}
		else
			animations[ani]->Render(pos.x, pos.y, alpha - 100);
	}
	else //còn không bị đánh thì bình thường
		animations[ani]->Render(pos.x, pos.y, alpha);
	//DebugOut(L"%d\n", attacked);
	this->RenderBoundingBox();
}

//Render state

void CNinja::Jump(int & ani)
{
	//Jump and Hit
	if (isHit != 0)
	{
		if (isUp)//Skill đặc biệt
		{
			if (nx > 0)
				ani = NINJA_ANI_THROW_RIGHT;
			else
				ani = NINJA_ANI_THROW_LEFT;

		}
		else//Danh binh thuong
		{
			if (nx < 0)
				ani = NINJA_ANI_ATTACK_LEFT;
			else
				ani = NINJA_ANI_ATTACK_RIGHT;
		}
		isHit++;
		if (isHit >= 8)
			isHit = 0;
	}
	//Nếu k đánh thì nhảy thôi
	else
	{
		if (nx >= 0)
			ani = NINJA_ANI_JUMP_RIGHT;
		else
			ani = NINJA_ANI_JUMP_LEFT;
	}
}

void CNinja::Sit(int &ani)
{
	if (isHit)//Ngoi danh
	{
		if (nx<0)
			ani = NINJA_ANI_SITATTACK_LEFT;
		else
			ani = NINJA_ANI_SITATTACK_RIGHT;
		isHit++;
		if (isHit >= 8)
			isHit = 0;
	}
	else//Ngoi binh thuong
	{
		if (nx < 0)
			ani = NINJA_ANI_SIT_LEFT;
		else
			ani = NINJA_ANI_SIT_RIGHT;
	}
}

void CNinja::OnWall(int & ani)
{
	vy = 0;
	if (canClimbUpDown)//Nếu được leo
	{
		if (isUp)
		{
			vy = NINJA_CLIMB_SPEED;
			if (nx > 0)
				ani = NINJA_ANI_CLIMB_RIGHT;
			else
				ani = NINJA_ANI_CLIMB_LEFT;
		}
		else if (isDown)
		{
			vy = -NINJA_CLIMB_SPEED;
			if (nx > 0)
				ani = NINJA_ANI_CLIMB_RIGHT;
			else
				ani = NINJA_ANI_CLIMB_LEFT;
		}
		else //đứng yên trên tường
		{
			if (nx > 0)
				ani = NINJA_ANI_ONWALL_RIGHT;
			else
				ani = NINJA_ANI_ONWALL_LEFT;
		}
		//DebugOut(L"%d \n", isDown);

	}
	else //đứng yên trên tường
	{
		if (nx > 0)
			ani = NINJA_ANI_ONWALL_RIGHT;
		else
			ani = NINJA_ANI_ONWALL_LEFT;
	}
}

void CNinja::Stand(int & ani)
{
	if (isHit)//Nếu đánh
	{
		if (isUp)//Skill đặc biệt
		{
			if (nx > 0)
				ani = NINJA_ANI_THROW_RIGHT;
			else
				ani = NINJA_ANI_THROW_LEFT;
		}
		else//Danh binh thuong
		{
			if (nx < 0)
				ani = NINJA_ANI_ATTACK_LEFT;
			else
				ani = NINJA_ANI_ATTACK_RIGHT;
		}
		isHit++;
		if (isHit >= 8)
		{
			isHit = 0;
		}
		vx = 0;
	}
	else if (vx != 0)
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

void CNinja::Attacked(int & ani)
{
	if (!isOnWall)
	{
		if (nx < 0)
		{
			this->x += 3;
			ani = NINJA_ANI_ATTACKED_LEFT;
		}

		else
		{
			this->x -= 3;
			ani = NINJA_ANI_ATTACKED_RIGHT;
		}
	}
	else
	{
		if (nx < 0)
		{
			ani = NINJA_ANI_ONWALL_LEFT;
		}
		else
		{
			ani = NINJA_ANI_ONWALL_RIGHT;
		}

	}
	attacked++;
	if (attacked >= 10)
		attacked = 0;
}

#pragma endregion

#pragma region State
//Hàm để set trạng thái khi nhấn phím thôi. Hàm render mới chính
void CNinja::SetState(int state)
{
	CGameObject::SetState(state);

	//isUp = false;
	switch (state)
	{
	case NINJA_STATE_IDLE:
		vx = 0;
		dy = 0;
		isSit = false;
		isUp = false;
		isDown = false;
		break;
	case NINJA_STATE_RUN_RIGHT:
		vx = NINJA_SPEED;
		if(!isOnWall)
			nx = 1;
		isSit = false;
		isUp = false;
		isDown = false;
		break;
	case NINJA_STATE_RUN_LEFT:
		vx = -NINJA_SPEED;
		if (!isOnWall)
			nx = -1;
		isSit = false;
		isUp = false;
		isDown = false;
		break;
	case NINJA_STATE_JUMP:
		if (canJump)
		{
			vy = +ninjaJumpForce;
		}
		onGround = false;
		isJump = 1;
		canJump = false;
		isSit = false;
		canClimbUpDown = false;
		isOnWall = false;
		break;
	case NINJA_STATE_HIT:
		isHit = 1;
		vx = 0;
		break;
	case NINJA_STATE_DOWN:
		isDown = true;
		if(isJump==0&&!isOnWall)
			isSit = 1;
		vx = 0;
		isUp = false;
		if (isOnWall&&onGround)
			isOnWall = false;
		break;
	case NINJA_STATE_UP:
		isUp = true;
		isDown = false;

		break;
	case NINJA_STATE_ONWALL:
		canClimbUpDown = true;
		isOnWall = true;
		break;
	case NINJA_STATE_ATTACKED:
		attacked = 1;
		break;
	}
}
#pragma endregion

#pragma region Load resource

void CNinja::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_NINJA, L"textures\\Ninja.png", D3DCOLOR_XRGB(255, 0, 255));
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
	LPANIMATION ani;
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

	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 0); //Thêm cái ani 100 vào mảng anis của nhân vật ninja => ani 0 = Idle right
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 1);	//ani 1 = run
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 2);	//ani 2 = idle left
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 3);	//ani 3 = run left
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 4);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 5);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 6);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 7);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 8);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 9);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 10);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 11);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 12);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 13);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 14);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 15);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 16);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 17);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 18);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 19);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 20);
	this->AddAnimation(NINJA_ANI_BASE_NUMBER + 21);
	this->SetPosition(50.0f, 0);

}


#pragma endregion


#pragma region Collision

void CNinja::GetBoundingBox(float &x, float &y, float &width, float &height)
{
	if (this->isSit)
	{
		x = this->x;
		y = this->y-12;
		width = NINJA_WIDTH_TMP;
		height = NINJA_HEIGHT_TMP-12;
	}
	else if (this->isHit &&!isOnWall/*&& !this->isSit*/)
	{
		x = this->x;
		y = this->y - 6;
		width = NINJA_WIDTH_TMP;
		height = NINJA_HEIGHT_TMP - 6;
	}
	else if (this->isJump /*&&!this->isHit*/)
	{
		x = this->x;
		y = this->y - 6;
		width = NINJA_WIDTH_TMP;
		height = NINJA_HEIGHT_TMP - 12;
	}
	else
	{
		x = this->x;
		y = this->y;
		width = NINJA_WIDTH_TMP;
		height = NINJA_HEIGHT_TMP;
	}
	
}
unsigned short int CNinja::isCollitionObjectWithObject(CGameObject * obj)
{
	LPCOLLISIONEVENT e = SweptAABBEx(obj); // kt va chạm giữa 2 object bằng sweptAABB
	if (e->t != 0)
	{
		if (e->t > 0 && e->t <= 1.0f)
		{
			if (e->ny > 0)
			{
				//DebugOut(L"Cham duoi chan ninja\n");
				SAFE_DELETE(e);
				return OBJ_COLLISION_BOTTOM;
			}
			else if (e->ny < 0)
			{
				//DebugOut(L"Cham dau ninja\n");
				SAFE_DELETE(e);
				return OBJ_COLLISION_TOP;
			}
			
			if (e->nx > 0)
			{
				//DebugOut(L"Cham ben trai ninja\n");
				SAFE_DELETE(e);
				return OBJ_COLLISION_LEFT;
			}
			if (e->nx <0)
			{
				//DebugOut(L"Cham ben phai ninja\n");
				SAFE_DELETE(e);
				return OBJ_COLLISION_RIGHT;
			}
		}
	}
	return checkAABB(obj);
}

#pragma endregion

