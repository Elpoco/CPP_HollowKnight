#include "Stdafx.h"
#include "HiveScene.h"

HRESULT HiveScene::init(void)
{
	IMAGEMANAGER->addImage("hive", "Resources/Images/BackGround/hive.bmp", WINSIZE_X, WINSIZE_Y+40);
	_player = new Player;
	_player->init();
	_hiveKnight = new HiveKnight;
	_hiveKnight->init();

	_player->setEnemy(_hiveKnight);
	_hiveKnight->setEnemy(_player);
	
	return S_OK;
}

HRESULT HiveScene::init(Player * player)
{
	IMAGEMANAGER->addImage("hive", "Resources/Images/BackGround/hive.bmp", WINSIZE_X, WINSIZE_Y + 40);
	_player = player;
	_hiveKnight = new HiveKnight;
	_hiveKnight->init();

	_player->setEnemy(_hiveKnight);
	_hiveKnight->setEnemy(_player);

	_time = GetTickCount64();
	_arrowX = 0;
	_dir = 1;

	return S_OK;
}

void HiveScene::release(void)
{	
	SAFE_DELETE(_player);
	SAFE_DELETE(_hiveKnight);
}

void HiveScene::update(void)
{
	_player->update();
	_hiveKnight->update();

	if (_hiveKnight->isDead()) {
		_player->openMap(RIGHT);
		if (_time + 50 <= GetTickCount64()) {
			_time = GetTickCount64();
			_arrowX += _dir;
			if (_arrowX > 10 || _arrowX < 0) {
				_dir *= -1;
			}
		}
	}
}

void HiveScene::render(void)
{
	IMAGEMANAGER->render("hive", getMemDC());
	_hiveKnight->render(getMemDC());
	if (_hiveKnight->isDead()) {
		IMAGEMANAGER->plusRender("arrow", getMemDC(), WINSIZE_X - 100 + _arrowX, WINSIZE_Y - 200, true);
	}
	_player->render(getMemDC());
}

void HiveScene::setScene()
{
	_player->setEnemy(_hiveKnight);
	_hiveKnight->setEnemy(_player);
}
