#include "Stdafx.h"
#include "ThornBall.h"

ThornBall::ThornBall()
{
	IMAGEMANAGER->addImage("thorn", L"Resources/Images/Object/Thorn.png");
}

ThornBall::~ThornBall()
{
	SAFE_DELETE(_img);
}

void ThornBall::init(int x, int y, int idx, Unit* enemy)
{
	Unit::init();
	_img = IMAGEMANAGER->addFrameImage("ball" + idx, L"Resources/Images/Object/Thorn_ball.png", 4, 3);
	_imgW = _img->getFrameWidth();
	_imgH = _img->getFrameHeight();
	_idx = idx;
	_pos.x = x;
	_pos.y = WINSIZE_Y + 100;
	_movePos.x = x;
	_movePos.y = y;
	_isEndPattern = _isShoot = _isReady = false;
	_enemy = enemy;
	_img->setFrameY(0, 4, 0);

	_dir = 1;
	_boundBox = { _pos.x, _pos.y, _pos.x + 50, _pos.y + 50 };

	_hp = 5;
}

void ThornBall::update()
{
	Unit::update();
	if (_isEndPattern) return;
	if (!_isShoot && _pos.y > _movePos.y) {
		_pos.y -= 20;
		for (int i = 0; i < 8; i++) {
			_thorn[i].pos.y -= 20;
		}
	}
	else {
		if (!_isReady) {
			_time = _tickCount;
			_tick = 2000;
			_img->setFrameY(1, 4, 3);
			_time2 = _time;
			_tick3 = 100;
		}
		_isReady = true;
	}

	if (_isReady) {
		_boundBox = { _pos.x - 50, _pos.y - 50, _pos.x + 50, _pos.y + 50 };
	}

	if (_isReady && _time + _tick2 <= _tickCount) { 
		if (!_isShoot && _time2 + _tick3 <= _tickCount) { // ½î±âÀü Èçµé±â
			_time2 = _tickCount;
			_pos.x += 3 * _dir;
			_pos.y -= 3 * _dir;
			_dir *= -1;
		}
	}

	if (_isHit || _isReady && _time + _tick <= _tickCount) {
		if (_movingPoint.pos.x > 0 || _movingPoint.pos.y > 0) {
			_tick = 0;
			return;
		}
		if (!_isShoot) {
			float angle = PI / 4;
			for (int i = 0; i < 8; i++) {
				_thorn[i].angle = angle * i;
				_thorn[i].pos.x = cos(angle * i) * 25 + _pos.x;
				_thorn[i].pos.y = sin(angle * i) * 25 + _pos.y;
			}
			_img->setFrameY(2, 2, 1);
			_pos.y = WINSIZE_Y + 100;
		}
		_isAttack = true;
		_isShoot = true;
		_isEndPattern = true;
		for (int i = 0; i < 8; i++) {
			_attackBoxList[i] = RectMakeCenter(_thorn[i].pos.x, _thorn[i].pos.y, 10, 10);
			_thorn[i].pos.x += cos(_thorn[i].angle) * 10;
			_thorn[i].pos.y += sin(_thorn[i].angle) * 10;
			if (_thorn[i].pos.x > -33 && _thorn[i].pos.x < WINSIZE_X + 33 &&
				_thorn[i].pos.y > -33 && _thorn[i].pos.y < WINSIZE_Y + 33) {
				_isEndPattern = false;
			}
		}
	}
}

void ThornBall::render(HDC hdc)
{
	Unit::render(hdc);
	if (_isEndPattern) return;
	//IMAGEMANAGER->plusRender("ball", hdc, _pos.x, _pos.y);

	if (_isShoot) {
		for (int i = 0; i < 8; i++) {
			IMAGEMANAGER->plusRender("thorn", hdc, _thorn[i].pos.x, _thorn[i].pos.y, false, _thorn[i].angle * 180 / PI, true);
		}
	}
	IMAGEMANAGER->plusFrameRender("ball" + _idx, hdc, _pos.x - _imgW / 2, _pos.y - _imgH / 2, 10, true);
}
