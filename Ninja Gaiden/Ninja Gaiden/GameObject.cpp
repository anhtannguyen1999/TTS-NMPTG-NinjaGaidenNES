#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}



void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}


CGameObject::~CGameObject()
{

}