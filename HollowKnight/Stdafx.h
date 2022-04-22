#pragma once
#include<SDKDDKVer.h>

#include <Windows.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>

#include <functional>

using namespace std;

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")


// =================================
#include "CommonMacroFuntion.h"
#include "RandomFuntion.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"

// =======================
#define RND RandomFuntion::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()

// ==========================
#define WINNAME				(LPSTR)(TEXT("Hollow Kight"))

//#define  FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X			0
#define WINSTART_Y			0
#define WINSIZE_X			GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y			GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE 
#else
#define WINSTART_X			100//-10
#define WINSTART_Y			0
#define WINSIZE_X			1600//GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y			900//GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE			WS_CAPTION | WS_SYSMENU 
#endif

#define MAGENTA				RGB(255, 0, 255)
#define PI		3.141592f		

// =============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
// =============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p)=nullptr;}}

// =============
// # 전역 변수 #
// =============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;


typedef function<void()> func;
