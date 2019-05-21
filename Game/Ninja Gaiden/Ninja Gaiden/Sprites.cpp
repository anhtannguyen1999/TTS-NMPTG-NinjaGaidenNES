#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex,
	D3DXVECTOR2 rotationCenter, D3DXVECTOR2 translation, D3DXVECTOR2 scale,float rotation)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	//Thêm
	if (rotationCenter != D3DXVECTOR2(0, 0))
		mRotationCenter = rotationCenter;
	else
		mRotationCenter = D3DXVECTOR2((right-left)/2, (bottom-top)/2);

	mTranslation = translation;

	if (scale != D3DXVECTOR2(0, 0))
		mScale = scale;
	else
		mScale = D3DXVECTOR2(1, 1);

	mRotation = rotation;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

//void CSprite::Draw(float x, float y, int alpha)
//{
//	CGame * game = CGame::GetInstance();
//	game->Draw(x, y, texture, left, top, right, bottom, alpha);
//}
void CSprite::Draw(float x, float y, int alpha)
{
	D3DXVECTOR3 inPosition(x, y, 0);
	RECT inSourceRect;
	inSourceRect.left = left;
	inSourceRect.top = top;
	inSourceRect.right = right;
	inSourceRect.bottom = bottom;

	D3DXVECTOR2 inCcale = mScale;
	D3DXVECTOR2 inTranslation = mTranslation;
	D3DXVECTOR2 inRotationCenter = mRotationCenter;
	D3DXVECTOR2 scalingScenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(&mMatrix, &scalingScenter, 0, &inCcale, &inRotationCenter,
		mRotation, &inTranslation);

	D3DXMATRIX oldMatrix;
	CGame * game = CGame::GetInstance();
	game->GetSpriteHandler()->GetTransform(&oldMatrix);
	game->GetSpriteHandler()->SetTransform(&mMatrix);

	D3DXVECTOR3 center = D3DXVECTOR3((right - left) / 2.0, (bottom - top) / 2.0, 0);

	game->GetSpriteHandler()->Draw(texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(alpha, alpha, alpha, alpha)); // nhung pixel nao co mau trang se duoc to mau nay len

	game->GetSpriteHandler()->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
	
}

void CSprite::Draw(float x, float y,float w,float h, int alpha)
{
	D3DXVECTOR3 inPosition(x, y, 0);
	RECT inSourceRect;
	inSourceRect.left = left;
	inSourceRect.top = top;
	inSourceRect.right = w+2;
	inSourceRect.bottom = h+5;

	D3DXVECTOR2 inCcale = mScale;
	D3DXVECTOR2 inTranslation = mTranslation;
	D3DXVECTOR2 inRotationCenter = mRotationCenter;
	D3DXVECTOR2 scalingScenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(&mMatrix, &scalingScenter, 0, &inCcale, &inRotationCenter,
		mRotation, &inTranslation);

	D3DXMATRIX oldMatrix;
	CGame * game = CGame::GetInstance();
	game->GetSpriteHandler()->GetTransform(&oldMatrix);
	game->GetSpriteHandler()->SetTransform(&mMatrix);

	D3DXVECTOR3 center = D3DXVECTOR3((right - left) / 2.0, (bottom - top) / 2.0, 0);

	game->GetSpriteHandler()->Draw(texture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(alpha, alpha, alpha, alpha)); // nhung pixel nao co mau trang se duoc to mau nay len

	game->GetSpriteHandler()->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay

}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 translation, D3DXVECTOR2 scale, float rotation)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, rotationCenter, translation,scale, rotation);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}
	//Thêm
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}

