#pragma once
#include "Unit.h"
class HornetWeapon : public Unit
{
private:
	bool _isThrow;

public:
	HornetWeapon();
	~HornetWeapon();

	void init(int x, int y, bool isLeft, Unit* enemy);
	virtual void update();
	virtual void render(HDC hdc);

	void throwWeapon();
	void recorverWeapon();
};

