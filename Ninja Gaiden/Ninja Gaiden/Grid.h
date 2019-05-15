#pragma once
#include "Game.h" 
#include "Sprites.h"  
#include "define.h"
#include "Ground.h"

#include <fstream>
#include <string>
using namespace std;

class CGrid
{
	vector<CGameObject *> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN]; //Mảng 2 chiều chứa listObj
	string filepath;
public:
	CGrid();
	~CGrid();
	void SetFile(string str); // Đọc các object từ file
	void LoadGrid();

	CGameObject * CreateNewObject(int type, int x, int y, int w, int h);
	void Insert(int id, int type, float x, float y, int w, int h); //Thêm object vào grid
	void GetListObject(vector<CGameObject*>& ListObj, CCamera * camera);// lấy hết các object "còn Alive" trong vùng camera;
};

