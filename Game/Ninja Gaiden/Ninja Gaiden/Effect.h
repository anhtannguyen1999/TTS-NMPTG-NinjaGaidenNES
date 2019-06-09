#pragma once
//#include "define.h"

//#include <Windows.h>
//#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
#include "Camera.h"
struct EffectElement
{
	//LPANIMATION animations;
	int animationID;
	int timeRender=0;
	int x=0, y=0;
};
class CEffect
{
	static CEffect *__instance;
	vector<LPANIMATION>animations;
	vector<EffectElement> arrEffect;
	CCamera *camera = CCamera::GetInstance();

public:
	static CEffect * GetInstance();
	void RenderEffect(int effectID, int x,int y,int time=-1);
	void Render();
	
	CEffect();
	~CEffect();
	void LoadResource();
	void AddAnimation(int aniId);

};


