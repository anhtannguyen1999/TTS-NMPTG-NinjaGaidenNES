#pragma once

//Main
#define WINDOW_CLASS_NAME L"NinjaGame"
#define MAIN_WINDOW_TITLE L"NinjaGame"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 260
#define SCREEN_HEIGHT 250

#define MAX_FRAME_RATE 120

#define ALPHA 255
//*************************************
//Sprites
/*
	NINJA: 1xx
	10x: idle
	11x: Run
	12x: climp
	13x: jump
	14x: attack
	15x: jump attack
	16x: throw
	17x: sit attack
	18x
	19x


*/
//Ani
/*
	NINJA:1xx voi xx tu 1 den 15
	Enemy: 2xx, moi enemy 1 it
*/

//Ninja
#define NINJA_GRAVITY 0.0011f//0.001f
#define NINJA_SPEED 0.1f
#define NINJA_CLIMB_SPEED 0.05f
#define NINJA_JUMP_FORCE 0.35f//0.35f
#define NINJA_STATE_IDLE			100
#define NINJA_STATE_RUN_RIGHT	110
#define NINJA_STATE_RUN_LEFT	111
#define NINJA_STATE_JUMP	120
#define NINJA_STATE_DOWN 130 //Co the la leo xuong hoac ngoi xuong
#define NINJA_STATE_HIT 140
#define NINJA_STATE_UP 150
#define NINJA_STATE_ONWALL 160
#define NINJA_STATE_ATTACKED 170

#define NINJA_ANI_BASE_NUMBER 100
#define NINJA_ANI_IDLE_RIGHT 0		//OK
#define NINJA_ANI_RUN_RIGHT 1		//
#define NINJA_ANI_IDLE_LEFT 2		//
#define NINJA_ANI_RUN_LEFT 3		//
#define NINJA_ANI_CLIMB_RIGHT 4		//
#define NINJA_ANI_CLIMB_LEFT 5		//
#define NINJA_ANI_JUMP_RIGHT 6		//
#define NINJA_ANI_JUMP_LEFT 7		//
#define NINJA_ANI_ATTACK_RIGHT 8	//
#define NINJA_ANI_ATTACK_LEFT 9		//
#define NINJA_ANI_JUMPATTACK_RIGHT 10	//
#define NINJA_ANI_JUMPATTACK_LEFT 11	//
#define NINJA_ANI_THROW_RIGHT 12	//Nem phi tieu
#define NINJA_ANI_THROW_LEFT 13		//
#define NINJA_ANI_SITATTACK_RIGHT 14	//
#define NINJA_ANI_SITATTACK_LEFT 15		//
#define NINJA_ANI_SIT_RIGHT 16			//
#define NINJA_ANI_SIT_LEFT 17			//
#define NINJA_ANI_ONWALL_RIGHT 18			//
#define NINJA_ANI_ONWALL_LEFT 19			//
#define NINJA_ANI_ATTACKED_RIGHT 20			//
#define NINJA_ANI_ATTACKED_LEFT 21			//

#define NINJA_WIDTH_TMP 20
#define NINJA_HEIGHT_TMP 33
//Tex
#define ID_TEX_NINJA 1
#define ID_TEX_BOX 2 //box collision
#define ID_TEX_ENEMY 3

#define ID_TILES_MAP1 10000

// Sprite ID
#define ID_SPRITE_BOXCOLLISION 0

//TileMap

#define MAPTILE_SIZE 16

//Camera
#define CAMERA_WIDTH 260
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
#define A_KEY 5
#define L_KEY 6
#define D_KEY 7
//Scene
#define GAME_STAGE_31 1
#define GAME_STAGE_32 2
#define GAME_STAGE_33 3

//Grid
#define GRID_CELL_HEIGHT CAMERA_HEIGHT/2
#define GRID_CELL_WIDTH CAMERA_WIDTH/2
#define GRID_CELL_MAX_COLUMN 30 //MAP1_WIDTH/GRID_CELL_WIDTH+2 // so dong toi da //+2 tha du con hon thieu
#define GRID_CELL_MAX_ROW 4 //MAP1_HEIGHT/GRID_CELL_HEIGHT+2 // so cot toi da

//Type obj
#define TYPE_GROUND 1
#define TYPE_ENEMY 2

//Minitype
#define ENEMY_MINITYPE_NGUOICAMKIEM 1
#define ENEMY_MINITYPE_BAT 3
#define ENEMY_MINITYPE_PANTHER 4
#define ENEMY_MINITYPE_BOSS 5
//ID = type *100+count;

	//TYPE ENEMY
	//
	//
	//
	//
	//
	//
//Collision
#define OBJ_NO_COLLISION 0
#define OBJ_COLLISION_CENTER 1 //Co va cham ma chua biet huong
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

//Enemy
/*
TypeEnemy:
	NguoiCamKiem :1


*/