#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;  
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height, HWND hWnd);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new MainGame();
	_hInstance = hInstance;

	ULONG_PTR gpToken;
	Gdiplus::GdiplusStartupInput gpsi;
	if (Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL) != Gdiplus::Ok) return 0;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;									
	wndClass.cbWndExtra = 0;									
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			
	wndClass.hInstance = hInstance;								
	wndClass.lpfnWndProc = (WNDPROC)WndProc;					
	wndClass.lpszClassName = WINNAME;							
	wndClass.lpszMenuName = NULL;								
	wndClass.style = CS_HREDRAW | CS_VREDRAW;					

	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	DEVMODE dm;

	dm.dmBitsPerPel = 32;			
	dm.dmPelsWidth = 1920;			
	dm.dmPelsHeight = 1200;			
	dm.dmDisplayFrequency = 60;		

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

#else
	_hWnd = CreateWindow
	(
		WINNAME,				
		WINNAME,				
		WINSTYLE,				
		WINSTART_X,				
		WINSTART_Y,				
		WINSIZE_X,				
		WINSIZE_Y,				
		NULL,					
		(HMENU)NULL,			
		hInstance,				
		NULL					
								
	);

#endif
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y, _hWnd);

	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init())) {
		return 0;
	}

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	_mg->release();
	UnregisterClass(WINNAME, hInstance);

	Gdiplus::GdiplusShutdown(gpToken);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height, HWND hWnd)
{
	RECT rc = { 0,0, width, height };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
