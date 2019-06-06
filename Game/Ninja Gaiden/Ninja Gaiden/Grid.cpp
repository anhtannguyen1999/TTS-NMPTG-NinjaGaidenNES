#include "Grid.h"



CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}

void CGrid::SetFile(string str)
{
	this->filepath = str;
}

void CGrid::LoadGrid()
{
	//VD man 1 qua man 2 can clear lai
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
			cells[i][j].clear();

	int id, type, w, h, n, miniType, other=0;//miniType là type trong type...VD Type enemy gồm nhiều miniType như Người cầm kiếm, dơi, báo...
	float x, y;

	string firstLine;

	ifstream fileGrid;
	fileGrid.open(filepath);
	if (fileGrid.is_open())
	{
		getline(fileGrid, firstLine); //Bỏ cái dòng đầu đi vì đọc số nguyên k được đâu
		getline(fileGrid, firstLine);
		n = stoi(firstLine);

		string line;
		
		size_t pos = 0;
		string number;
		int j = 0;

		for (int i = 0; i < n; i++)
		{
			getline(fileGrid, line);
			while ((pos = line.find(" ")) != string::npos)
			{
				number = line.substr(0, pos);
				switch (j)
				{
				case 0:
					id = stoi(number);
					break;
				case 1:
					type = stoi(number);
					break;
				case 2:
					x = stoi(number);
					break;
				case 3:
					y = stoi(number);
					break;
				case 4:
					w = stoi(number);
					break;
				case 5:
					h = stoi(number);
					break;
				case 6:
					miniType = stoi(number);
				case 7:
					other = stoi(number);
				default:
					break;
				}
				line.erase(0, pos + 1);
				j++;
			}
			//doc tung cai va insert no vao
			Insert(id, type, x, y, w, h,miniType,other);
			j = 0;
		}
		fileGrid.close();
	}

}

CGameObject * CGrid::CreateNewObject(int id, int type, int x, int y, int w, int h,int miniType, int other)
{
	switch (type)
	{

	case TYPE_GROUND:
		return new CGround(x,y,w,h,miniType);
	case TYPE_WALL:
		return new CWall(x, y, w, h, miniType);
	case TYPE_ENEMY:
	{
		switch (miniType)
		{
		case ENEMY_MINITYPE_NGUOICAMKIEM:
			return new CNguoiCamKiem(id,x, y);
		case ENEMY_MINITYPE_HAWK:
			return new CHawk(id, x, y);
		case ENEMY_MINITYPE_BAT:
			return new CBat(id, x, y,other);
		case ENEMY_MINITYPE_PANTHER:
			return new CPanther(id, x, y,other);
		case ENEMY_MINITYPE_CLOAK:
			return new CCloak(id, x, y);
		case ENEMY_MINITYPE_COMMANDO:
			return new CCommando(id, x, y);
		case ENEMY_MINITYPE_GUNNER:
			return new CGunner(id, x, y);
		case ENEMY_MINITYPE_RUNNER:
			return new CRunner(id, x, y);
		case CONTAINER_MINITYPE_BUTTERFLY:
			return new Butterfly(id, x, y, other);
		case CONTAINER_MINITYPE_BIRD:
			return new Bird(id, x, y, other);
		case ENEMY_MINITYPE_BOSS:
			return  CBoss::GetInstance(id,x,y);
		}

		return NULL;
	}
		

	}
	return NULL;
}

//Tạo obj và thêm 
void CGrid::Insert(int id, int type, float x, float y, int w, int h,int miniType,int other)
{
	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y - h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	CGameObject * obj = CreateNewObject(id, type, x, y, w, h, miniType,other);
	if (obj == NULL)
		return;

	obj->SetId(id);
	obj->SetType(type);

	for (int i = bottom; i <= top; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
}


// lấy hết các object "còn Alive" trong vùng camera;
void CGrid::GetListObject(vector<CGameObject*> & listBackgroundObj, vector<CGameObject*> &listOtherObj,CCamera * camera)
{
	listBackgroundObj.clear();
	listOtherObj.clear();
	//Danh sách các Cell bị camera đè lên
	int top = (int)(camera->GetY() / GRID_CELL_HEIGHT); 
	int bottom = (int)((camera->GetY() - camera->GetHeight()) / GRID_CELL_HEIGHT); //CELL HEIGHT 112
	int left = (int)(camera->GetX() / GRID_CELL_WIDTH);
	int right = (int)((camera->GetX() + camera->GetWidth()) / GRID_CELL_WIDTH); //CELL WIDTH 160
	//Duyệt từng cái
	for (int i = bottom; i <= top; i++)
		for (int j = left; j <= right; j++)
			for (UINT k = 0; k < cells[i][j].size(); k++) //Duyệt từng obj trong cell đó
			{
				if (cells[i][j].at(k)->GetHP() > 0|| cells[i][j].at(k)->GetHP() == -100) // còn tồn tại&& -100 de xet trang thay boss khi chet chua bien mat
				{
					if (cells[i][j].at(k)->typeObj == TYPE_GROUND)
						listBackgroundObj.push_back(cells[i][j].at(k));

					else if (cells[i][j].at(k)->typeObj == TYPE_WALL)
						listBackgroundObj.push_back(cells[i][j].at(k));

					else if (cells[i][j].at(k)->typeObj == TYPE_ENEMY)
						listOtherObj.push_back(cells[i][j].at(k));
				}
				else//Neu HP=0
				{
					if (((ninja->x > cells[i][j].at(k)->x - CAMERA_WIDTH / 2 + 15 && ninja->x < cells[i][j].at(k)->x - CAMERA_WIDTH / 2 + 17) //Khoang ninja so voi obj ben phai
						|| (ninja->x > cells[i][j].at(k)->x + CAMERA_WIDTH / 2 - 22 && ninja->x < cells[i][j].at(k)->x + CAMERA_WIDTH / 2 - 20))//Khoang ninja so voi obj ben trai
						)	//&& (ninja->nx >0/*== cells[i][j].at(k)->rootNX*/)) //va nịna di ve ben phai thi active
					{
						if (cells[i][j].at(k)->typeObj == TYPE_ENEMY)
						{
							CEnemy* enemy = dynamic_cast<CEnemy*>(cells[i][j].at(k));
							if (enemy->GetTypeEnemy() != ENEMY_MINITYPE_PANTHER&&enemy->GetTypeEnemy() != ENEMY_MINITYPE_BAT)
							{
								cells[i][j].at(k)->SetHP(1);
								listOtherObj.push_back(cells[i][j].at(k));
							}
							else if (enemy->rootNX > 0 && ninja->x > enemy->x
								|| enemy->rootNX < 0 && ninja->x < enemy->x)//neu la panther or Bat va ninja nam dung huong root
							{
								cells[i][j].at(k)->SetHP(1);
								listOtherObj.push_back(cells[i][j].at(k));
							}
						}


					}
				}
			}
	
#pragma region Deactivate

	//Duyệt và deavtive từng object ở cell trước		
	for (UINT k = 0; k < cells[bottom][left-1].size(); k++) //Duyệt từng obj trong cell ở trước
	{
		if (left - 1< 0)
			break;
		if (cells[bottom][left - 1].at(k)->typeObj == TYPE_ENEMY) // nếu là enemy thì hủy nó đi
		{
			if (cells[bottom][left - 1].at(k)->GetHP() > 0)
			{
				CEnemy*enemy = dynamic_cast<CEnemy*>(cells[bottom][left - 1].at(k));
				enemy->DeActivate();
			}
		}
	}
	//Duyệt và deavtive từng object ở cell sau
	for (UINT k = 0; k < cells[bottom][right+ 1].size(); k++) 
	{
		if (cells[bottom][right + 1].size() <= 0)
			break;
		if (cells[bottom][right + 1].at(k)->typeObj == TYPE_ENEMY) // nếu là enemy thì hủy nó đi
		{
			if (cells[bottom][right + 1].at(k)->GetHP() > 0)
			{
				CEnemy*enemy = dynamic_cast<CEnemy*>(cells[bottom][right + 1].at(k));
				enemy->DeActivate();
			}
		}
	}

#pragma endregion

}
