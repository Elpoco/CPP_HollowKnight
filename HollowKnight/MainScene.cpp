#include "Stdafx.h"
#include "MainScene.h"

HRESULT MainScene::init(void)
{
	IMAGEMANAGER->addImage("main", "Resources/Images/BackGround/main.bmp", WINSIZE_X + 100, WINSIZE_Y);

	_player = new Player;
	_player->init();
	_player->openMap(LEFT);
	_player->openMap(RIGHT);

	return S_OK;
}

HRESULT MainScene::init(Player * player)
{
	IMAGEMANAGER->addImage("main", "Resources/Images/BackGround/main.bmp", WINSIZE_X + 100, WINSIZE_Y);
	IMAGEMANAGER->addImage("arrow", L"Resources/Images/Object/RT_LT_arrow.png");

	_player = player;
	_player->openMap(LEFT);
	_player->openMap(RIGHT);

	_time = GetTickCount64();
	_arrowX = 0;
	_dir = 1;

	return S_OK;
}

void MainScene::release(void)
{
	SAFE_DELETE(_player);
}

void MainScene::update(void)
{
	_player->update();
	
	if (_time + 50 <= GetTickCount64()) {
		_time = GetTickCount64();
		_arrowX += _dir;
		if (_arrowX > 10 || _arrowX < 0) {
			_dir *= -1;
		}
	}
}

void MainScene::render(void)
{
	IMAGEMANAGER->render("main", getMemDC());
	IMAGEMANAGER->plusRender("arrow", getMemDC(), 50 - _arrowX, WINSIZE_Y - 200);
	IMAGEMANAGER->plusRender("arrow", getMemDC(), WINSIZE_X - 100 + _arrowX, WINSIZE_Y - 200, true);
	_player->render(getMemDC());
}
