#pragma once
#include "GameNode.h"
#include "Player.h"
#include "HiveKnight.h"

class HiveScene : public GameNode
{
private:
	Player* _player;
	HiveKnight* _hiveKnight;

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

	HiveScene() {}
	~HiveScene() {}
};

