#pragma once
#include "Unit.h"
#include "ThornBall.h"
#include "Hiveling.h"

#define HIVE_MAX		4

class HiveKnight : public Unit
{
private:
	enum HiveKnightMotion
	{
		IDLE,
		JUMP,
		SKILL1_1,
		SKILL1_2,
		SKILL2_1,
		SKILL2_2,
		SKILL2_3,
		SKILL3_1,
		SKILL3_2,
		SKILL4,
		DEAD,
		DEAD1,
		DEAD2,
		INTRO
	};

	bool _isSkill3, _isSkill4;
	ULONGLONG _sCool3, _sCool4;
	ThornBall* _ball[3];
	Hiveling* _hive[HIVE_MAX];

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void childHit();

	void intro();
	void move();
	void jump();
	void activeSkill1();
	void activeSkill2();
	void activeSkill3();
	void activeSkill4();
	void dead();

	void runSkill3();
	void runSkill4();

	void setIdleState();
	void findPlayer();

	bool isDead() { return _isDead; }

	HiveKnight() : _isSkill3(false), _isSkill4(false){}
	virtual ~HiveKnight() {}
};

