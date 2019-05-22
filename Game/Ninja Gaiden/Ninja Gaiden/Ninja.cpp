#include "Ninja.h"
#include "debug.h"
//#include "Game.h"
#include <algorithm>
#include "Textures.h"

CNinja * CNinja::__instance = NULL;

CNinja * CNinja::GetInstance()
{
	if (__instance == NULL) 
		__instance = new CNinja();
	return __instance;
}


CNinja::~CNinja()
{
}

void CNinja::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CGameObject::Update(dt);
	preY = y;
	
	y += dy;
	//Nếu đang đánh(đánh ở trạng thái đứng chứ k phải nhảy hay ngồi) thì dừng lại trục x.
	//Nếu đang leo tường thì dừng lại trục x
	if(!(isHit!=0 && !isJump && !isSit) && !isOnWall && canMove)
		x += dx;

	if (onGround)//chạm đất
	{
		if (!isJump)//Neu dang cham dat va khong dang nhay
		{
			vy = 0;
			dy = 0;
		}
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
	CalNinjaSword();
	//DebugOut(L"%d \n", hp);
	//DebugOut(L"x= %f\n", x);

	ninjaSword->Update(dt);
}


float CNinja::GetPositionX()
{
	return x;
}

void CNinja::BeAttacked(int dame, int xObj) //Toa do x cua Obj
{
	if (attacked == 0)
	{
		if (xObj>x)//neu con enemy nam ben phai con ninja=> Ninja bay ve ben trai
		{
			huongAttacked = false;
		}
		else
			huongAttacked = true;
		this->SetState(NINJA_STATE_ATTACKED);
		hp -= dame;
		if (hp < 0)
			hp = 0;
		canMove = false;
	}
}

void CNinja::CongHP(int luongHP)
{
	this->hp += luongHP;
	if (hp < 0)
		hp = 0;
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

	//int alpha = 255;

	D3DXVECTOR3 pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = 0;
	pos = camera->SetPositionInViewPort(pos); //Nhân lại thành tọa độ trong viewport
											  //Canh số lại để vẽ vì đứa cắt hình bị lệnh
	//DebugOut(L"NINJA at: %f %f %f %f\n", x, y, pos.x, pos.y);

	if (ani == NINJA_ANI_ATTACK_RIGHT || ani == NINJA_ANI_SITATTACK_RIGHT)
		pos.x += 12;
	else if (ani == NINJA_ANI_ATTACK_LEFT || ani == NINJA_ANI_SITATTACK_LEFT)
		pos.x -= 12;
	if (isSit)
		pos.y += 5;

	if (attacked != 0 && attacked<20) //Nếu ĐANG bị đánh thì render(k xet trang thai nhap nhay sau danh)
	{
		Attacked(ani);
		animations[ani]->Render(pos.x, pos.y, ALPHA);
	}
	else //khong o trong trang thai bi danh
	{
		if (attacked >= 20)//trang thai nhap nhay sau khi bi danh
		{
			if (attacked % 2 == 0)
			{
				animations[ani]->Render(pos.x, pos.y, ALPHA);
			}
			else
				animations[ani]->Render(pos.x, pos.y, ALPHA - 100);

			attacked++;
			if (attacked >= 20)
			{
				canMove = true;
			}
			if (attacked >= 60)
				attacked = 0;

		}
		else//trang thai binh thuong
			animations[ani]->Render(pos.x, pos.y, ALPHA);
	}
		
	//DebugOut(L"%d\n", attacked);
	//this->RenderBoundingBox();
	ninjaSword->Render();
	
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
		if (attacked <= 6)
			//y = y + 3;
			vy = vy+0.05f;
		else //y = y - 3;
			vy -= 0.03f;
		if (huongAttacked)// ninja bi bay qua ben phai 
		{
			this->x += 3;
			
			ani = NINJA_ANI_ATTACKED_LEFT;
		}
		else
		{
			this->x -= 3;
			ani = NINJA_ANI_ATTACKED_RIGHT;
		}
		if (attacked < 10)
			this->y += 3;
		else if(attacked<20)
			this->y -= 3;
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
	if (attacked >= 20)
	{
		canMove = true;
	}
	if (attacked >= 60)
		attacked = 0;
	
}
void CNinja::CalNinjaSword()
{
	if (this->attacked > 0 && this->attacked <= 20) //Neu bi danh thi thoi
	{
		return;
	}
		
	if (isHit&&!isUp&&!isOnWall)
	{
		if (isSit||isJump)
		{
			if (nx > 0)
			{
				ninjaSword->SetPosition(this->x + NINJA_WIDTH_TMP-2, this->y-10,nx);
				ninjaSword->SetActive(true);
			}				
			else
			{
				ninjaSword->SetPosition(this->x -22, this->y-10,nx);
				ninjaSword->SetActive(true);
			}
		}
		else
		{
			if (nx > 0)
			{
				ninjaSword->SetPosition(this->x + NINJA_WIDTH_TMP-2, this->y-2,nx);
				ninjaSword->SetActive(true);
			}
			else
			{
				ninjaSword->SetPosition(this->x - 22, this->y-2,nx);
				ninjaSword->SetActive(true);
			}
		}
	}
	else
	{
		ninjaSword->SetActive(false);
	}
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
		if (isJump)
			isJump = false;
		canJump = true;
		break;
	case NINJA_STATE_ATTACKED:
		isHit = false;
		ninjaSword->SetActive(false);
		if (attacked==0) // neu co the danh
		{
			attacked = 1;
			if (!isOnWall)
				vy = 0;
		}
		
		break;
	}
}
#pragma endregion

#pragma region Load resource

void CNinja::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

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

#pragma endregion

