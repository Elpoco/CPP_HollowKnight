#include "Stdafx.h"
#include "MainGame.h"

/*
Hollow Knight
Enter: 게임시작, F1: 디버그, Z: 점프, X: 공격, 방향키로 이동
게임에 등장하는 벌집기사와 호넷 이라는 보스를 구현했습니다.

gdi+로 이펙트와 작은 오브젝트들 이미지 회전을 사용했습니다.

사용자 키 입력은 애니메이션 관리해주는 객체를 만들어
벡터로 저장을 하여 애니메이션 프레임이 끝날때마다 callback을 받아
다음 애니메이션으로 넘어가는 방식으로 동작을 합니다.

보스 패턴은 랜덤으로 실행 됩니다.
보스가 소환하는 유닛도 공격이 가능하고,
던지는 무기도 서로 칠수 있도록 구현 했습니다.
보스가 공격할때 맞공격을 하면 패링을 하도록 만들었습니다. (타이밍 중요!!)

보스방에 들어가면 다시 나올수 없게 막히고
잡으면 다시 복귀할 수 있습니다.
메인 화면으로 가면 체력이 다시 회복 됩니다.

그 외에는 시간 부족...ㅠㅠ
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
