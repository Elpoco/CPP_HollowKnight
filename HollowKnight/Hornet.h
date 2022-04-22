#pragma once
#include "Unit.h"
#include "HornetWeapon.h"

class Hornet : public Unit
{
private:
	enum HornetMotion
	{
		INTRO1,
		INTRO2,
		IDLE,
		MOVE,
		JUMP1,
		JUMP2,
		LAND,
		EVADE,
		DASH1,
		DASH2,
		DASH3,
		SPHERE1,
		SPHERE2,
		THROW1,
		THROW2,
		THROW3,
		DEAD,
		MAX_FRAME_Y
	};

	bool _isSkill2, _isSkill3, _isSkill4;
	bool _skillEffect3;

	HornetWeapon* _weapon;

public:
	virtual void init();
	virtual void update();
	virtual void render(HDC hdc);
	void release();

	virtual void childHit();

	void intro();
	void move();
	void dead();

	void setIdleState();
	void findPlayer();

	void jump();
	void activeSkill1();
	void activeSkill2();
	void activeSkill3();
	void activeSkill4();

	bool isDead() { return _isDead; }

	Hornet(){}
	~Hornet(){}
};

