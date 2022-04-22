#pragma once
#include "Unit.h"

class ThornBall : public Unit
{
private:
	struct Thorn
	{
		float angle;
		POINT pos;
	};

	int _idx;
	bool _isReady;
	bool _isShoot;
	POINT _movePos;
	Thorn _thorn[8];
	Image* _img;
	int _imgW, _imgH;

	DWORD _time, _tick, _tick2;
	DWORD _time2, _tick3;

	int _dir;
	bool _isEndPattern;
	func _callback;

public:
	ThornBall();
	~ThornBall();

	void init(int x, int y, int idx, Unit* enemy);
	void update();
	void render(HDC hdc);
};

