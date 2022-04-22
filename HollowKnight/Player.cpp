#include "Stdafx.h"
#include "Player.h"

void Player::init()
{
	Unit::init();
	_callback = [this]() {
		Animation anim = _animationManager->getAnimation();
		_img->setFrame(anim.currentFrameX, anim.currentFrameY, anim.maxFrame, anim.startFrame);
	};

	IMAGEMANAGER->addFrameImage("playerR", "Resources/Images/Unit/playerR.bmp", 1530, 1452, 9, 11, true, MAGENTA);
	_img = IMAGEMANAGER->addFrameImage("player", "Resources/Images/Unit/player.bmp", 1530, 1452, 9, 11, true, MAGENTA);
	_img->setCallback(_callback);

	_pos.y = FLOOR - _img->getFrameHeight();

	_frameWidth = _img->getFrameWidth();
	_frameHeight = _img->getFrameHeight();

	_state = NORMAL;
	_isPlayer = true;

	_attackTime = _time = _tickCount;
	_term = 300;
	_attackTick = ATTACK_TERM;

	_animationManager = new AnimationManager;
	_animationManager->insertAnimation(AnimState::PLAY, 0, 0, 9, 0, true);

	_hp = PLAYER_HP;
	_hitTerm = PLAYER_HIT_TERM;

	// ÀÌÆåÆ®
	IMAGEMANAGER->addFrameImage("player_attack1", L"Resources/Images/Effects/attack.png", 2, 1);
	IMAGEMANAGER->addFrameImage("player_attack_down", L"Resources/Images/Effects/attack_down.png", 2, 1);
	IMAGEMANAGER->addFrameImage("player_attack_up", L"Resources/Images/Effects/attack_up.png", 2, 1);
	IMAGEMANAGER->addFrameImage("attack_hit", L"Resources/Images/Effects/attack_hit.png", 4, 1);
	IMAGEMANAGER->addFrameImage("player_hit", L"Resources/Images/Effects/player_hit.png", 3, 1);

	_isOpenL = _isOpenR = false;

	// Ã¼·Â UI
	IMAGEMANAGER->addFrameImage("hp", L"Resources/Images/Object/hp_ui.png", 5, 1);
}

void Player::update()
{
	Unit::update();
	move();

	if (_isHit && _time + _term <= _tickCount) {
		_alpha = _alpha == 0 ? 100 : 0;
		_time = _tickCount;
	}
	if (!_isHit) {
		_alpha = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('Z') && !_isJump) {
		_gravity = 0.0f;
		_isJump = true;
		_img->setFrameY(JUMP, JUMP_X);
	}

	if (_isAttack && _attackTime + 150 <= _tickCount) {
		_isAttack = false;
	}

	if (KEYMANAGER->isOnceKeyDown('X') && _attackTime + _attackTick <= _tickCount) {
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _isJump) {
			_img->setFrameY(ATTACK_DOWN, ATTACK_DOWN_X);
			_effectManager->addEffect("player_attack_down",
				{ _centerX - 90, _centerY - 20 }, { 0,0 }, { 0,0 }, _isLeft, 5);
			_attackBox = RectMake(_centerX - 90, _centerY + 40, 160, 160);
			_up_down = DOWN;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			_img->setFrameY(ATTACK_UP, ATTACK_DOWN_X);
			_effectManager->addEffect("player_attack_up",
				{ _centerX - 80, _centerY - 200 }, { 0,0 }, { 0,0 }, _isLeft, 5);
			_attackBox = RectMake(_centerX - 80, _centerY - 200, 160, 160);
			_up_down = UP;
		}
		else {
			_img->setFrameY(ATTACK1, ATTACK1_X);
			_effectManager->addEffect("player_attack1",
				{ _centerX - (_isLeft ? 240 : -40), _pos.y + 20 },
				{ 0, 0 }, { 0,0 }, _isLeft, 5);
			_attackBox = RectMake(_centerX - (_isLeft ? 240 : -40), _pos.y + 20, 200, 110);
		}
		_attackTime = _tickCount;
		_isAttack = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN)) {
		_up_down = FRONT;
	}

	if (KEYMANAGER->isOnceKeyDown('C')) {

	}

}

void Player::render(HDC hdc)
{
	Unit::render(hdc);
	if (_isLeft) {
		IMAGEMANAGER->frameRender("player", hdc, _pos.x, _pos.y, 5, false, _alpha);
	}
	else {
		IMAGEMANAGER->frameRender("playerR", hdc, _pos.x, _pos.y, 5, false, _alpha);
	}
	_effectManager->render(hdc);
	for (int i = 0; i < PLAYER_HP / 4; i++) {
		if (_hp < 4 * (i)) {
			IMAGEMANAGER->plusFrameRender("hp", hdc, 100 + i * 50, 100, 0, 0);
		}
		else {
			IMAGEMANAGER->plusFrameRender("hp", hdc, 100 + i * 50, 100, _hp > 4 * (i + 1) ? 4 : _hp - i * 4, 0);
		}
	}
}

void Player::move()
{
	_boundBox = { _pos.x + 55, _pos.y, _pos.x + 115, _pos.y + 132 };
	_centerX = _boundBox.right - (_boundBox.right - _boundBox.left) / 2;

	if (_isJump) {
		_pos.y -= 25 + _gravity;
		_gravity -= 1;
		if (_pos.y > FLOOR - _frameHeight) {
			_pos.y = FLOOR - _frameHeight;
			_isJump = false;
			if (_animationManager->isCurrentAnimation(AIR)) {
				_animationManager->deleteAnimation();
			}
			_img->setFrameY(LANDDING, LANDDING_X);
		}
	}
	else {
		_pos.y = FLOOR - _frameHeight;
		if (_animationManager->isCurrentAnimation(AIR)) {
			_animationManager->deleteAnimation();
		}
	}

	if (_pos.y > FLOOR - _frameHeight) {
		_pos.y = FLOOR - _frameHeight;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		if (!_isLeft) {
			_isLeft = true;
			int currentX = _img->getFrameX();
			int currentY = _img->getFrameY();
			_img = IMAGEMANAGER->findImage("player");
			_img->setFrameX(currentX);
			_img->setFrameY(currentY);
		}
		if (!_animationManager->isAnimation(MOVE)) {
			_animationManager->insertAnimation(AnimState::PLAY, 0, MOVE, MOVE_X, 3, true);
			_img->setFrameY(MOVE, MOVE_X);
		}
		_img->setCallback(_callback);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		if (!_isLeft) {
			_isLeft = true;
			changeImg(_isLeft);
		}
		_pos.x -= 5;
		if (!_animationManager->isAnimation(MOVE)) {
			_animationManager->insertAnimation(AnimState::PLAY, 0, MOVE, MOVE_X, 3, true);
			_img->setFrameY(MOVE, MOVE_X);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT)) {
		if (_animationManager->isCurrentAnimation(MOVE)) {
			_animationManager->deleteAnimation();
			_img->setFrameY(STOP, STOP_X);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		if (_isLeft) {
			_isLeft = false;
			int currentX = _img->getFrameX();
			int currentY = _img->getFrameY();
			_img = IMAGEMANAGER->findImage("playerR");
			_img->setFrameX(currentX);
			_img->setFrameY(currentY);
		}
		if (!_animationManager->isAnimation(MOVE)) {
			_animationManager->insertAnimation(AnimState::PLAY, 0, MOVE, MOVE_X, 3, true);
			_img->setFrameY(MOVE, MOVE_X);
		}
		_img->setCallback(_callback);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		if (_isLeft) {
			_isLeft = false;
			changeImg(_isLeft);
		}
		_pos.x += 5;
		if (!_animationManager->isAnimation(MOVE)) {
			_animationManager->insertAnimation(AnimState::PLAY, 0, MOVE, MOVE_X, 3, true);
			_img->setFrameY(MOVE, MOVE_X);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT)) {
		if (_animationManager->isCurrentAnimation(MOVE)) {
			_animationManager->deleteAnimation();
			_img->setFrameY(STOP, STOP_X);
		}
	}

	if (_isOpenL) {
		if (_pos.x < -60) _pos.x = -60;
	}
	else {
		if (_pos.x < 100) _pos.x = 100;
	}

	if (_isOpenR) {
		if (_pos.x > WINSIZE_X - 110) _pos.x = WINSIZE_X - 110;
	}
	else {
		if (_pos.x > WINSIZE_X - 260) _pos.x = WINSIZE_X - 260;
	}
}

void Player::changeImg(bool isLeft)
{
	int currentX = _img->getFrameX();
	int currentY = _img->getFrameY();
	if (isLeft) {
		_img = IMAGEMANAGER->findImage("player");
	}
	else {
		_img = IMAGEMANAGER->findImage("playerR");
	}
	_img->setFrameX(currentX);
	_img->setFrameY(currentY);
}

void Player::childHit()
{
	_effectManager->addEffect("player_hit", { _centerX - 240, _centerY - 100 }, { 0,0 }, { 0,0 }, _isLeft, 5);
}

void Player::attackHit()
{
	if (!_effectManager->isEffect("attack_hit")) {
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/attack.wav");
		_effectManager->addEffect("attack_hit",
			{ _hitRc.left + (_hitRc.right - _hitRc.left) / 2 - 100, _hitRc.top + (_hitRc.bottom - _hitRc.top) / 2 - 100 },
			{ 0,0 }, { 0,0 }, _isLeft, 5, 0, 0, true);
	}
}

void Player::openMap(DIRECTION dir)
{
	if (dir == LEFT) {
		_isOpenL = true;
	}
	else if (dir == RIGHT) {
		_isOpenR = true;
	}
}

void Player::closeMap()
{
	_isOpenL = false;
	_isOpenR = false;
}

Player::~Player()
{

}
