#include "Stdafx.h"
#include "Hiveling.h"

void Hiveling::init(int x, int y, int idx, Unit* enemy)
{
	Unit::init();
	IMAGEMANAGER->addFrameImage("Hiveling_up", "Resources/Images/Unit/Hiveling_up.bmp", 310, 103, 3, 1, true, MAGENTA);
	_img = IMAGEMANAGER->addFrameImage("Hiveling_down", "Resources/Images/Unit/Hiveling_down.bmp", 310, 103, 3, 1, true, MAGENTA);

	_pos.x = x;
	_pos.y = y;
	_isUp = true;
	_enemy = enemy;
	_isDead = false;
	_idx = idx;

	_hp = 5;
}

void Hiveling::update()
{
	Unit::update();
	if (_isDead) return;
	_boundBox = {_pos.x-40, _pos.y, _pos.x + 45, _pos.y + 100};
	if (_isUp) {
		_pos.y -= 10;
	}
	else {
		_pos.y += 10;
	}
	if (_pos.y < -345 * (_idx + 1)) {
		_isUp = false;
	}
	if (_pos.y < -345) {
		_pos.x = _enemy->getCenterX();
	}
	if (_pos.y > WINSIZE_Y + 345) {
		_isDead = true;
	}
}

void Hiveling::render(HDC hdc)
{
	Unit::render(hdc);

	if (_isDead) {
		return;
	}
	if (_isUp && _pos.y > WINSIZE_Y - 340) {
		return;
	}
	if (_isUp) {
		IMAGEMANAGER->frameRender("Hiveling_up", hdc, _pos.x - 45, _pos.y, 8);
	}
	else {
		IMAGEMANAGER->frameRender("Hiveling_down", hdc, _pos.x - 45, _pos.y, 8);
	}
}
