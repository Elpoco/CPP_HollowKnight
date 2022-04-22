#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Hornet.h"

class GreenpathScene : public GameNode
{
private:
	Player* _player;
	Hornet* _hornet;

	ULONGLONG _time;
	int _arrowX;
	int _dir;
	
public:
	HRESULT init(void);
	HRESULT init(Player* player);
	void release(void);
	void update(void);
	void render(void);

	void setScene();

	GreenpathScene() {}
	~GreenpathScene() {}

};

