#include "Ninja.h"
#include "debug.h"
//#include "Game.h"
#include <algorithm>
#include "Textures.h"
#include"Sound.h"


CNinja * CNinja::__instance = NULL;

CNinja * CNinja::GetInstance()
{
	if (__instance == NULL) 
		__instance = new CNinja();
	return __instance;
}


CNinja::CNinja() : CGameObject()
{
	this->LoadResource();
	this->x = this->rootX = 20;
	this->y = this->rootY = 200;
	this->hp = hpMax;
	this->id = 0;
	this->mana = 0;
	this->point = 0;
	this->soMang = 2;
	//ninjaSword = new CNinjaSword();
	//SetSpecialWeapon(WEAPON_MINITYPE_FIRES);
	//isPauseWhenDie = true;
}

CNinja::~CNinja()
{
}

void CNinja::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	//DebugOut(L"HP: %d\n", hp);
	CGameObject::Update(dt);
	//preY = y;
	if (!isPauseWhenDie)
	{
		y += dy;
	}
	//DebugOut(L"IS PAUSE: %d\n", isPauseWhenDie);
	
	//Nếu đang đánh(đánh ở trạng thái đứng chứ k phải nhảy hay ngồi) thì dừng lại trục x.
	//Nếu đang leo tường thì dừng lại trục x
	if (!(isHit != 0 && !isJump && !isSit) && !isOnWall && canMove)
	{
		//Neu khong (bi khoa ben trai va di ve ben trai) va tuong tu ben phai
		if (!(dx >= 0 && !canMoveRight) && !(dx <= 0 && !canMoveLeft))
		{
			if (!isPauseWhenDie)
				x += dx;
		}
	}
	

	if (onGround)//chạm đất
	{
		if (!isJump)//Neu dang cham dat va khong dang nhay
		{
			if (vy < 0)
			{
				vy = 0;
				dy = 0;
			}
		}
		canJump = true;
		
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
	if (this->y < -30) //xet cho khoi rot gay bug thoi 9 // Rot xuong thi ve vach xuat phat
	{
		//this->y = 8;
		SetPosition(10, 200);
		vy = 0; dy = 0;
	}
	CalNinjaSword();

	ninjaSword->Update(dt);		
	if (specialWeapon)
	{
		switch (specialWeapon->GetMiniTypeWeapon())
		{
		case WEAPON_MINITYPE_SMALL_SHURIKEN:
		{
			CSmallShuriken* smallShuriken = dynamic_cast<CSmallShuriken*>(specialWeapon);
			smallShuriken->Update(dt);
			break;
		}
		case WEAPON_MINITYPE_BIG_SHURIKEN:
		{
			CBigShuriken* bigShuriken = dynamic_cast<CBigShuriken*>(specialWeapon);
			bigShuriken->Update(dt,this->x,this->y);
			break;
		}
		case WEAPON_MINITYPE_FIRES:
		{
			CFiresWeapon* bigShuriken = dynamic_cast<CFiresWeapon*>(specialWeapon);
			bigShuriken->Update(dt);
			break;
		}
		}
	}
		

	
	if (isHit != 0)
		isHit++;

	//DebugOut(L"%d \n", hp);

	//Khoa khong cho danh
	if (isHit >= 9 || timeResetHit != 0)
	{
		if (timeResetHit == 9)
		{
			animations[NINJA_ANI_THROW_LEFT]->ResetCurrentFrame();
			animations[NINJA_ANI_THROW_RIGHT]->ResetCurrentFrame();
		}
		isHit = 0;
		timeResetHit++;
		if (timeResetHit > 10)
			timeResetHit = 0;
	}

	
}

void CNinja::CalNinjaSword()
{
	
	//Caculate cho sword	
	if (isHit && !isUp && !isOnWall)
	{
		if (this->attacked > 0 && this->attacked <= 20) //Neu bi danh thi thoi
		{
			return;
		}
		if(ninjaSword->GetActive()==false)//Neu cay kiem chua duoc danh ra thi play sound
			Sound::getInstance()->play(DirectSound_ATTACK_ENEMY);
		if (isSit || isJump)
		{
			if (nx > 0)
			{
				ninjaSword->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 10, nx);
				ninjaSword->SetActive(true);
			}
			else
			{
				ninjaSword->SetPosition(this->x - 22, this->y - 10, nx);
				ninjaSword->SetActive(true);
			}
		}
		else
		{
			if (nx > 0)
			{
				ninjaSword->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 2, nx);
				ninjaSword->SetActive(true);
			}
			else
			{
				ninjaSword->SetPosition(this->x - 22, this->y - 2, nx);
				ninjaSword->SetActive(true);
			}
		}
	}
	else//Caculate cho vu khi khac
	{
		ninjaSword->SetActive(false);

		//Caculate cho vu khi khac	
		if (isHit==1 && isUp && !isOnWall && specialWeapon&&!isSit) //Neu ton tai vu khi khac
		{
			switch (specialWeapon->GetMiniTypeWeapon())
			{
			case WEAPON_MINITYPE_SMALL_SHURIKEN:
			{
				
				CSmallShuriken* smallShuriken = dynamic_cast<CSmallShuriken*>(specialWeapon);
				if (smallShuriken&&smallShuriken->GetManaTieuHao() <= this->mana)
				{
					//Neu chua active thi tien hanh tru mana va active
					if (smallShuriken->GetActive() == false)
					{
						Sound::getInstance()->play(DIRECTSOUND_NINJA_THROW);
						this->mana -= smallShuriken->GetManaTieuHao();
					}
					//DebugOut(L"Mana: %d\n", mana);
					if (isJump)
					{
						if (nx > 0)
						{
							smallShuriken->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y-10, nx);
							//smallShuriken->SetActive(true);
						}
						else
						{
							smallShuriken->SetPosition(this->x , this->y-10, nx);
							//smallShuriken->SetActive(true);
						}
					}
					else
					{
						if (nx > 0)
						{
							smallShuriken->SetPosition(this->x + NINJA_WIDTH_TMP-2, this->y-5, nx);
							//smallShuriken->SetActive(true);
						}
						else
						{
							smallShuriken->SetPosition(this->x, this->y-5, nx);
							//smallShuriken->SetActive(true);
						}
					}
					smallShuriken->SetActive(true);
				}
				break;
			}
			case WEAPON_MINITYPE_BIG_SHURIKEN:
			{
				
				CBigShuriken* bigShuriken = dynamic_cast<CBigShuriken*>(specialWeapon);
				if (bigShuriken&&bigShuriken->GetManaTieuHao() <= this->mana)
				{
					//Neu chua active thi tien hanh tru mana va active
					if (bigShuriken->GetActive() == false)
					{
						Sound::getInstance()->play(DIRECTSOUND_SUBWEAPON_BIG_SHURIKEN);
						this->mana -= bigShuriken->GetManaTieuHao();
					}
					//DebugOut(L"Mana: %d\n", mana);
					if (isJump)
					{
						if (nx > 0)
						{
							bigShuriken->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 10, nx);
							
						}
						else
						{
							bigShuriken->SetPosition(this->x, this->y - 10, nx);
						}
					}
					else
					{
						if (nx > 0)
						{
							bigShuriken->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 5, nx);
						}
						else
						{
							bigShuriken->SetPosition(this->x, this->y - 5, nx);
						}
					}
					bigShuriken->SetActive(true);
				}
				break;
			}
			case WEAPON_MINITYPE_FIRES:
			{
				CFiresWeapon* fires = dynamic_cast<CFiresWeapon*>(specialWeapon);
				if (fires&&fires->GetManaTieuHao() <= this->mana)
				{
					//Neu chua active thi tien hanh tru mana va active
					if (fires->GetActive() == false)
					{
						Sound::getInstance()->play(DIRECTSOUND_SUBWEAPON_FIRE);
						this->mana -= fires->GetManaTieuHao();
					}
					//DebugOut(L"Mana: %d\n", mana);
					if (isJump)
					{
						if (nx > 0)
						{
							fires->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 10, nx);

						}
						else
						{
							fires->SetPosition(this->x, this->y - 10, nx);
						}
					}
					else
					{
						if (nx > 0)
						{
							fires->SetPosition(this->x + NINJA_WIDTH_TMP - 2, this->y - 5, nx);
						}
						else
						{
							fires->SetPosition(this->x, this->y - 5, nx);
						}
					}
					fires->SetActive(true);
				}
				break;
			}
				//default:
				//	break;
			}

		}
	}


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
	if (hp > hpMax)
		hp = hpMax;
	if (hp < 0)
		hp = 0;
}

void CNinja::CongMana(int luongMana)
{
	this->mana += luongMana;
}

void CNinja::CongDiem(int luongPoint)
{
	this->point += luongPoint;
}


void CNinja::SetSpecialWeapon(int minitype)
{
	switch (minitype)
	{
	case WEAPON_MINITYPE_SMALL_SHURIKEN:
		specialWeapon = CSmallShuriken::GetInstance();//new CSmallShuriken();
		break;
	case WEAPON_MINITYPE_BIG_SHURIKEN:
		specialWeapon = CBigShuriken::GetInstance();
		break;
	case WEAPON_MINITYPE_FIRES:
		specialWeapon = CFiresWeapon::GetInstance();
		break;
	default:
		break;
	}


	/*
	if (!this->specialWeapon)//neu chua co vu khi
	{
		switch (minitype)
		{
		case WEAPON_MINITYPE_SMALL_SHURIKEN:
			specialWeapon = CSmallShuriken::GetInstance();
			break;
		default:
			break;
		}
	}
	else if (this->specialWeapon->GetMiniTypeWeapon() != minitype)//neu co vu khi khac
	{
		switch (minitype)
		{
		case WEAPON_MINITYPE_SMALL_SHURIKEN:
			specialWeapon = CSmallShuriken::GetInstance();//new CSmallShuriken();
		default:
			break;
		}
	}
	*/
}

int CNinja::GetTypeItem()
{
	if (specialWeapon)
		return specialWeapon->GetMiniTypeWeapon();
	else
		return 0;
}

void CNinja::ResetVeTrangThaiDau()
{
	this->x = this->rootX;
	this->y = this->rootY;
	this->hp = hpMax;
	canMove = true;
	canMoveLeft = true;
	canMoveRight = true;
	canJump = true;
	isJump = false;
	isSit = false;
	canClimbUpDown = false; //Co 2 loai wall, 1 loai cho leo 1 loai k cho leo
	isOnWall = false;
	canClingOnClimbWall = true;// khi nhay xong co the bam len tuong, khi ngoi xuong thi k the
	isUp = false;//is KeyUp
	isDown = false;
	isHit = 0;
	attacked = 0; //attacked =0 la k bi danh => co the bi danh; attack 0->12: trang thai bay khi bi danh, 12->40: trang thai nhap nhay sau do
	huongAttacked = true; // false la huong con enemy di nguoc Ox => ninja bay ve phia trai
	onGround = false;
	vy = 0;
	vx = 0;
	dy = 0;
	dx = 0;
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

	if (isPauseWhenDie)
	{
		if (nx < 0)
			ani = NINJA_ANI_ATTACKED_LEFT;
		else ani = NINJA_ANI_ATTACKED_RIGHT;
		animations[ani]->Render(pos.x, pos.y, 200);
	}
	else if (attacked != 0 && attacked<20) //Nếu ĐANG bị đánh thì render(k xet trang thai nhap nhay sau danh)
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
	if (specialWeapon)
		specialWeapon->Render();
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
		/*isHit++;
		if (isHit >= 8)
			isHit = 0;*/
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
	if (isHit!=0)//Ngoi danh
	{
		if (nx<0)
			ani = NINJA_ANI_SITATTACK_LEFT;
		else
			ani = NINJA_ANI_SITATTACK_RIGHT;
		
		/*isHit++;
		if (isHit >= 8)
			isHit = 0;*/
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
	if (isHit!=0)//Nếu đánh
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
		/*isHit++;
		if (isHit >= 8)
		{
			isHit = 0;
		}*/
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
	//onGround = false;
	if (!isOnWall)
	{
		if (attacked <= 6)
			//y = y + 3;
			vy = vy+0.05f;
		else //y = y - 3;
			vy -= 0.03f;
		
		if (huongAttacked)// ninja bi bay qua ben phai 
		{
			if (!isOnWall)
			{
				this->x += 2;
			}
				
			//dx = 3;
			ani = NINJA_ANI_ATTACKED_LEFT;
		}
		else
		{
			//dx = -3;
			if (!isOnWall&&canMoveLeft)
			{
				this->x -= 2;
				//DebugOut(L"X: %d\n",this->x);
			}
				
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
void CNinja::SetOnGround(bool onGround)
{
	this->onGround = onGround;
	
}
void CNinja::SetOnWall(bool onWall)
{
	this->isOnWall = onWall;
}


#pragma endregion

#pragma region State
//Hàm để set trạng thái khi nhấn phím thôi. Hàm render mới chính
void CNinja::SetState(int state)
{
	CGameObject::SetState(state);
	if (isPauseWhenDie)
		return;
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
		isDown = false;
		//new
		//canMoveLeft = true;
		break;
	case NINJA_STATE_RUN_LEFT:
		vx = -NINJA_SPEED;
		if (!isOnWall)
			nx = -1;
		isSit = false;
		isDown = false;
		//canMoveRight = true;
		break;
	case NINJA_STATE_JUMP:
		if (canJump)
		{
			//Sound::getInstance()->play(DirectSound_NINJA_JUMP);
			if (isOnWall)
				vy = +NINJA_JUMP_FORCE_ONWALL;
			else
				vy = +NINJA_JUMP_FORCE;
		}
		//Neu dang o tren tuong va vx=0
		//Hoac neu dang o tren tuong va vx cung huong nx thi k cho nhay
		if(isOnWall&&(vx==0||(vx>0&&nx>0||vx<0&&nx<0)))
		{
			vy = 0;
			dy = 0;
		}
		if(canJump&&vy>0) //Xet de play sound
			Sound::getInstance()->play(DirectSound_NINJA_JUMP);
		onGround = false;
		isJump = 1;
		canJump = false;
		isSit = false;
		canClimbUpDown = false;
		isOnWall = false;
		canClingOnClimbWall = true; //Neu nhay thi cho phep bam len tuong
		//DebugOut(L"True\n");
		break;
	case NINJA_STATE_HIT:
		if (!(attacked != 0 && attacked < 20))//Neu khong dang trong trang thai bi danh
		{
			if (timeResetHit == 0)
				isHit = 1;
			vx = 0;
		}
		break;
	case NINJA_STATE_DOWN:
		isDown = true;
		if (isJump == 0 && !isOnWall)
		{
			isSit = true;
		}
		vx = 0;
		//isUp = false;
		if (isOnWall&&onGround) // Neu cham dat thi k cho bam len tuong nua
		{
			//isOnWall = false;
			canClingOnClimbWall = false;
		}
		break;
	case NINJA_STATE_UP:
		isUp = true;
		//isDown = false;
		break;
	case NINJA_STATE_ON_CLIMBING_WALL:
		if (!canClingOnClimbWall)
		{
			isOnWall = false;
			break;
		}
		canClimbUpDown = true;
		isOnWall = true;
		if (isJump)
			isJump = false;
		canJump = true;
		//vx = 0;
		break;
	case NINJA_STATE_ON_CLING_WALL:
		if (onGround)
		{
			isOnWall = false;
			break;
		}
		canClimbUpDown = false;
		isOnWall = true;
		if (isJump)
			isJump = false;
		canJump = true;
		canMoveLeft = false;
		//canMoveRight = false;
		break;
	case NINJA_STATE_ATTACKED:
		Sound::getInstance()->play(NINJA_ATTACKED);
		isHit = false;
		canJump = false;
		ninjaSword->SetActive(false);
		if (attacked==0) // neu co the danh
		{
			attacked = 1;
			if (!isOnWall)
				vy = 0;
		}
		break;
	case NINJA_STATE_STOP_RIGHT:
		if (canMoveRight)
			canMoveRight = false;
		break;
	case NINJA_STATE_STOP_LEFT:
		if (canMoveLeft)
			canMoveLeft = false;
		break;
	case NINJA_STATE_ACTIVE_RIGHT:
		if (!canMoveRight)
			canMoveRight = true;
		break;
	case NINJA_STATE_ACTIVE_LEFT:
		if (!canMoveLeft)
			canMoveLeft = true;
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

