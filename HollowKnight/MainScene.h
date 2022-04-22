#pragma once
#include "GameNode.h"
#include "Player.h"

class MainScene : public GameNode
{
private:
	Player* _player;

	ULONGLONG _time;
	int _arrowX;
	int _dir;

public:
	HRESULT init(void);
	HRESULT init(Player* player);
	void release(void);
	void update(void);
	void render(void);

	MainScene() {}
	~MainScene() {}
};

