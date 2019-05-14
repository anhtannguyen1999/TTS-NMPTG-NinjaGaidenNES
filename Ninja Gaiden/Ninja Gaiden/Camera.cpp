#include "Camera.h"



CCamera * CCamera::__instance = NULL;

CCamera::CCamera()
{
	width = CAMERA_WIDTH;//
	height = CAMERA_HEIGHT;//

	x = 0;	//start point x
	y = height-15;	// start point y+ VP.Height

}


CCamera::~CCamera()
{
}

CCamera * CCamera::GetInstance()
{
	if (__instance == NULL)
		__instance = new CCamera();
	return __instance;
}

void CCamera::Update(DWORD dt, int const &ninjaX, int const &ninjaY, int const &mapWidth, int const &mapHeight)
{
	
	//Truyền thống=> đôi lúc sẽ giật
	x = ninjaX-CAMERA_WIDTH/2;
	//y = ninjaY+CAMERA_HEIGHT/2;

	if (x < 0)
	{
		x = 0;
	}
	else if (x > mapWidth-SCREEN_WIDTH)
	{
		x = mapWidth - SCREEN_WIDTH;
	}

	//DebugOut(L"Camera: %d , %d \n", x, y);

}

void CCamera::SetData(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}



D3DXVECTOR3 CCamera::SetPositionInViewPort(D3DXVECTOR3 position)
{
	
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); //chuyen ma tran mt ve ma tran dong nhat_ Duong cheo=1, con lai =0
	mt._22 = -1.0f;
	mt._41 = -this->x;
	mt._42 = this->y;
	D3DXVECTOR4 vp_pos; //Toa do moi trong viewport //Dung toa do nay de ve 
	D3DXVec3Transform(&vp_pos, &position, &mt);//nhan position voi ma tran trung gian de ra toa do moi

	return D3DXVECTOR3(vp_pos.x, vp_pos.y+ SPACE_FROM_CAMERA_TO_TOP, 0); //+SPACE_FROM_CAMERA_TO_TOP cho khỏi mất khúc trên của map
}
