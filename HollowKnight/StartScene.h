#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScene() {}
	~StartScene() {}
};

