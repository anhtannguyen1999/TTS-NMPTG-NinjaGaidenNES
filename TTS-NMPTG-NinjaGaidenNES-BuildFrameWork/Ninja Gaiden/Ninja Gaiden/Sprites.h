#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
	//
	D3DXVECTOR2             mScale; // Vector tuy chinh do phong to / thu nho cua texture
	D3DXVECTOR2             mTranslation; //Doi hinh anh vi tri thuc cua Sprite + mTranslate
	D3DXMATRIX              mMatrix; // ma tran cua Spite ho tro trong cac phep hinh hoc
	D3DXVECTOR2             mRotationCenter; // diem trung tam trong phep xoay hinh (origin vector)
	float                   mRotation; // goc quay cua Sprite tinh theo radian

public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, 
		D3DXVECTOR2 rotationCenter, D3DXVECTOR2 translation, D3DXVECTOR2 scale, float rotation);

	void Draw(float x, float y, int alpha = 255);
	
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 translation, D3DXVECTOR2 scale, float rotation);
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha=255);
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

