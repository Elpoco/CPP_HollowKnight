#include "Stdafx.h"
#include "GreenpathScene.h"

HRESULT GreenpathScene::init(void)
{
	IMAGEMANAGER->addImage("greenpath", "Resources/Images/BackGround/greenpath.bmp", WINSIZE_X, WINSIZE_Y - 10);
	_player = new Player;
	_player->init();
	_hornet = new Hornet;
	_hornet->init();

	_player->setEnemy(_hornet);
	_hornet->setEnemy(_player);

	return S_OK;
}

HRESULT GreenpathScene::init(Player * player)
{
	IMAGEMANAGER->addImage("greenpath", "Resources/Images/BackGround/greenpath.bmp", WINSIZE_X, WINSIZE_Y - 10);
	_player = player;
	_hornet = new Hornet;
	_hornet->init();

	_player->setEnemy(_hornet);
	_hornet->setEnemy(_player);

	_time = GetTickCount64();
	_arrowX = 0;
	_dir = 1;

	return S_OK;
}

void GreenpathScene::release(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_hornet);
}

void GreenpathScene::update(void)
{
	_player->update();
	_hornet->update();

	if (_hornet->isDead()) {
		_player->openMap(LEFT);
		if (_time + 50 <= GetTickCount64()) {
			_time = GetTickCount64();
			_arrowX += _dir;
			if (_arrowX > 10 || _arrowX < 0) {
				_dir *= -1;
			}
		}
	}
}

void GreenpathScene::render(void)
{
	IMAGEMANAGER->render("greenpath", getMemDC());
	_hornet->render(getMemDC());
	if (_hornet->isDead()) {
		IMAGEMANAGER->plusRender("arrow", getMemDC(), 50 - _arrowX, WINSIZE_Y - 200);
	}
	_player->render(getMemDC());
}

void GreenpathScene::setScene()
{
	_player->setEnemy(_hornet);
	_hornet->setEnemy(_player);
}
