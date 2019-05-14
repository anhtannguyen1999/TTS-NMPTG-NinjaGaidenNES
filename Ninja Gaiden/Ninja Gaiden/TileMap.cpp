#include "TileMap.h"

//Lấy dữ liệu đọc chuyển thành dòng trong ma trận
Row ConvertToRow(string line)
{
	Row result = Row();
	size_t pos = 0;
	string number;
	
	while ((pos = line.find(" ")) != string::npos)
	{
		number = line.substr(0, pos);
		result.push_back(stoi(number));
		line.erase(0, pos + 1);
	}

	return result;
}

CTileMap::CTileMap(LPCWSTR matrixPath, LPCWSTR tilesPath)
{
	this->matrixPath = matrixPath;
	this->tilesPath = tilesPath;
	LoadMatrix();
	LoadTiles();
}

CTileMap::~CTileMap()
{
}

void CTileMap::LoadMatrix() //Load ngược so với file matrix(chiều dọc)
{
	string firstLine;

	ifstream fileMatrix;
	DebugOut(L"matrixPath: %s\n", matrixPath);
	fileMatrix.open(matrixPath);
	if (fileMatrix.is_open())
	{
		getline(fileMatrix, firstLine); //Lấy dòng đầu tiên // chưa dùng

		string line;
		Row matrixRow;

		this->matrix.clear();

		while (getline(fileMatrix, line)) //Lấy mấy dòng sau trong file
		{
			matrixRow = ConvertToRow(line); //Lọc nó ra chuyển nó về kiểu ROW 
			this->matrix.push_back(matrixRow); //push vào ma trận
		}
		fileMatrix.close();
	}
	
	this->mapHeight = matrix.size()*MAPTILE_SIZE;
	this->mapWidth = matrix[0].size() * MAPTILE_SIZE;
	//DebugOut(L"Map: %d x %d \n", mapWidth,mapHeight);
}

void CTileMap::LoadTiles() //Load file ảnh chứa tiles, cắt ra và lưu vô sprite
{
	D3DXIMAGE_INFO info;
	//lấy texture
	HRESULT result = D3DXGetImageInfoFromFile(tilesPath, &info);

	//Check lỗi
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] Load Map Tileset failed: %s\n", tilesPath);
		return;
	}
	this->tileWidth = info.Width / MAPTILE_SIZE;
	this->tileHeight = info.Height / MAPTILE_SIZE;

	//Load nó vào texture
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TILES_MAP1, tilesPath, D3DCOLOR_XRGB(255, 0, 255));

	//Lấy texture ra
	LPDIRECT3DTEXTURE9 texMap1 = textures->Get(ID_TILES_MAP1);
	
	for (int i = 0; i < this->tileHeight * this->tileWidth; i++) //cắt
	{
		int left = (i % this->tileWidth) * MAPTILE_SIZE;
		int right = left + MAPTILE_SIZE;
		int top = (i / this->tileWidth) * MAPTILE_SIZE;
		int bottom = top + MAPTILE_SIZE;
		sprites->Add(ID_TILES_MAP1 + i+1, left, top, right, bottom, texMap1, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), 0);
	}

}

void CTileMap::Render() //render đọc từ 0 lên, trái qua phải ma trận= đọc từ trên xuống của file => vẽ từ trên xuống
{
	D3DXVECTOR3 pos;
	for (int i = 0; i <matrix.size(); i++) //size: 11 dòng -row
	{
		//if (i * MAPTILE_SIZE >= camera->GetY() -MAPTILE_SIZE && i * MAPTILE_SIZE <= camera->GetY() + camera->GetHeight() +MAPTILE_SIZE )//Nếu vùng nằm trong height viewport thì mới được vẽ
		
		{
			Row curRow = matrix[i];

			for (int j = 0; j < curRow.size(); j++) //size: 128 collumn mỗi dòng
			{
				if (j * MAPTILE_SIZE >= camera->GetX() - MAPTILE_SIZE && j * MAPTILE_SIZE <= camera->GetX() + camera->GetWidth())//Nếu vùng nằm trong width viewport thì mới được vẽ
				{
					if (curRow[j] != 0)
					{
						int number = curRow[j];

						pos.x = j * MAPTILE_SIZE;
						pos.y = (matrix.size() - i +1) * MAPTILE_SIZE;
						pos.z = 0;
						pos = camera->SetPositionInViewPort(pos); //Nhân lại tọa độ viewport
						sprites->Get(ID_TILES_MAP1 + number)->Draw(pos.x, pos.y+5);

						//Vẽ từ trên xuống (4 cái biên sẽ vẽ doi ra 1 khúc (k nhìn thấy trên viewport nhưng vẫn vẽ cho khỏi nháy))
						//sprites->Get(ID_TILES_MAP1 + number)->Draw(j * MAPTILE_SIZE - camera->GetX(), i * MAPTILE_SIZE+MAPTILE_SIZE - camera->GetY());

					}
				}
			}

		}
	}
}
