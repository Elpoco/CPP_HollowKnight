#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("start", "Resources/Images/BackGround/start.bmp", WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
}

void StartScene::render(void)
{
	IMAGEMANAGER->render("start", getMemDC());
}
