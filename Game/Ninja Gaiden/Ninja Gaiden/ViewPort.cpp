#include "ViewPort.h"


#define MAP1_WIDTH 2048
CViewPort * CViewPort::__instance = NULL;

CViewPort::CViewPort()
{
	x = 0;
	y = 0;

	dx=0;	// dx = vx*dt
	dy=0;	// dy = vy*dt

	vx=0;
	vy=0;

	width = VIEW_PORT_WIDTH;//
	height = VIEW_PORT_HEIGHT;//

}


CViewPort::~CViewPort()
{
}

CViewPort * CViewPort::GetInstance()
{
	if (__instance == NULL)
		__instance = new CViewPort();
	return __instance;
}

void CViewPort::Update(DWORD dt)
{
	dx = vx*dt;
	dy = vy*dt;
	
	if (!(x <0 || x>2048- SCREEN_WIDTH))
	{
		x += dx;
		//y += dy;
	}
	if (x < 0)
	{
		x = 0;
	}
	else if (x > 2048-SCREEN_WIDTH)
	{
		x = 2048- SCREEN_WIDTH;
	}

	if (!(y <0 || y>176 - SCREEN_HEIGHT))
	{
		x += dx;
		//y += dy;
	}
	
	//if (y+176 > SCREEN_HEIGHT)
	//{
	//	//y =  SCREEN_HEIGHT-176-32;
	//}
	//else 
	/*if (y < 0)
	{
		y = 0;
	}*/

	//DebugOut(L"%d , %d \n",x,y);

	//int rightBoundary = (int)(MAP1_WIDTH - SCREEN_WIDTH / 2);//??
	//int leftBoundary = (int)SCREEN_WIDTH / 2;
	//if (xNinja > leftBoundary && xNinja< rightBoundary)
	//{
	//	this->x = xNinja - leftBoundary;
	//}
}

void CViewPort::SetState(int state)
{
	this->state = state;
	if (this->state == VIEW_PORT_STATE_MOVELEFT)
	{
		vx = -VIEW_PORT_SPEED;
	}
	else if (this->state == VIEW_PORT_STATE_MOVERIGHT)
	{
		vx = VIEW_PORT_SPEED;
	}
	else if (this->state == VIEW_PORT_STATE_MOVETOP)
	{
		vy = -VIEW_PORT_SPEED;
	}
	else if (this->state == VIEW_PORT_STATE_MOVEDOWN)
	{
		vy = VIEW_PORT_SPEED;
	}
	else if (this->state == VIEW_PORT_STATE_STOPMOVEHORIZONTAL)
	{
		vx = 0;
	}
	else if (this->state == VIEW_PORT_STATE_STOPMOVEVERTICAL)
	{
		vy = 0;
	}
	else//IDLE
	{
		vx = 0;
		vy = 0;
	}
	//DebugOut(L"filepath: %f , %f\n", vx, vy);
}
void CViewPort::SetData(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
