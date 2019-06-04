#include "Weapon.h"
class CBigShuriken : public CWeapon
{
	static CBigShuriken *__instance;

	bool moveLeft = true; //=true la sang trai, false la sang phai
	int bienDoX = 150; //Bien do A cua giao dong lo xo theo truc x
	int tamGiaoDongX = 0;
	bool moveDown = true; //=true la di xuong, false la di len
	bool dangGiaoDongX = true;

	
public:
	CBigShuriken();
	~CBigShuriken();
	static CBigShuriken * GetInstance();
	void Update(DWORD dt, int ninjaX, int ninjaY);
	void Render();
	void SetPosition(float x, float y, int nx);

	void GiaoDongQuanhNinja(int ninjaX,int ninjaY);
	virtual void BienMatKhiChamEnemy() {};//Khong bi bien mat

};
