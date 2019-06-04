#pragma once
#include "Game.h" 
#include "Sprites.h"  
#include "define.h"
#include "Ground.h"
#include "NguoiCamKiem.h"
#include "Hawk.h"
#include <fstream>
#include <string>
#include "Ninja.h"
#include "Bat.h"
#include "Panther.h"
#include "CCloak.h"
#include "CCommando.h"
#include "CGunner.h"
#include "CRunner.h"
#include "Wall.h"
#include "Butterfly.h"
#include "Bird.h"
#include "Boss.h"
using namespace std;

class CGrid
{
	vector<CGameObject *> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN]; //Mảng 2 chiều chứa danh sach listObj
	string filepath;
	CNinja*ninja = CNinja::GetInstance();
public:
	CGrid();
	~CGrid();
	void SetFile(string str); // Đọc các object từ file
	void LoadGrid();

	CGameObject * CreateNewObject(int id,int type, int x, int y, int w, int h,int miniType,int other);
	void Insert(int id, int type, float x, float y, int w, int h,int miniType,int other); //Thêm object vào grid
	void GetListObject(vector<CGameObject*>& listBackgroundObj, vector<CGameObject*> & listOtherObj, CCamera * camera);// lấy hết các object "còn Alive" trong vùng camera;
	//void ActiveObj()
};

