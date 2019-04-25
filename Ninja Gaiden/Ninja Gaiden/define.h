#pragma once

//Main
#define WINDOW_CLASS_NAME L"NinjaGame"
#define MAIN_WINDOW_TITLE L"NinjaGame"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120


//*************************************
//Ninja
#define NINJA_GRAVITY 0.002f
#define NINJA_SPEED 0.5f
#define NINJA_STATE_IDLE			100
#define NINJA_STATE_RUN_RIGHT	110
#define NINJA_STATE_RUN_LEFT	111

#define NINJA_ANI_IDLE_RIGHT 0
#define NINJA_ANI_RUN_RIGHT 1
#define NINJA_ANI_IDLE_LEFT 2
#define NINJA_ANI_RUN_LEFT 3

#define ID_TEX_NINJA 0

//TileMap
#define ID_TILES_MAP1 10000
#define MAPTILE_SIZE 16
//ViewPort
#define VIEW_PORT_WIDTH 320
#define VIEW_PORT_HEIGHT 224
#define SPACE_FROM_VIEW_PORT_TO_TOP 20 
#define MAP1_WIDTH 2048
