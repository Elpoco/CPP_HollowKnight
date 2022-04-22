#pragma once

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

// 선그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMake(int x, int y, int width, int height, int posX, int posY)
{
	RECT rc = { x + posX, y + posY, x + width + posX, y + height + posY };
	return rc;
}

// RECT 중심점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

// 사각형 그리기(렉탱글 함수 사용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// 타원 그리기 (Ellipse() 함수 사용)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 타원 센터점 중심으로 그리기 (Ellipse() 함수 사용)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void RectangleMakeRect(HDC hdc, RECT rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void RectangleMakeRect(HDC hdc, RECT rc, int x, int y) {
	Rectangle(hdc, x+rc.left, y+rc.top, x+rc.right, y+rc.bottom);
}

inline void PolygonMake(HDC hdc, POINT points[], int size) {
	Polygon(hdc, points, size);
}

template <typename T>
inline int GetArrLen(T arr[]) {
	return sizeof(*arr) / sizeof(*arr[0]);
}