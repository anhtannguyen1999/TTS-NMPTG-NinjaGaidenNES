#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "debug.h"
#define VIEW_PORT_WIDTH 320
#define VIEW_PORT_HEIGHT 224

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224

#define VIEW_PORT_STATE_IDLE 11000
#define VIEW_PORT_STATE_MOVELEFT 11001
#define VIEW_PORT_STATE_MOVERIGHT 11002
#define VIEW_PORT_STATE_MOVETOP 11003
#define VIEW_PORT_STATE_MOVEDOWN 11004
#define VIEW_PORT_STATE_STOPMOVEHORIZONTAL 11005
#define VIEW_PORT_STATE_STOPMOVEVERTICAL 11006
#define VIEW_PORT_SPEED 1.0f//0.15f
class CViewPort
{
	static CViewPort * __instance;
	int x, y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int width, height;

	int state;
public:
	CViewPort();
	~CViewPort();
	static CViewPort * GetInstance();
	void Update(DWORD dt);
	void SetState(int state);
	void SetData(int x,int y,int width,int height);
	int GetX() { return this->x; };
	int GetY() { return this->y; };
	int GetWidth() { return this->width; };
	int GetHeight() { return this->height; };
};

