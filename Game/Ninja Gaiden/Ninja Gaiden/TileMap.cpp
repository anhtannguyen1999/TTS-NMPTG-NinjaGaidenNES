#include "TileMap.h"

//Lấy dữ liệu đọc chuyển thành dòng trong ma trận
Row ConvertToRow(string line)
{
	size_t pos = 0;
	string token;
	Row result = Row();
	while ((pos = line.find(" ")) != string::npos)
	{
		token = line.substr(0, pos);
		result.push_back(stoi(token));
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

void CTileMap::LoadMatrix()
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
}



void CTileMap::LoadTiles()
{
	
	HRESULT result;
	//Thông tin tileset
	D3DXIMAGE_INFO info;

	//lấy texture
	result = D3DXGetImageInfoFromFile(tilesPath, &info);
	//Check lỗi
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] Load Map Tileset failed: %s\n", tilesPath);
		return;
	}
	this->tileWidth = info.Width / 16;
	this->tileHeight = info.Height / 16;

	//this->mapWidth = info.Width;
	//this->mapHeight = info.Height;

	tiles[0] = 0;
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TILES_MAP1, tilesPath, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texMap1 = textures->Get(ID_TILES_MAP1);
	D3DXVECTOR2 zero = D3DXVECTOR2(0, 0);
	for (int i = 0; i < this->tileHeight * this->tileWidth; i++)
	{
		int left = (i % this->tileWidth) * 16;
		int right = left + 16;
		int top = (i / this->tileWidth) * 16;
		int bottom = top + 16;
		sprites->Add(ID_TILES_MAP1 + i+1, left, top, right, bottom, texMap1, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), 0);
		
	}
}

void CTileMap::Render()
{
	for (int i = 0; i <matrix.size(); i++) //size: 11 dòng
	{
		//if (i * 16 >= viewPort->GetY() -16 && i * 16 <= viewPort->GetY() + viewPort->GetHeight() +16 )//Nếu vùng nằm trong height viewport thì mới được vẽ
		
		{
			Row curRow = matrix[i];

			for (int j = 0; j < curRow.size(); j++) //size: 128 cột mỗi dòng
			{
				if (j * 16 >= viewPort->GetX() - 16 && j * 16 <= viewPort->GetX() + viewPort->GetWidth())//Nếu vùng nằm trong width viewport thì mới được vẽ
				{
					if (curRow[j] != 0)
					{
						int number = curRow[j];
						sprites->Get(ID_TILES_MAP1 + number)->Draw(j * 16 - viewPort->GetX(), i * 16+16 - viewPort->GetY());
					}
				}
			}

		}
	}
}
