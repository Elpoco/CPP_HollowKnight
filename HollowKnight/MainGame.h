#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "MainScene.h"
#include "HiveScene.h"
#include "GreenpathScene.h"
#include "Player.h"

class MainGame : public GameNode
{
private:
	StartScene* _start;
	MainScene* _main;
	HiveScene* _hive;
	GreenpathScene* _green;

	GameNode* _currentScene;

	bool _isStart;

	Player* _player;
	RECT _rcLeftScene;
	RECT _rcRightScene;
	RECT _rc;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeScene(string str);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}
};
