#pragma once
#include "SingletonBase.h"

class RandomFuntion : public SingletonBase<RandomFuntion>
{
public:
	RandomFuntion()
	{
		srand(GetTickCount());
	}
	~RandomFuntion() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	// 주의사항 0이 나오면 터진다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};