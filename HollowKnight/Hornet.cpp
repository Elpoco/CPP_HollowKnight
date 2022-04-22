#include "Stdafx.h"
#include "Hornet.h"

void Hornet::init()
{
	Unit::init();
	IMAGEMANAGER->addFrameImage("hornetR", "Resources/Images/Unit/hornetR.bmp", 3700, 5270, 10, MAX_FRAME_Y, true, MAGENTA);
	_img = IMAGEMANAGER->addFrameImage("hornet", "Resources/Images/Unit/hornet.bmp", 3700, 5270, 10, MAX_FRAME_Y, true, MAGENTA);
	
	_frameWidth = _img->getFrameWidth();
	_frameHeight = _img->getFrameHeight() - 10;

	_pos.x = WINSIZE_X - _frameWidth - 100;
	_pos.y = FLOOR - _frameHeight;

	_time = _tickCount;
	_term = 700;

	_isSkill2 = _isSkill3 = _isSkill4 = false;
	_skillEffect3 = false;

	_hp = HORNET_HP;

	IMAGEMANAGER->addFrameImage("hornet_sphere_start", L"Resources/Images/Effects/hornet_sphere_start.png", 4, 1);
	IMAGEMANAGER->addFrameImage("hornet_sphere", L"Resources/Images/Effects/hornet_sphere.png", 9, 1);
	IMAGEMANAGER->addFrameImage("hornet_throw", L"Resources/Images/Effects/hornet_throw.png", 3, 1);
	IMAGEMANAGER->addFrameImage("hornet_throw_line", L"Resources/Images/Effects/hornet_throw_line.png", 6, 1);

	_weapon = new HornetWeapon;
}

void Hornet::update()
{
	Unit::update();
	move();

	if (_isIntro) {
		if (_isIntroAnim) {
			_isIntroAnim = false;
			intro();
		}
		return; 
	}

	if (_isSkill4) {
		_weapon->update();
		POINT pos = _weapon->getPos();
		_attackBox = { pos.x - 110 + (_isLeft ? 0 : 80), pos.y + 30, pos.x + 110 - (_isLeft ? 80 : 0), pos.y + 50 };
	}

	if (_isDead) {
		_attackBox = { 0,0,0,0 };
		if (_isDeadAnim) {
			_isDeadAnim = false;
			dead();
		}
		return;
	}

	if (_time + _term >= _tickCount) {
		return;
	}
	_time = _tickCount;

	if (!_isActive && !_isDead) {
		_isActive = true;
		findPlayer();
		for (; _prePattern == _pattern;) {
			_pattern = RND->getInt(6);
		}
		_prePattern = _pattern;
		switch (_pattern)
		{
		case 0:
			jump();
			break;
		case 1:
			activeSkill1();
			break;
		case 2:
			activeSkill2();
			break;
		case 3:
			activeSkill3();
			break;
		case 4:
			activeSkill4();
			break;
		default:
			_isActive = false;
			break;
		}
	}
}

void Hornet::render(HDC hdc)
{
	Unit::render(hdc);
	if (_isLeft) IMAGEMANAGER->frameRender("hornet", hdc, _pos.x, _pos.y, 6);
	else IMAGEMANAGER->frameRender("hornetR", hdc, _pos.x, _pos.y, 6);

	_effectManager->render(hdc);

	if (_isSkill4 && !_isDead) {
		_weapon->render(hdc);
	}
}

void Hornet::release()
{
	SAFE_DELETE(_weapon);
}

void Hornet::childHit()
{
}

void Hornet::intro()
{
	_img->setFrameY(INTRO1, 10, [this]() {
		_img->setFrameY(INTRO2, 4, [this]() {
			//_isActive = true;
			_isIntro = false;
			_img->setFrameY(IDLE, 6);
		});
	});
}

void Hornet::move()
{
	_boundBox = { _pos.x + 145, _pos.y + 90 +(_isSkill2 ? 60 : 0), _pos.x + 220, _pos.y + 290 };
	if (_isJump && !_isDead) {
		_pos.y -= 30 + _gravity;
		_gravity -= 1;
		if (_pos.y > FLOOR - _frameHeight) {
			_pos.y = FLOOR - _frameHeight;
			_isJump = false;
			_img->setFrameY(LAND, 3, [this]() {
				setIdleState();
				if (_isSkill3) _isSkill3 = false;
			});
		}
	}
	else {
		if (!_isSkill3) {
			_pos.y = FLOOR - _frameHeight;
		}
	}

	if (_pos.y > FLOOR - _frameHeight) {
		_pos.y = FLOOR - _frameHeight;
	}

	if (_pos.y < 0) {
		_pos.y = 0;
	}

	if (_pos.x < 100) {
		_pos.x = 100;
	}

	if (_pos.x > WINSIZE_X - _frameWidth) {
		_pos.x = WINSIZE_X - _frameWidth;
	}
}

void Hornet::dead()
{
	_pos.y = FLOOR - _frameHeight;
	_effectManager->addEffect("hornet_sphere_start", { _centerX - 420, _centerY - 50 }, { 0,0 }, { 0,0 }, !_isLeft, 10);
	_img->setFrameY(DEAD, 5, 1);
}

void Hornet::setIdleState()
{
	_img->setFrameY(IDLE, 5);
	_isActive = false;
}

void Hornet::findPlayer()
{
	if (_enemy->getCenterX() < _centerX) {
		_dir = -1;
		_isLeft = true;
		_img = IMAGEMANAGER->findImage("hornet");
	}
	else {
		_dir = 1;
		_isLeft = false;
		_img = IMAGEMANAGER->findImage("hornetR");
	}
}

void Hornet::jump()
{
	_img->setFrameY(JUMP1, 4, [this]() {
		_movingPoint.pos.x = 300;
		_movingPoint.tick.x = 5 * (RND->getInt(2) == 0 ? -1 : 1);
		_gravity = 0;
		_isJump = true;
		_img->setFrameY(JUMP2, 9, []() {});
	});
}

void Hornet::activeSkill1()
{
	_movingPoint.pos.x = 230;
	_movingPoint.tick.x = 5 * (_isLeft ? 1 : -1);
	_gravity = -15;
	_isJump = true;
	_img->setFrameY(EVADE, 6, [this]() {
		//setIdleState();
	});
}

void Hornet::activeSkill2()
{
	_isSkill2 = true;
	_animLoop = 0;
	_img->setFrameY(DASH1, 10, [this]() {
		_movingPoint.pos.x = 525;
		_movingPoint.tick.x = 15 * _dir;
		_isAttack = true;
		_isMoveAttackBox = true;
		_attackBox = RectMake(_centerX - (_isLeft ? 150 : 0), _pos.y + 250, 150, 30);
		_img->setFrameY(DASH2, 2, [this]() {
			if (++_animLoop > 2) {
				_isAttack = false;
				_isMoveAttackBox = false;
				_movingPoint.pos.x = 200;
				_movingPoint.tick.x = 10 * _dir;
				_img->setFrameY(DASH3, 6, [this]() {
					_isSkill2 = false;
					setIdleState();
				});
			}
		});
	});
}

void Hornet::activeSkill3()
{
	_isSkill3 = true;
	_movingPoint.pos.y = RND->getFromIntTo(200, 300);
	_movingPoint.tick.y = -10;
	_movingPoint.pos.x = RND->getFromIntTo(200, 250);
	_movingPoint.tick.x = 10 * _dir;
	_img->setFrameY(SPHERE1, 7, [this]() {
		_isAttack = true;
		_effectManager->addEffect("hornet_sphere", { _centerX - 200, _centerY -200}, { 0,0 }, { 0,0 }, !_isLeft, 5);
		_attackBox = RectMake(_centerX - 200, _centerY - 160, 400, 400);
		_img->setFrameY(SPHERE2, 9, [this]() {
			_isJump = true;
			_gravity = -25;
			_skillEffect3 = false;
			_isAttack = false;
		});
	}, 0, [this]() {
		if (!_skillEffect3) {
			_skillEffect3 = true;
		}
	}, 6);
}

void Hornet::activeSkill4()
{
	_weapon->init(_centerX, _centerY, _isLeft, _enemy);
	_img->setFrameY(THROW1, 10, [this]() {
		_effectManager->addEffect("hornet_throw", { _centerX -140, _centerY-50 }, { 0,0 }, { 0,0 }, !_isLeft, 5);
		_effectManager->addEffect("hornet_throw_line", { _centerX + (_isLeft ? - 550 : 50), _centerY + 20 }, { 0,0 }, { 0,0 }, !_isLeft, 8);
		_isSkill4 = true;
		_isAttack = true;
		_weapon->throwWeapon();
		_img->setFrameY(THROW2, 6, [this]() {
			_weapon->recorverWeapon();
			_img->setFrameY(THROW3, 6, [this]() {
				_isSkill4 = false;
				_isAttack = false;
				setIdleState(); 
			});
		});
	});
}
