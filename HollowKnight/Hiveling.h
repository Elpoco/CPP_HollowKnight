#pragma once
#include "Unit.h"
class Hiveling : public Unit
{
private:
	bool _isUp;
	int _idx;

public:
	virtual void init() {}
	virtual void init(int x, int y, int idx, Unit* enemy);
	virtual void update();
	virtual void render(HDC hdc);

	Hiveling() {}
	virtual ~Hiveling() {}
};

