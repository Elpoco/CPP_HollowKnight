#include "Stdafx.h"
#include "HornetWeapon.h"

HornetWeapon::HornetWeapon()
{
	IMAGEMANAGER->addImage("hornet_weapon", L"Resources/Images/Object/hornet_weapon.png");
}

HornetWeapon::~HornetWeapon()
{
}

void HornetWeapon::init(int x, int y, bool isLeft, Unit* enemy)
{
	Unit::init();
	_pos.x = x;
	_pos.y = y;
	_isLeft = isLeft;
	_dir = isLeft ? -1 : 1;
	_enemy = enemy;
	_isThrow = false;
}

void HornetWeapon::update()
{
	Unit::update();
}

void HornetWeapon::render(HDC hdc)
{
	Unit::render(hdc);
	IMAGEMANAGER->plusRender("hornet_weapon", hdc, _pos.x, _pos.y + 40, _isLeft, 0, true);
}

void HornetWeapon::throwWeapon()
{
	_movingPoint.pos.x = 600;
	_movingPoint.tick.x = 30 * _dir;
}

void HornetWeapon::recorverWeapon()
{
	_movingPoint.pos.x = 500;
	_movingPoint.tick.x = 15 * -_dir;
}
