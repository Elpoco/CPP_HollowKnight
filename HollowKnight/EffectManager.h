#pragma once
#include "Image.h"

class EffectManager
{
private:
	struct EffectInfo
	{
		string name;
		POINT pos;
		POINT movePos;
		POINT size;
		int tick;
		int time;
		int startTime;
		float angle;
		bool isLeft;

		Image* image;

		EffectInfo() {
			movePos = { 0,0 };
			angle = 0;
		}

		EffectInfo(string name, POINT pos, POINT movePos, POINT size, bool isLeft, int tick, int time, float algle) {
			this->name = name;
			this->pos = pos;
			this->movePos = movePos;
			this->size = size;
			this->isLeft = isLeft;
			this->time = time;
			this->tick = tick;
			this->angle = angle;
		}
	};

	vector<EffectInfo> _EffectList;
	vector<EffectInfo>::iterator _iter;


public:
	HRESULT init(void);
	void release(void);
	void render(HDC hdc);

	void addEffect(string strKey, POINT pos, POINT movePos, POINT size, bool isLeft, int tick, int time = 0, float angle = 0.f, bool isCenter = false);
	bool isEffect(string strKey);

	EffectManager() {}
	~EffectManager() {}
};

