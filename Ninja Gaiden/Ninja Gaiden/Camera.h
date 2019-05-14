#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include "debug.h"
#include "define.h"

class CCamera
{
	static CCamera * __instance;

	int x, y; //Xét theo tọa độ thế giới
	
	int width, height;

	int state;
	
public:
	CCamera();
	~CCamera();
	static CCamera * GetInstance();

	void Update(DWORD dt, int const &ninjaX, int const &ninjaY, int const &mapWidth,int const &mapHeight);
	
	void SetData(int x,int y,int width,int height);

	int GetX() { return this->x; };
	int GetY() { return this->y; };
	int GetWidth() { return this->width; };
	int GetHeight() { return this->height; };
	D3DXVECTOR3 SetPositionInViewPort(D3DXVECTOR3 position); //Nhân ma trận đổi tọa độ world -> viewport 
};

