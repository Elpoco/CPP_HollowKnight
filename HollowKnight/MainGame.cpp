#include "Stdafx.h"
#include "MainGame.h"

/*
Hollow Knight
Enter: ���ӽ���, F1: �����, Z: ����, X: ����, ����Ű�� �̵�
���ӿ� �����ϴ� �������� ȣ�� �̶�� ������ �����߽��ϴ�.

gdi+�� ����Ʈ�� ���� ������Ʈ�� �̹��� ȸ���� ����߽��ϴ�.

����� Ű �Է��� �ִϸ��̼� �������ִ� ��ü�� �����
���ͷ� ������ �Ͽ� �ִϸ��̼� �������� ���������� callback�� �޾�
���� �ִϸ��̼����� �Ѿ�� ������� ������ �մϴ�.

���� ������ �������� ���� �˴ϴ�.
������ ��ȯ�ϴ� ���ֵ� ������ �����ϰ�,
������ ���⵵ ���� ĥ�� �ֵ��� ���� �߽��ϴ�.
������ �����Ҷ� �°����� �ϸ� �и��� �ϵ��� ��������ϴ�. (Ÿ�̹� �߿�!!)

�����濡 ���� �ٽ� ���ü� ���� ������
������ �ٽ� ������ �� �ֽ��ϴ�.
���� ȭ������ ���� ü���� �ٽ� ȸ�� �˴ϴ�.

�� �ܿ��� �ð� ����...�Ф�
*/

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	_player = new Player;
	_player->init();

	_start = new StartScene;
	_start->init();

	_main = new MainScene;
	_main->init(_player);

	_hive = new HiveScene;
	_hive->init(_player);

	_green = new GreenpathScene;
	_green->init(_player);

	_currentScene = _start;
	assert(_currentScene != nullptr);

	_isStart = false;

	_rcLeftScene = { 0, WINSIZE_Y - 160, 60, WINSIZE_Y -100};
	_rcRightScene = { WINSIZE_X - 60, WINSIZE_Y - 160, WINSIZE_X, WINSIZE_Y -100};


	TEMPSOUNDMANAGER->addMp3FileWithKey("BGM_main", "Resources/Sounds/main_bgm.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("BGM_hive", "Resources/Sounds/Hive Knight_bgm.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("BGM_green", "Resources/Sounds/hornet_bgm.mp3");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_start);
	SAFE_DELETE(_main);
	SAFE_DELETE(_hive);
	SAFE_DELETE(_green);
}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && !_isStart) {
		_isStart = true;
		_currentScene = _main;
		_player->setScene(MAIN, CENTER);
		TEMPSOUNDMANAGER->playSoundWithKey("BGM_main");
	}

	if (IntersectRect(&_rc, &_player->getBoundBox(), &_rcLeftScene)) {
		if (_player->getScene() == MAIN) {
			_currentScene = _hive;
			_currentScene->setScene();
			_player->setScene(HIVE, RIGHT);
			_player->closeMap();
			TEMPSOUNDMANAGER->stopMp3WithKey("BGM_main");
			TEMPSOUNDMANAGER->playSoundWithKey("BGM_hive");
		}
		else {
			_currentScene = _main;
			_player->setScene(MAIN, RIGHT);
			_player->openMap(RIGHT);
			_player->openMap(LEFT);
			_player->recovery();
			TEMPSOUNDMANAGER->stopMp3WithKey("BGM_green");
			TEMPSOUNDMANAGER->playSoundWithKey("BGM_main");
		}
	}

	if (IntersectRect(&_rc, &_player->getBoundBox(), &_rcRightScene)) {
		if (_player->getScene() == MAIN) {
			_currentScene = _green;
			_currentScene->setScene();
			_player->setScene(GREENPATH, LEFT);
			_player->closeMap();
			TEMPSOUNDMANAGER->stopMp3WithKey("BGM_main");
			TEMPSOUNDMANAGER->playSoundWithKey("BGM_green");
		}
		else {
			_currentScene = _main;
			_player->setScene(MAIN, LEFT);
			_player->openMap(RIGHT);
			_player->openMap(LEFT);
			_player->recovery();
			TEMPSOUNDMANAGER->stopMp3WithKey("BGM_hive");
			TEMPSOUNDMANAGER->playSoundWithKey("BGM_main");
		}
	}
	
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	_currentScene->render();
	this->getBackBuffer()->render(getHDC());
}

void MainGame::changeScene(string str)
{
	if (str == "main") {
		_currentScene = _main;
	}
	else if (str == "hive") {
		_currentScene = _hive;
	}
	else {
		_currentScene = _green;
	}
}
