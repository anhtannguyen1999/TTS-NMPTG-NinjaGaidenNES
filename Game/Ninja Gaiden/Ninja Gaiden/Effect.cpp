#include "Effect.h"

CEffect * CEffect::__instance = NULL;

CEffect * CEffect::GetInstance()
{
	if (__instance == NULL)
		__instance = new CEffect();
	return __instance;
}

void CEffect::RenderEffect(int effectID, int x, int y, int time)
{
	EffectElement eff;
	eff.animationID = effectID;
	if (time == -1)//Khong nhap time
	{
		switch (effectID)
		{
		case 0://hieu ung no
			time = 3;
			break;
		default:
			break;
		}
	}
	eff.timeRender = time;
	eff.x = x;
	eff.y = y;
	arrEffect.push_back(eff);
}

void CEffect::Render()
{
	//DebugOut(L"Size= %d\n", arrEffect.size());
	int i = 0;
	while(i<arrEffect.size())
	{
		if (arrEffect[i].timeRender != 0)
		{
			arrEffect[i].timeRender--;
			int tmp = arrEffect[i].timeRender;
			if (tmp <= 0)
			{
				arrEffect[i].timeRender = 0;
				animations[arrEffect[i].animationID]->ResetCurrentFrame();
				for (int j = i; j < arrEffect.size()-1; j++)
				{
					arrEffect[j] = arrEffect[j + 1];
				}
				arrEffect.pop_back();
				i--;
			}
			else
			{
				//DebugOut(L"time= %d\n", arrEffect[i].timeRender);
				D3DXVECTOR3 pos;
				pos.x = arrEffect[i].x;
				pos.y = arrEffect[i].y;
				pos.z = 0;
				pos = camera->SetPositionInViewPort(pos);
				animations[arrEffect[i].animationID]->Render(pos.x, pos.y, 255);
			}
		}
		i++;
	}
}

CEffect::CEffect()
{
	LoadResource();
}

CEffect::~CEffect()
{
}

void CEffect::LoadResource()
{
	this->AddAnimation(301);//0: Animation no
}

void CEffect::AddAnimation(int aniId)
{
	/*LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	EffectElement eff;
	eff.animations = ani;
	eff.timeRender = 0;
	arrEffect.push_back(eff);*/
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}
