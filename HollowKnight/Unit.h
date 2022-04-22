#pragma once
#include "Config.h"
#include "Image.h"
#include "AnimationManager.h"
#include "EffectManager.h"

#define ATK_BOX				10

#define PLAYER_HIT_TERM		1000
#define HIT_TERM			500
#define PARRYING_TERM		1000

#define DEFAULT_HP			10
#define PLAYER_HP			20
#define HIVEKNIGHT_HP		20
#define HORNET_HP			20

class Unit
{
protected:
	enum UPNDONW{
		FRONT,
		UP,
		DOWN
	};

	struct MoveData
	{
		POINT pos;
		POINT tick;

		MoveData() {
			pos = { 0,0 };
			tick = { 0,0 };
		}
	};

	Image* _img;
	MOTION _motion;
	STATE _state;
	bool _isLeft;
	POINT _pos;
	int _gravity;
	bool _isJump;
	int _pattern;
	int _prePattern;

	bool _isPlayer;
	bool _isActive;
	bool _isDead;
	bool _isDeadAnim;
	bool _isEnd;
	bool _isIntro;
	bool _isIntroAnim;
	bool _isAttack;
	bool _isHit;
	bool _isAttacking;
	bool _isParrying;
	bool _parrying;

	int _animLoop;
	
	Unit* _enemy;
	RECT _boundBox;
	int _centerX, _centerY;
	bool _playerIsLeft;
	int _dir;
	UPNDONW _up_down;
	RECT _attackBox;
	RECT _attackBoxList[ATK_BOX];
	bool _isMoveAttackBox;

	MoveData _movingPoint;

	ULONGLONG _tickCount;
	ULONGLONG _time, _term;
	ULONGLONG _hitTime, _hitTerm;
	ULONGLONG _parryingTime, _parryingTerm;
	BYTE _alpha;

	int _frameWidth, _frameHeight;

	RECT _hitRc;

	int _hp;
	AnimationManager* _animationManager;
	EffectManager* _effectManager;

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC hdc);

	void setEnemy(Unit* enemy) { _enemy = enemy; }
	void setBoundBox(RECT box) { _boundBox = box; }
	RECT getBoundBox() { return _boundBox; }
	int getCenterX() { return _centerX; }
	int getCenterY() { return _centerY; }
	RECT getAttackBox() { return _attackBox; }
	RECT getAttackBox(int i) { return _attackBoxList[i]; }
	POINT getPos() { return _pos; }
	void hit();
	virtual void childHit() {};
	virtual void attackHit() {};

	Unit() :
		_state(NORMAL), _motion(NONE), _isLeft(true), _pos({ WINSIZE_X / 2, FLOOR }),
		_gravity(0), _isActive(false), _isDead(false), _isDeadAnim(true), _isEnd(false), _animLoop(0),
		_centerX(0), _dir(-1), _isIntro(true), _isIntroAnim(true), _pattern(-1), _prePattern(-1),
		_isAttack(false), _isMoveAttackBox(false), _isPlayer(false), _hitTerm(HIT_TERM), _alpha(0),
		_isHit(false), _isAttacking(false), _boundBox({0,0,0,0}), _up_down(FRONT), _isJump(false),
		_parrying(false), _hp(DEFAULT_HP), _parryingTerm(PARRYING_TERM)
	{}
	virtual ~Unit();
};

