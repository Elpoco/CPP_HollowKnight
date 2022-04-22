#pragma once
#include "Config.h"

class AnimationManager
{
private:
	vector<Animation> _animationList;
	vector<Animation>::iterator _iter;

public:
	AnimationManager() {}
	~AnimationManager() {}

	void insertAnimation(AnimState state, int currentX, int currentY, int maxFrame, int startFrame = 0, bool isLoop = false);
	int getCurrentY();
	Animation getAnimation();
	void deleteAnimation();
	bool isAnimation(int currentY);
	bool isCurrentAnimation(int currentY);

};

