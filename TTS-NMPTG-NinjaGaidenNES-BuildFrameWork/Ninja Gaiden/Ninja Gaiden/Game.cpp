#include "Game.h"
#include "debug.h"

CGame * CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for 
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;									

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw 
*/
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r; 
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	HRESULT
		hr = DirectInput8Create
		(
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) 
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	this->keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::ProcessKeyboard()
{
	HRESULT hr; 

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h==DI_OK)
			{ 
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}
	if (keyHandler != NULL)
	{
		keyHandler->KeyState((BYTE *)&keyStates);
	}


	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		if (keyHandler != NULL)
		{
			int KeyCode = keyEvents[i].dwOfs;
			int KeyState = keyEvents[i].dwData;
			if ((KeyState & 0x80) > 0)
				keyHandler->OnKeyDown(KeyCode);
			else
				keyHandler->OnKeyUp(KeyCode);
		}
	}
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}


CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}


//
//#pragma region Collision vs SweptAABB
//
//void CGame::SweptAABB2(
//	float mx, float my, float mw, float mh,
//	float dx, float dy,
//	float sx, float sy, float sw, float sh,
//	float &t, float &nx, float &ny)
//{
//	float dxEntry, dxExit;
//	float dyEntry, dyExit;
//	float txEntry, txExit;
//	float tyEntry, tyExit;
//	t = -1.0f;			// no collision
//	nx = ny = 0;
//
//	// tìm khoảng cách các cạnh tương ứng
//	if (dx > 0.0f)
//	{
//		dxEntry = sx - (mx + mw);//
//		dxExit = (sx + sw) - mx;//
//	}
//	else
//	{
//		dxEntry = (sx + sw) - mx;
//		dxExit = sx - (mx + mw);
//		//dxEntry = (mx) - (sx+sw);
//		//dxExit =  (mx + mw)- sx;
//	}
//
//	if (dy > 0.0f)
//	{
//		/*dyEntry = sy - (my + mh);
//		dyExit = (sy + sh) - my;*/
//		dyEntry = (sy-sh) - (my);
//		dyExit = (sy) - (my-mh);
//	}
//	else
//	{
//		/*dyEntry = (sy +sh) - my;
//		dyExit = sy - (my + mh);*/
//		dyEntry = (sy) - (my - mh);
//		dyExit = (sy - sh) - (my);
//	}
//
//	// tính thời gian từ khoảng cách tính được và vận tốc của đối tượng
//	// vận tốc này là trong 1 frame hình nha
//	if (dx == 0.0f)
//	{
//		// đang đứng yên thì bằng vô cực (chia cho  0)
//		txEntry = -99999999999;
//		txExit = 99999999999;
//	}
//	else
//	{
//		txEntry = dxEntry / dx;
//		txExit = dxExit / dx;
//	}
//
//	if (dy == 0.0f)
//	{
//		tyEntry = - 99999999999;
//		tyExit = 99999999999;
//	}
//	else
//	{
//		tyEntry = dyEntry / dy;
//		tyExit = dyExit / dy;
//	}
//
//	// thời gian va chạm là thời gian lớn nhất của 2 trục (2 trục phải cùng tiếp xúc thì mới va chạm)
//	float entryTime = max(txEntry, tyEntry);
//	// thời gian hết va chạm là thời gian của 2 trục, (1 cái ra khỏi là object hết va chạm)
//	float exitTime = min(txExit, tyExit);
//
//	// kiểm tra nếu không có va chạm thì out
//	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
//	{
//		return;
//	}
//	
//	// lấy hướng va chạm
//	if (txEntry > tyEntry)
//	{
//		if (dxEntry > 0.0f)
//		{
//			nx = -1.0f;
//		}
//		else
//		{
//			nx = 1.0f;
//		}
//	}
//	else
//	{
//		if (dyEntry > 0.0f)
//		{
//			ny = -1.0f;
//		}
//		else
//		{
//			ny = 1.0f;
//		}
//	}
//
//	// có thì lấy thời gian
//	t= entryTime;
//
//}
//
//
///*
//SweptAABB
//*/
//void CGame::SweptAABB(
//	float ml, float mt, float mr, float mb,
//	float dx, float dy,
//	float sl, float st, float sr, float sb,
//	float &t, float &nx, float &ny)
//{
//
//	float dx_entry, dx_exit, tx_entry, tx_exit;
//	float dy_entry, dy_exit, ty_entry, ty_exit;
//
//	float t_entry;
//	float t_exit;
//
//	t = -1.0f;			// no collision
//	nx = ny = 0;
//
//	//
//	// Broad-phase test 
//	//
//
//	float bl = dx > 0 ? ml : ml + dx;
//	float bt = dy > 0 ? mt : mt + dy;
//	float br = dx > 0 ? mr + dx : mr;
//	float bb = dy > 0 ? mb + dy : mb;
//
//	if (br < sl || bl > sr || bb < st || bt > sb) return;
//
//
//	if (dx == 0 && dy == 0) return;		// nếu moving object không di chuyển => không có va chạm
//
//	if (dx > 0)	//tính dx_entry, dx_exit khi moving object qua trái, phải
//	{
//		dx_entry = sl - mr;
//		dx_exit = sr - ml;
//	}
//	else if (dx < 0)
//	{
//		dx_entry = sr - ml;
//		dx_exit = sl - mr;
//	}
//
//	//tính dy_entry, dy_exit khi moving object lên xuống
//	if (dy > 0)
//	{
//		dy_entry = st - mb;
//		dy_exit = sb - mt;
//	}
//	else if (dy < 0)
//	{
//		dy_entry = sb - mt;
//		dy_exit = st - mb;
//	}
//
//	//Nếu moving object k di chuyển theo trục x thì thời gian entry, exit là vô cùng
//	if (dx == 0)
//	{
//		//cho số âm vô cùng để đoạn dưới chọn max sẽ lấy của ty
//		tx_entry = -99999999999;
//		//cho số dương vô cùng để đoạn dưới chọn min sẽ lấy của ty
//		tx_exit = 99999999999;
//	}
//	else //t=D/v
//	{
//		tx_entry = dx_entry / dx;
//		tx_exit = dx_exit / dx;
//	}
//
//	//Nếu moving object k di chuyển theo trục y thì thời gian entry, exit là vô cùng
//	if (dy == 0)
//	{
//		//cho số âm vô cùng để đoạn dưới chọn max sẽ lấy của tx
//		ty_entry = -99999999999;
//		//cho số dương vô cùng để đoạn dưới chọn min sẽ lấy của tx
//		ty_exit = 99999999999;
//	}
//	else //t=D/v
//	{
//		ty_entry = dy_entry / dy;
//		ty_exit = dy_exit / dy;
//	}
//
//	//Nếu không có cái nào nằm trong khoảng từ 0->1 thì k có va chạm
//	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;
//
//	//chọn max, min để xem nó va chạm theo trục nào
//	t_entry = max(tx_entry, ty_entry);
//	t_exit = min(tx_exit, ty_exit);
//
//	// !(thời gian vào<thời gian ra thì k có va chạm) 
//	if (t_entry > t_exit) return;
//
//	t = t_entry;
//
//	//Nếu tx_entry > ty_entry => va chạm xảy ra ở trục x
//	if (tx_entry > ty_entry)
//	{
//		ny = 0.0f;
//		//nếu dx>0 (đi qua phải) => trả về -1 là chạm ở bên trái, ngược lại...
//		dx > 0 ? nx = -1.0f : nx = 1.0f;
//	}
//	else // va chạm xảy ra ở trục y
//	{
//		nx = 0.0f;
//		//nếu dy>0 (đi xuống) => trả về -1 là chạm ở trên, ngược lại...
//		dy > 0 ? ny = -1.0f : ny = 1.0f;
//	}
//}
///*
void CGame::SweptAABB(
	float ml, float mt, float mr, float mb, //Moving obj left, top, right, bottom
	float dx, float dy,						//dx dy of Moving obj
	float sl, float st, float sr, float sb, // left, top right bottom of static obj
	float &t, float &nx, float &ny)			//nx, ny để xác định vị trí va chạm: nx =-1 là ở trái,0 : k có chạm ngang, 1: chạm ở phải
											//ny=-1: chạm trên, 0: k chạm, 1: chạm ở dưới
											// t sẽ lấy thời gian va chạm (t_entry)
{
	//DebugOut(L"%f, %f, %f, %f ||| %f, %f, %f, %f \n",ml,mt,mr,mb,sl,st,sr,sb);
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test xem frame tiếp có va chạm không!
	//
	float bl = ml, bt = mt, br = mr, bb = mb;
	if (dx > 0)
	{
		br += dx;
	}
	else
	{
		bl += dx;
	}
	if (dy > 0)
	{
		bt += dy;
		bb = mb;
	}
	else
	{
		bt = mt;
		bb += dy;

	}

	if (br < sl || bl > sr || bb > st || bt < sb)
		return;

	if (dx == 0 && dy == 0)
	{
		return;		// nếu moving object không di chuyển => không có va chạm

	}

	if (dx > 0)	//tính dx_entry, dx_exit khi moving object qua trái, phải
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)//Di phai qua trai
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}

	//tính dy_entry, dy_exit khi moving object lên xuống
	if (dy > 0)
	{
		//dy_entry = st - mb;
		//dy_exit = sb - mt;
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	else if (dy < 0) //đi xuống
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}

	//Nếu moving object k di chuyển theo trục x thì thời gian entry, exit là vô cùng
	if (dx == 0)
	{
		//cho số âm vô cùng để đoạn dưới chọn max sẽ lấy của ty
		tx_entry = -99999999999;
		//cho số dương vô cùng để đoạn dưới chọn min sẽ lấy của ty
		tx_exit = 99999999999;
	}
	else //t=D/v
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;

	}
	//DebugOut(L"%f, %f \n", tx_entry, tx_exit);
	//Nếu moving object k di chuyển theo trục y thì thời gian entry, exit là vô cùng
	if (dy == 0)
	{
		//cho số âm vô cùng để đoạn dưới chọn max sẽ lấy của tx
		ty_entry = -99999999999;
		//cho số dương vô cùng để đoạn dưới chọn min sẽ lấy của tx
		ty_exit = 99999999999;
	}
	else //t=D/v
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}
	//DebugOut(L"%f, %f \n", ty_entry, ty_exit);

	//Nếu không có cái nào nằm trong khoảng từ 0->1 thì k có va chạm
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f)
		return;

	//chọn max, min để xem nó va chạm theo trục nào
	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	//DebugOut(L"dx: %f,dy: %f \n", dx, dy);
	// !(thời gian vào<thời gian ra thì k có va chạm) 
	if (t_entry > t_exit)
	{
		return;
	}

	t = t_entry;

	//Nếu tx_entry > ty_entry => va chạm xảy ra ở trục x
	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		//nếu dx>0 (đi qua phải) => trả về -1 là chạm ở bên trái, ngược lại...
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else // va chạm xảy ra ở trục y
	{
		nx = 0.0f;
		//nếu dy>0 (đi xuống) => trả về -1 là chạm ở trên, ngược lại...
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

	//Test
	//DebugOut(L"%f, %f ||| %f, %f \n", mt, mb, st, sb);
	DebugOut(L"%f, %f, %f, %f ||| %f, %f, %f, %f \n", ml, mt, mr, mb, sl, st, sr, sb);
	if (t>0 && t <= 1.0f)
		DebugOut(L"%f, %f, %f\n", t, nx, ny);
}

//#pragma endregion






//Sweppaabb





