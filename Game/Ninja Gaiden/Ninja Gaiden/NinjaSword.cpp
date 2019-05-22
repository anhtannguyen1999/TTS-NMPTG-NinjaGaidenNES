#include "NinjaSword.h"


CNinjaSword * CNinjaSword::__instance = NULL;

CNinjaSword * CNinjaSword::GetInstance()
{
	if (__instance == NULL)
		__instance = new CNinjaSword();
	return __instance;
}

CNinjaSword::CNinjaSword()
{
	this->x = 0;
	this->y = 0;
	width = 22;
	height = 12;

	//Load resource
	//CAnimations * animations = CAnimations::GetInstance();
	this->AddAnimation(301);//Hieu ung no
	
}


CNinjaSword::~CNinjaSword()
{
}

void CNinjaSword::GetBoundingBox(float & x, float & y, float & width, float & height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CNinjaSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (active)
	{
		width = 22;
		height = 12;

	}
	else
	{
		width = 0;
		height = 0;
	}
}

void CNinjaSword::Render()
{
	//this->RenderBoundingBox(180);
	if (danhChetEnemy>0)
	{
		danhChetEnemy++;
		D3DXVECTOR3 pos;
		pos.x = this->x;
		if (this->nx>0)
			pos.x = this->x + this->width;
		else
			pos.x = this->x-this->width;
		pos.y = this->y;
		pos.z = 0;
		pos = camera->SetPositionInViewPort(pos);
		animations[0]->Render(pos.x, pos.y, ALPHA);

		if (danhChetEnemy >= 3)
		{
			danhChetEnemy = 0;
			animations[0]->ResetCurrentFrame();
		}
		//DebugOut(L"Render at: %f %f %f %f %d\n", x, y, pos.x, pos.y,danhChetEnemy);

	}
	

	
}

void CNinjaSword::SetPosition(float x, float y,int nx)
{
	this->x = x, this->y = y; 
	this->nx = nx;
}
