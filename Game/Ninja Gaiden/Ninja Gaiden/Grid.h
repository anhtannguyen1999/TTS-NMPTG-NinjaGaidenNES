#pragma once
#include "Game.h" 
#include "Sprites.h"  
#include "define.h"
#include "Ground.h"
#include "NguoiCamKiem.h"
#include "Bat.h"
#include "Panther.h"
#include "Boss.h"
#include <fstream>
#include <string>
using namespace std;

class CGrid
{
	vector<CGameObject *> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN]; //Mảng 2 chiều chứa danh sach listObj
	string filepath;
public:
	CGrid();
	~CGrid();
	void SetFile(string str); // Đọc các object từ file
	void LoadGrid();

	CGameObject * CreateNewObject(int id,int type, int x, int y, int w, int h,int miniType);
	void Insert(int id, int type, float x, float y, int w, int h,int miniType); //Thêm object vào grid
	void GetListObject(vector<CGameObject*>& listBackgroundObj, vector<CGameObject*> & listOtherObj, CCamera * camera);// lấy hết các object "còn Alive" trong vùng camera;
};

