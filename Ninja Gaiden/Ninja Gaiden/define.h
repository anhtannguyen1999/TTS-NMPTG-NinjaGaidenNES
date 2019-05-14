#pragma once

//Main
#define WINDOW_CLASS_NAME L"NinjaGame"
#define MAIN_WINDOW_TITLE L"NinjaGame"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 250

#define MAX_FRAME_RATE 120


//*************************************
//Ninja
#define NINJA_GRAVITY 0.0025f
#define NINJA_SPEED 0.22f
#define NINJA_JUMP_FORCE 0.5f
#define NINJA_STATE_IDLE			100
#define NINJA_STATE_RUN_RIGHT	110
#define NINJA_STATE_RUN_LEFT	111
#define NINJA_STATE_JUMP	120

#define NINJA_ANI_IDLE_RIGHT 0
#define NINJA_ANI_RUN_RIGHT 1
#define NINJA_ANI_IDLE_LEFT 2
#define NINJA_ANI_RUN_LEFT 3

#define NINJA_WIDTH_TMP 20
#define NINJA_HEIGHT_TMP 33
//Tex
#define ID_TEX_NINJA 0
#define ID_TEX_BOX 1
#define ID_TILES_MAP1 10000

// Sprite ID
#define ID_SPRITE_BOXCOLLISION 0

//TileMap

#define MAPTILE_SIZE 16
//Camera
#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 224
#define SPACE_FROM_CAMERA_TO_TOP 20 
#define CAMERA_SPEED NINJA_SPEED
#define MAP1_WIDTH 2048
#define MAP1_HEIGHT 176

//Key
#define NON_KEY 0
#define UP_KEY 1
#define DOWN_KEY 2
#define LEFT_KEY 3
#define RIGHT_KEY 4

//Scene
#define GAME_STAGE_31 1
#define GAME_STAGE_32 2
#define GAME_STAGE_33 3

//Grid
#define GRID_CELL_HEIGHT CAMERA_HEIGHT/2
#define GRID_CELL_WIDTH CAMERA_WIDTH/2
#define GRID_CELL_MAX_COLUMN MAP1_WIDTH/GRID_CELL_WIDTH+2 // so dong toi da //+2 tha du con hon thieu
#define GRID_CELL_MAX_ROW MAP1_HEIGHT/GRID_CELL_HEIGHT+2 // so cot toi da

//Type obj
#define TYPE_GROUND 1
//ID = type *100+count;

//Collision
#define OBJ_NO_COLLISION 0
#define OBJ_HAVE_COLLISION 1 //Co va cham ma chua biet huong
#define OBJ_COLLISION_LEFT 2
#define OBJ_COLLISION_TOP 3
#define OBJ_COLLISION_RIGHT 4
#define OBJ_COLLISION_BOTTOM 5

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

