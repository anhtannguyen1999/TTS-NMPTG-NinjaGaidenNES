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
#include "Camera.h"
//using namespace std;
#include "define.h"
typedef vector<vector <int>> Matrix;
typedef vector<int> Row;
class CTileMap
{
	CCamera *camera = CCamera::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	Matrix matrix;
	unordered_map<int, CSprite*> tiles;
	LPCWSTR matrixPath;//matrixPath of matrix
	LPCWSTR tilesPath; //file path of tiles

	void LoadMatrix();
	void LoadTiles();
	int tileWidth, tileHeight;
	int mapWidth, mapHeight;
public:
	CTileMap(LPCWSTR matrixPath, LPCWSTR tilesPath);
	~CTileMap();
	void Render();
	int GetMapWidth() { return mapWidth; };
	int GetMapHeight() { return mapHeight; };

};

