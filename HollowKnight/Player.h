#pragma once
#include "Unit.h"

#define ATTACK_TERM		400

class Player : public Unit
{
private:

	enum PLAYER_SHEET
	{
		IDLE,
		TURN,
		MOVE,
		STOP,
		JUMP,
		AIR,
		LANDDING,
		ATTACK1,
		ATTACK2,
		ATTACK_UP,
		ATTACK_DOWN
	};

	enum PLAYER_SHEET_MAX_FRAME_X
	{
		IDLE_X = 9,
		TURN_X = 3,
		MOVE_X = 8,
		STOP_X = 5,
		JUMP_X = 9,
		AIR_X = 3,
		LANDDING_X = 3,
		ATTACK1_X = 5,
		ATTACK2_X = 5,
		ATTACK_UP_X = 5,
		ATTACK_DOWN_X = 5
	};

	func _callback;
	ULONGLONG _attackTime, _attackTick;
	bool _isOpenL, _isOpenR;
	Scene _crrentScene;

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void changeImg(bool isLeft);
	virtual void childHit();
	virtual void attackHit();

	void setHit(bool* hit) { hit = &_isHit; }

	void openMap(DIRECTION dir);
	void closeMap();

	void setScene(Scene scene, DIRECTION dir) {
		_crrentScene = scene;
		if (dir == CENTER) {
			_pos.x = WINSIZE_X / 2;
		}
		else if (dir == LEFT) {
			_pos.x = 130;
		}
		else {
			_pos.x = WINSIZE_X - _frameWidth  - 130;
		}
	}
	Scene getScene() { return _crrentScene; }

	void recovery() { _hp = PLAYER_HP; }

	Player() {}
	virtual ~Player();
};

