#pragma once
#define FLOOR	WINSIZE_Y - 100

enum DIRECTION
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	CENTER
};

enum STATE
{
	NORMAL,
	MOVING,
	ATTACK
};

enum MOTION
{
	NONE,
	JUMPING,
//	ATTACK,
	SKILL1,
	SKILL2,
	SKILL3
};

enum AnimState
{
	PLAY,
	POUSE,
	STOP
};

enum Scene
{
	MAIN,
	HIVE,
	GREENPATH
};

struct Animation
{
	AnimState state;
	int currentFrameX;
	int currentFrameY;
	int maxFrame;
	int startFrame;
	bool isLoop;

	Animation(AnimState state, int currentFrameX, int currentFrameY,
		int maxFrame, int startFrame, bool isLoop)
	{
		this->state = state;
		this->currentFrameX = currentFrameX;
		this->currentFrameY = currentFrameY;
		this->maxFrame = maxFrame;
		this->startFrame = startFrame;
		this->isLoop = isLoop;
	}
};