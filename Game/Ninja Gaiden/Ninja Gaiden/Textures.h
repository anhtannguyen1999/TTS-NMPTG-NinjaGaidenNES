#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "Game.h"
using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;
	LPDIRECT3DDEVICE9 d3ddv;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public: 
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures * GetInstance();
};