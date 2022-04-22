#include "Stdafx.h"
#include "AnimationManager.h"

void AnimationManager::insertAnimation(AnimState state, int currentX, int currentY, int maxFrame, int startFrame, bool isLoop)
{
	_animationList.push_back({state, currentX, currentY, maxFrame, startFrame, isLoop});
	Animation res = _animationList.back();
}

int AnimationManager::getCurrentY()
{
	return _animationList.back().currentFrameY;
}

Animation AnimationManager::getAnimation()
{
	Animation res = _animationList.back();
	if (!res.isLoop) {
		_animationList.pop_back();
	}
	return res;
}

void AnimationManager::deleteAnimation()
{
	_animationList.pop_back();
}

bool AnimationManager::isAnimation(int currentY)
{
	bool res = false;
	for (auto animation : _animationList) {
		if (currentY == animation.currentFrameY) {
			res = true;
		}
	}
	return res;
}

bool AnimationManager::isCurrentAnimation(int currentY)
{
	Animation res = _animationList.back();
	return currentY == res.currentFrameY;
}


