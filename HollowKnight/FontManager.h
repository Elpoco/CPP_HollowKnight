#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSizem, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);

	FontManager() {}
	~FontManager() {}

};

