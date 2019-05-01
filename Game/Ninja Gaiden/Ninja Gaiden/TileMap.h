#pragma once
//#include <d3dx9.h>
//#include <d3d9.h>
#include <vector>
//#include <unordered_map> 
//#include <iostream>
#include <fstream>
#include <string>
#include "Sprites.h"
#include "Debug.h"
#include "Textures.h"
#include "ViewPort.h"
//using namespace std;
#define ID_TILES_MAP1 10000
typedef vector<vector <int>> Matrix;
typedef vector<int> Row;
class CTileMap
{
	CViewPort *viewPort = CViewPort::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	Matrix matrix;
	unordered_map<int, CSprite*> tiles;
	LPCWSTR matrixPath;//matrixPath of matrix
	LPCWSTR tilesPath; //file path of tiles

	void LoadMatrix();
	void LoadTiles();
	int tileWidth, tileHeight;
public:
	CTileMap(LPCWSTR matrixPath, LPCWSTR tilesPath);
	~CTileMap();
	void Render();

};

