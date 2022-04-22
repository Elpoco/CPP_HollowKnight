#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{
	return S_OK;
}

void EffectManager::release(void)
{
	_EffectList.clear();
}

void EffectManager::render(HDC hdc)
{
	_iter = _EffectList.begin();
	for (; _iter != _EffectList.end();) {
		bool endEffect = false;
		if (_iter->time > 0) {
			if (_iter->startTime + _iter->time <= GetTickCount64()) {
				endEffect = true;
			}
			else {
				_iter->image->plusRender(hdc, _iter->pos.x, _iter->pos.y, _iter->size.x, _iter->size.y, _iter->isLeft, true);
			}
		}
		else {
			endEffect = _iter->image->plusFrameRender(hdc, _iter->pos.x, _iter->pos.y, _iter->tick, 0, _iter->isLeft);
		}

		if (endEffect) {
			_iter = _EffectList.erase(_iter);
		}
		else ++_iter;
	}
}

void EffectManager::addEffect(string strKey, POINT pos, POINT movePos, POINT size, bool isLeft, int tick, int time, float angle, bool isCenter)
{
	EffectInfo ei = { strKey, pos, movePos, size, isLeft, tick, time, angle };
	ei.startTime = GetTickCount64();
	ei.image = IMAGEMANAGER->findImage(strKey);
	if (isCenter) {
		pos.x -= ei.image->getFrameWidth() / 2;
		pos.y -= ei.image->getFrameHeight() / 2;
	}
	_EffectList.push_back(ei);

}

bool EffectManager::isEffect(string strKey)
{
	bool res = false;
	for (auto effect : _EffectList) {
		if (effect.name == strKey) {
			res = true;
		}
	}
	return res;
}
