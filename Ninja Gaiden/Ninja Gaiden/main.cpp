#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include"TileMap.h"
#include "ViewPort.h"

#include"Ninja.h"


CGame *game;

CNinja *ninja;

CTileMap * tileMap;
CViewPort *viewPort;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	/*case DIK_UP:
		ninja->SetState(NINJA_STATE_RUN_LEFT);
		break;
	case DIK_SPACE:
		ninja->SetState(SIMON_STATE_HIT);
		break;*/
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	/*switch (KeyCode)
	{
	case DIK_RIGHT:
		viewPort->SetState(VIEW_PORT_STATE_STOPMOVEHORIZONTAL);
		break;
	case DIK_LEFT:
		viewPort->SetState(VIEW_PORT_STATE_STOPMOVEHORIZONTAL);
		break;
	case DIK_UP:
		viewPort->SetState(VIEW_PORT_STATE_STOPMOVEVERTICAL);
		break;
	case DIK_DOWN:
		viewPort->SetState(VIEW_PORT_STATE_STOPMOVEVERTICAL);
		break;
	}*/
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_RIGHT))
	{
		ninja->SetState(NINJA_STATE_RUN_RIGHT);
		//viewPort->SetState(VIEW_PORT_STATE_MOVERIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) 
	{
		ninja->SetState(NINJA_STATE_RUN_LEFT);
		//viewPort->SetState(VIEW_PORT_STATE_MOVELEFT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		//viewPort->SetState(VIEW_PORT_STATE_MOVETOP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		//viewPort->SetState(VIEW_PORT_STATE_MOVEDOWN);
	}
	//else if(game->IsKeyDown(DIK_DOWN))
		//ninja->SetState();
	else
		ninja->SetState(NINJA_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	load textures, sprites, animations and player object
*/
void LoadResources()
{
	ninja = new CNinja();
	objects.push_back(ninja);
	if (tileMap == NULL)
		tileMap = new CTileMap(L"ReSource\\Map1-Matrix.txt", L"ReSource\\Map1-Tiles.png");
	if (viewPort == NULL)
		viewPort = CViewPort::GetInstance();

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	float ninjaX = 0, ninjaY = 0;
	ninja->GetPosition(ninjaX,ninjaY);
	viewPort->Update(dt, ninjaX, ninjaY, tileMap->GetMapWidth(),tileMap->GetMapHeight());
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		tileMap->Render();

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}