#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	

	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_BOX, L"textures\\BoxCollision.png", D3DCOLOR_XRGB(255, 163, 177));
	texBoxCollision = textures->Get(ID_TEX_BOX);
	CSprites * sprites = CSprites::GetInstance();
	sprites->Add(ID_SPRITE_BOXCOLLISION, 2, 4, 19 + 2, 34 + 4, texBoxCollision, D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), 0);
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

int CGameObject::checkAABB(CGameObject * obj)
{
	float x, y, w, h;
	float x1, y1, w1, h1;

	this->GetBoundingBox(x, y, w, h);
	obj->GetBoundingBox(x1, y1, w1, h1);
	float left = x1 - (x+w);
	float top = (y1)-(y-h);
	float right = (x1+w1)-x;
	float bottom = (y1-h1) - y;
	
	if (!(left > 0 || right < 0 || top < 0 || bottom>0))
	{
		if (-left < 10)
			return OBJ_COLLISION_RIGHT;
		if (right < 10)
			return OBJ_COLLISION_LEFT;
		if (top < 10)
			return OBJ_COLLISION_BOTTOM;
		if (-bottom < 10)
			return OBJ_COLLISION_TOP;
		//else
		float tmp = min(-left, min(right, min(top, -bottom)));
		if (tmp == -left)
			return OBJ_COLLISION_RIGHT;
		if (right == tmp)
			return OBJ_COLLISION_LEFT;
		if (top == tmp)
			return OBJ_COLLISION_BOTTOM;
		if (-bottom == tmp)
			return OBJ_COLLISION_TOP;

	}
	else
		return OBJ_NO_COLLISION;
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}


CGameObject::~CGameObject()
{

}


#pragma region Collision vs SweptAABB

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sx, sy, sw, sh;		// static object x,y,w,h
	float mx, my, mw, mh;		// moving object
	float t, nx, ny;

	coO->GetBoundingBox(sx, sy, sw, sh); //Lấy vùng xét va chạm của vạt đứng yên
										 // deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	//static d= v*t
	float sdx = svx*dt;
	float sdy = svy*dt;

	//d tương đối khi đổi hệ quy chiếu từ vật chuyển động(static obj) thành đứng yên
	float dx = this->dx - sdx;
	float dy = this->dy - sdy;
	
	GetBoundingBox(mx, my, mw, mh); //Lấy vùng xét va chạm của vât chuyển động
						//xét xem tụi nó có va chạm k

	if (checkAABB(coO)) // kiểm tra va chạm bằng AABB trước
	{
		t = 1.0f;
		ny = 0;
		nx = 0;
	}
	else
	{
		CGameObject::SweptAABB(mx, my, mx+mw, my - mh, dx, dy, sx, sy, sx+sw, sy - sh, t, nx, ny);
	}
	//Trả về 1 sự kiện va chạm
	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	//DebugOut(L"GameObj: %f, %f, %f \n",t,nx,ny);
	return e;
}

void CGameObject::SweptAABB(
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
	
	// Broad-phase test xem frame tiếp có va chạm không!
	float bl=ml, bt=mt, br=mr, bb=mb;
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
		bt+=dy;
		bb = mb;
	}
	else
	{
		bt = mt;
		bb +=dy;
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
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	else if (dy < 0) //đi xuống
	{
		dy_entry = st - mb;
		dy_exit =sb-mt ;
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
	//DebugOut(L"%f, %f, %f, %f ||| %f, %f, %f, %f \n",ml,mt,mr,mb,sl,st,sr,sb);
	//if(t>0 && t<=1.0f)
		//DebugOut(L"%f, %f, %f\n", t, nx, ny);
}

//Tinh toan va loc va cham
/*
void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		//Nếu va chạm ở trục x và thời gian va chạm nhỏ hơn min(đang tìm min)
		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
		}
		//Nếu va chạm ở trục y và thời gian va chạm nhỏ hơn min(đang tìm min)
		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


//tính toán khả năng va chạm đối với các collison Objects
//coObjects: list of colliable objects
//coEvents: list of potential collisions
*/

/*
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		//xét khả năng va chạm vs từng vật thế
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		//Nếu thời gian va chạm từ 0 đến 1 thì thêm nó vào list
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}
*/

void CGameObject::RenderBoundingBox()
{
	float x, y, w, h;
	GetBoundingBox(x, y, w, h);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = w;
	rect.bottom = h;
	
	D3DXVECTOR3 pos = camera->SetPositionInViewPort(D3DXVECTOR3(x, y, 0));

	CTextures * textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texBoxCollision = textures->Get(ID_TEX_BOX);

	CSprites * sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_BOXCOLLISION)->Draw(pos.x, pos.y,w,h, 150);
}


#pragma endregion


