#include "Stdafx.h"
#include "HiveKnight.h"

void HiveKnight::init()
{
	Unit::init();
	IMAGEMANAGER->addFrameImage("hiveKnight", "Resources/Images/Unit/hiveKnight.bmp", 7000, 7560, 10, 14, true, MAGENTA);
	_img = IMAGEMANAGER->addFrameImage("hiveKnightR", "Resources/Images/Unit/hiveKnightR.bmp", 7000, 7560, 10, 14, true, MAGENTA);
	_img->setMaxFrameX(5);
	_frameWidth = _img->getFrameWidth();
	_frameHeight = _img->getFrameHeight();

	_pos.x = 100;
	_pos.y = FLOOR - _frameHeight;

	_sCool4 = _sCool3 = _time = _tickCount;
	_term = 700;

	_hp = HIVEKNIGHT_HP;

	_isLeft = false;
}

void HiveKnight::update()
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

	if (_isSkill3) {
		for (int i = 0; i < 3; i++)
		{
			_ball[i]->update();
		}
	}

	if (_isSkill4) {
		for (int i = 0; i < HIVE_MAX; i++) {
			_hive[i]->update();
		}
	}

	if (_isDead) {
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
			if (_sCool3 + 6000 <= _tickCount) {
				_sCool3 = _tickCount;
				activeSkill3();
			}
			else _isActive = false;
			break;
		case 4:
			if (_sCool4 + 10000 <= _tickCount) {
				_sCool4 = _tickCount;
				activeSkill4();
			}
			else _isActive = false;
			break;
		default:
			_isActive = false;
			break;
		}
	}
}

void HiveKnight::render(HDC hdc)
{
	Unit::render(hdc);
	if (!_isEnd) {
	//IMAGEMANAGER->plusFrameRender("hiveKnight", hdc, _pos.x, _pos.y, 5, _isLeft);
		if (_isLeft) IMAGEMANAGER->frameRender("hiveKnight", hdc, _pos.x, _pos.y, 5);
		else IMAGEMANAGER->frameRender("hiveKnightR", hdc, _pos.x, _pos.y, 5);
	}
	else {
		if (_isLeft) IMAGEMANAGER->render("hiveKnight", hdc, _pos.x, _pos.y, 2100, 6480, 700, 540);
		else IMAGEMANAGER->render("hiveKnightR", hdc, _pos.x, _pos.y, 2100, 6480, 700, 540);
	}
	_effectManager->render(hdc);


	if (_isSkill3) {
		for (int i = 0; i < 3; i++) {
			_ball[i]->render(hdc);
		}
	}

	if (_isSkill4) {
		for (int i = 0; i < HIVE_MAX; i++) {
			_hive[i]->render(hdc);
		}
	}
}

void HiveKnight::childHit()
{
	//_effectManager->addEffect("hit_orange", { _centerX, _centerY }, { 0,0 }, { 500,500 }, false, 0, 150);
}

void HiveKnight::intro()
{
	_animLoop = 0;
	_img->setFrameY(INTRO, 10, [this]() {
		if (++_animLoop > 1) {
			_isIntro = false;
		}
	});
}

void HiveKnight::move()
{
	_boundBox = { _pos.x + 245, _pos.y + 265, _pos.x + 450, _pos.y + 540 };

	if (_isJump && !_isDead) {
		_pos.y -= 30 + _gravity;
		_gravity -= 1;
		if (_pos.y > FLOOR - _frameHeight) {
			_pos.y = FLOOR - _frameHeight;
			_isJump = false;
			setIdleState();
		}
	}
	else {
		_pos.y = FLOOR - _frameHeight;
	}

	if (_pos.y > FLOOR - _frameHeight) {
		_pos.y = FLOOR - _frameHeight;
	}

	if (_pos.x < 0 - 100) {
		_pos.x = -100;
	}

	if (_pos.x + _img->getFrameWidth() > WINSIZE_X + 100) {
		_pos.x = WINSIZE_X - _frameWidth + 100;
	}
}

void HiveKnight::jump()
{
	_movingPoint.pos.x = 220;
	_movingPoint.tick.x = 4 * (RND->getInt(2) == 0 ? -1 : 1);
	_img->setFrameY(JUMP, 3, NULL);
	_isJump = true;
	_gravity = 0;
}

void HiveKnight::activeSkill1()
{
	_img->setFrameY(SKILL1_1, 5, [this]() {
		if (_isLeft) {
			_pos.x = _enemy->getBoundBox().right - _frameWidth;
		}
		else {
			_pos.x = _enemy->getBoundBox().left;
		}
		_boundBox = { _pos.x + 245, _pos.y + 265, _pos.x + 450, _pos.y + 540 };
		_centerX = _boundBox.right - (_boundBox.right - _boundBox.left) / 2;
		findPlayer();
		_img->setFrameY(SKILL1_2, 9,
			[this]() {
				setIdleState();
			}, 0, 
			[this]() {
				_isAttack = true;
				_attackBox = RectMake(_centerX - 319, _pos.y + 247, 637, 263);
			}, 6,
			[this]() {
				_isAttack = false;
			}, 7);
	});
}

void HiveKnight::activeSkill2()
{
	_animLoop = 0;
	_img->setFrameY(SKILL2_1, 10, [this]() {
		_movingPoint.pos.x = 525;
		_movingPoint.tick.x = 20 * _dir;
		_isAttack = true;
		_isMoveAttackBox = true;
		_attackBox = RectMake(_centerX - (_isLeft ? 350 : 0), _pos.y + 354, 350, 134);
		_img->setFrameY(SKILL2_2, 2, [this]() {
			if (++_animLoop > 2) {
				_isAttack = false;
				_isMoveAttackBox = false;
				_movingPoint.pos.x = 250;
				_movingPoint.tick.x = 20 * _dir;
				_img->setFrameY(SKILL2_3, 5, [this]() {
					setIdleState();
				});
			}
		});
	});
}

void HiveKnight::activeSkill3()
{
	_img->setFrameY(SKILL3_1, 8, [this]() {
		runSkill3();
		_img->setFrameY(SKILL3_2, 5, [this]() {
			setIdleState();
		});
	});
}

void HiveKnight::activeSkill4()
{
	_animLoop = 0;
	_img->setFrameY(SKILL4, 2, [this]() {
		if (++_animLoop > 1) {
			_img->setFrameY(SKILL4, 3, [this]() {
				_animLoop = 0;
				runSkill4();
				_img->setFrameY(SKILL4, 6, [this]() {
					if (++_animLoop > 5) {
						setIdleState();
					}
				}, 4);
			});
		}
	});
}

void HiveKnight::dead()
{
	_animLoop = 0;
	_img->setFrameY(DEAD, 10, [this]() {
		if (++_animLoop > 2) {
			_pos.x = WINSIZE_X / 2 - 300;
			_pos.y = FLOOR - _frameHeight;
			_img->setFrameY(DEAD1, 10, [this]() {
				_img->setFrameY(DEAD2, 4, [this]() {
					_isEnd = true;
				});
			});
		}
	});
}

void HiveKnight::runSkill3()
{
	_isSkill3 = true;
	for (int i = 0; i < 3; i++) {
		int x = RND->getFromIntTo(300, 500);
		int y = RND->getFromIntTo(200, 400);
		if(_ball[i] == nullptr) _ball[i] = new ThornBall;
		_ball[i]->init(x + 400 * i, y, i, _enemy);
	}
}

void HiveKnight::runSkill4()
{
	_isSkill4 = true;
	for (int i = 0; i < HIVE_MAX; i++) {
		if (_hive[i] == nullptr) _hive[i] = new Hiveling;
		_hive[i]->init(_centerX, _centerY + i * 70, i, _enemy);
	}
}

void HiveKnight::setIdleState()
{
	_isActive = false;
	_img->setFrameY(IDLE, 5);
}

void HiveKnight::findPlayer()
{
	if (_enemy->getCenterX() < _centerX) {
		_dir = -1;
		_isLeft = true;
		_img = IMAGEMANAGER->findImage("hiveKnight");
	}
	else {
		_dir = 1;
		_isLeft = false;
		_img = IMAGEMANAGER->findImage("hiveKnightR");
	}
}
