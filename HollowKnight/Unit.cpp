#include "Stdafx.h"
#include "Unit.h"

void Unit::hit()
{
	if (_enemy->_isHit) return;
	_enemy->_isHit = true;
	_enemy->_hitTime = _tickCount;
	_enemy->_hp--;

	_enemy->_movingPoint.pos.x = 150;
	_enemy->_movingPoint.tick.x = 10 * (_centerX < _enemy->getCenterX() ? 1 : -1);
	_enemy->_movingPoint.pos.y = 50;
	_enemy->_movingPoint.tick.y = -10;
}

void Unit::init()
{
	_effectManager = new EffectManager;
	IMAGEMANAGER->addImage("hit_orange", L"Resources/Images/Effects/hit_orange.png");
}

void Unit::update()
{
	if (_isDead) {
		_boundBox = { 0,0,0,0 };
		_attackBox = { 0,0,0,0 };
		return;
	}
	_centerX = _boundBox.right - (_boundBox.right - _boundBox.left) / 2;
	_centerY = _boundBox.top + (_boundBox.bottom - _boundBox.top) / 2;

	_tickCount = GetTickCount64();

	if (_movingPoint.pos.x > 0) {
		_pos.x += _movingPoint.tick.x;
		_movingPoint.pos.x -= abs(_movingPoint.tick.x);
		if (_isMoveAttackBox) {
			_attackBox.left += _movingPoint.tick.x;
			_attackBox.right += _movingPoint.tick.x;
		}
	}

	if (_movingPoint.pos.y > 0) {
		_pos.y += _movingPoint.tick.y;
		_movingPoint.pos.y -= abs(_movingPoint.tick.y);
		if (_isMoveAttackBox) {
			_attackBox.left += _movingPoint.tick.y;
			_attackBox.right += _movingPoint.tick.y;
		}
	}

	if (!_isAttack) {
		_attackBox = { 0,0,0,0 };
		for (int i = 0; i < ATK_BOX; i++) {
			_attackBoxList[i] = { 0,0,0,0 };
		}
	}

	if (!_enemy) return;

	// 패링
	if (!_isParrying && IntersectRect(&_hitRc, &_attackBox, &_enemy->_attackBox)) {
		_isParrying = true;
		_parryingTime = _tickCount;
		if (_isPlayer) {
			attackHit();
			if (_up_down == UP) {
				_movingPoint.pos.y = 100;
				_movingPoint.tick.y = 10;
			}
			else if (_up_down == DOWN) {
				_gravity /= 3;
				_animationManager->insertAnimation(AnimState::PLAY, 0, 5, 3, 0, true);
			}
			else {
				_movingPoint.pos.x = 100;
				_movingPoint.tick.x = 10 * (_centerX < _enemy->getCenterX() ? -1 : 1);
			}
		}
	}

	// 적에게 맞기
	if (!_isHit && IntersectRect(&_hitRc, &_boundBox, &_enemy->_attackBox) && !_isParrying) {
		_isHit = true;
		_hitTime = _tickCount;
		_hp--;
		childHit();
			
		if (_enemy->_up_down == DOWN) {
			_movingPoint.pos.y = 100;
			_movingPoint.tick.y = 10;
		}
		else if (_enemy->_up_down == UP) {
			_movingPoint.pos.y = 250;
			_movingPoint.tick.y = -20;
		}
		else {
			_movingPoint.pos.x = 100;
			_movingPoint.tick.x = 5 * (_centerX < _enemy->getCenterX() ? -1 : 1);
		}
		if (_enemy->_isPlayer) {
			_enemy->_hitRc = _hitRc;
			_isParrying;
			_enemy->attackHit();
			if (_enemy->_up_down == UP) {
				if (_enemy->_movingPoint.pos.y < 20) {
					_enemy->_movingPoint.pos.y = 100;
					_enemy->_movingPoint.tick.y = 10;
				}
			}
			else if (_enemy->_up_down == DOWN) {
				if (_enemy->_movingPoint.pos.y < 5) {
					_enemy->_movingPoint.pos.y = 10;
					_enemy->_movingPoint.tick.y = -1;
					_enemy->_gravity /= 3;
					_enemy->_animationManager->insertAnimation(AnimState::PLAY, 0, 5, 3, 0, true);
				}
			}
			else {
				_enemy->_movingPoint.pos.x = 100;
				_enemy->_movingPoint.tick.x = 10 * (_centerX < _enemy->getCenterX() ? 1 : -1);
			}
		}
	}

	

	// 몸통 박치기
	if (!_enemy->_isHit && IntersectRect(&_hitRc, &_boundBox, &_enemy->getBoundBox()) && !_isPlayer) {
		if (_isDead) return;
		_enemy->_isHit = true;
		_enemy->_hitTime = _tickCount;
		_enemy->_hp--;
		_enemy->childHit();
		_enemy->_movingPoint.pos.x = 150;
		_enemy->_movingPoint.tick.x = 10 * (_centerX < _enemy->getCenterX() ? 1 : -1);
	}
	
	if (_isHit && _hitTime + _hitTerm <= _tickCount) {
		_isHit = false;
	}

	if (_isParrying && _parryingTime + _parryingTerm <= _tickCount) {
		_isParrying = false;
	}

	// 적 때리기
	for (int i = 0; i < ATK_BOX; i++) {
		if (IntersectRect(&_hitRc, &getAttackBox(i), &_enemy->_boundBox)) {
			hit();
		}
	}

	if (_hp <= 0) {
		_isDead = true;
	}
}

void Unit::render(HDC hdc)
{
	if (_isDead) return;
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		char str[128];
		wsprintf(str, "x: %d, y: %d, hp: %d", _pos.x, _pos.y, _hp);
		TextOut(hdc, _centerX - 40, _boundBox.top - 15, str, strlen(str));
		if (_isHit) {
			HBRUSH hbr = CreateSolidBrush(RGB(200, 0, 0));
			FillRect(hdc, &_boundBox, hbr);
			DeleteObject(hbr);
		}
		else {
			if(_boundBox.left > 0) RectangleMakeRect(hdc, _boundBox);
		}
		if (_isAttack) {
			HBRUSH hbr = CreateSolidBrush(RGB(189, 189, 189));
			FillRect(hdc, &_attackBox, hbr);
			for (int i = 0; i < ATK_BOX; i++) {
				FillRect(hdc, &_attackBoxList[i], hbr);
			}
			DeleteObject(hbr);
		}
	}
}

Unit::~Unit()
{
	SAFE_DELETE(_img);
	SAFE_DELETE(_animationManager);
	SAFE_DELETE(_effectManager);
}
