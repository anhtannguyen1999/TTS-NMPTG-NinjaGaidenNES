#include "ViewPort.h"



CViewPort * CViewPort::__instance = NULL;

CViewPort::CViewPort()
{
	width = VIEW_PORT_WIDTH;//
	height = VIEW_PORT_HEIGHT;//

	x = 0;	//start point x
	y = 0+height;	// start point y+ VP.Height

}


CViewPort::~CViewPort()
{
}

CViewPort * CViewPort::GetInstance()
{
	if (__instance == NULL)
		__instance = new CViewPort();
	return __instance;
}

void CViewPort::Update(DWORD dt, int const &ninjaX, int const &ninjaY, int const &mapWidth, int const &mapHeight)
{
	x = ninjaX-VIEW_PORT_WIDTH/2;
	y = ninjaY+VIEW_PORT_HEIGHT/2;

	if (x < 0)
	{
		x = 0;
	}
	else if (x > mapWidth-SCREEN_WIDTH)
	{
		x = mapWidth - SCREEN_WIDTH;
	}

	//DebugOut(L"ViewPort: %d , %d \n", x, y);

}

void CViewPort::SetData(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}



D3DXVECTOR3 CViewPort::SetPositionInViewPort(D3DXVECTOR3 position)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); //chuyen ma tran mt ve ma tran dong nhat_ Duong cheo=1, con lai =0
	mt._22 = -1.0f;
	mt._41 = -this->x;
	mt._42 = this->y;
	D3DXVECTOR4 vp_pos; //Toa do moi trong viewport //Dung toa do nay de ve 
	D3DXVec3Transform(&vp_pos, &position, &mt);//nhan position voi ma tran trung gian de ra toa do moi

	return D3DXVECTOR3(vp_pos.x, vp_pos.y+ SPACE_FROM_VIEW_PORT_TO_TOP, 0); //+SPACE_FROM_VIEW_PORT_TO_TOP cho khỏi mất khúc trên của map
}
