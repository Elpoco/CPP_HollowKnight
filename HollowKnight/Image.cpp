#include "Stdafx.h"
#include "Image.h"

#pragma comment (lib, "msimg32.lib")

Image::Image() : _imageInfo(NULL)
			   , _fileName(NULL)
		  	   , _isTrans(FALSE)
			   , _transColor(RGB(0,0,0)) 
			   , _blendImage(NULL)
{
}

HRESULT Image::init(int width, int height)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);
	
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;

	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const WCHAR * fileName, int width, int height)
{
	if (_imageInfo != NULL) this->release();

	_img = new Gdiplus::Image(fileName);
	if (_img->GetLastStatus() != Gdiplus::Ok) return warningAlert();
	_bmp = new Gdiplus::Bitmap(fileName, PixelFormat16bppARGB1555);

	int w = _img->GetWidth();
	int h = _img->GetHeight();
	
	if (width) {
		w = width;
	}
	if (height) {
		h = height;
	}

	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = w;
	_imageInfo->height = h;

	int len = wcslen(fileName);

	_fileName = new CHAR[len + 1];
	//wcstombs_s(_fileName, fileName, len + 1);

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const WCHAR * fileName, int maxFrameX, int maxFrameY, int maxFrame)
{
	if (_imageInfo != NULL) this->release();

	if (maxFrame == 0) maxFrame = maxFrameX;

	_img = new Gdiplus::Image(fileName);
	if (_img->GetLastStatus() != Gdiplus::Ok) return warningAlert();
	_bmp = new Gdiplus::Bitmap(fileName, PixelFormat16bppARGB1555);

	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = _img->GetWidth();
	_imageInfo->height = _img->GetHeight();
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = _img->GetWidth() / maxFrameX;
	_imageInfo->frameHeight = _img->GetHeight() / maxFrameY;
	_imageInfo->maxFrame = maxFrame - 1;

	int len = wcslen(fileName);

	_fileName = new CHAR[len + 1];
	//wcstombs(_fileName, fileName, len + 1);

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::setTransColor(BOOL isTrans, COLORREF transColopr)
{
	_isTrans = isTrans;
	_transColor = transColopr;
}

void Image::release(void)
{
	if (_imageInfo) {
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage) {
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}

	if (_graphics) {
		SAFE_DELETE(_graphics);
	}

	if (_img) {
		SAFE_DELETE(_img);
	}

	if (_bmp) {
		SAFE_DELETE(_bmp);
	}
}

void Image::render(HDC hdc)
{
	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else {
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		AlphaBlend(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	
}

void Image::frameRender(HDC hdc, int destX, int destY, int tick, bool reverseFrameX, BYTE alpha)
{
	if (_imageInfo->stopFrame) {
		if (_imageInfo->callback != NULL) {
			_imageInfo->callback();
		}
		return;
	}
	if (_imageInfo->currentFrameY > _imageInfo->maxFrameY) {
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	_imageInfo->x = destX;
	_imageInfo->y = destY;

	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_imageInfo->startTick == _imageInfo->currentFrameX) {
		if (_imageInfo->startCallback != NULL) {
			_imageInfo->startCallback();
		}
	}

	if (_imageInfo->endTick == _imageInfo->currentFrameX) {
		if (_imageInfo->endCallback != NULL) {
			_imageInfo->endCallback();
		}
	}

	if (_isTrans) {
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc,
			destX, destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);

		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0,0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
	
	_imageInfo->count++;
	if (!reverseFrameX && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX++;
	}
	if (reverseFrameX && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX--;
	}

	if (_imageInfo->currentFrameX > _imageInfo->maxFrameX) {
		if (_imageInfo->callback != NULL) {
			_imageInfo->callback();
			//_imageInfo->callback = NULL;
		}
		_imageInfo->currentFrameX = _imageInfo->startFrameX;
	}


	if (_imageInfo->currentFrameX < 0) {
		_imageInfo->currentFrameX = _imageInfo->maxFrame - _imageInfo->startFrameX;
		if (_imageInfo->callback != NULL) {
			_imageInfo->callback();
			//_imageInfo->callback = NULL;
		}
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) {
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY) {
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight) {
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH) {
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth) {
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW) {
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		} 
	}
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void Image::plusRender(HDC hdc, int destX, int destY, bool flipX, int angle, bool isCenter)
{
	Gdiplus::ImageAttributes imgAttr;
	//imgAttr.SetColorKey(_transColor, _transColor, Gdiplus::ColorAdjustTypeBitmap);
	if (_imageInfo->isLeft != flipX) {
		_imageInfo->isLeft = flipX;
		_img->RotateFlip(Gdiplus::RotateNoneFlipX);
		_bmp->RotateFlip(Gdiplus::RotateNoneFlipX);
	}
	//gp.RotateTransform(45, Gdiplus::MatrixOrderPrepend);


	//_bmp = new Gdiplus::Bitmap(_img->GetWidth(), _img->GetHeight(), PixelFormat16bppARGB1555);

	if (!_graphics) {
		_graphics = new Gdiplus::Graphics(hdc);
		//_graphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
		_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		_graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
		_graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);
		_graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);
	}

	float x = destX;
	float y = destY;
	if (isCenter) {
		x -= _imageInfo->width / 2;
		y -= _imageInfo->height / 2;
	}

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { (float)destX, (float)destY });
	_graphics->SetTransform(&matrix);

	_graphics->DrawImage(
		_bmp,
		Gdiplus::Rect(x, y, _imageInfo->width, _imageInfo->height),
		0, 0,
		_imageInfo->width, _imageInfo->height,
		Gdiplus::UnitPixel, &imgAttr, NULL, NULL);
}

void Image::plusRender(HDC hdc, int destX, int destY, int width, int height, bool flipX, bool isCenter)
{
	Gdiplus::ImageAttributes imgAttr;
	imgAttr.SetColorKey(_transColor, _transColor, Gdiplus::ColorAdjustTypeBitmap);

	if (!_graphics) {
		_graphics = new Gdiplus::Graphics(hdc);
		//_graphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
		_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		_graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
		_graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);
		_graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);
	}

	int x = destX;
	int y = destY;
	if (isCenter) {
		x -= width / 2;
		y -= height / 2;
	}

	_graphics->DrawImage(
		_bmp,
		Gdiplus::Rect(x, y, width, height),
		0, 0,
		_imageInfo->width, _imageInfo->height,
		Gdiplus::UnitPixel, &imgAttr, NULL, NULL);
}

bool Image::plusFrameRender(HDC hdc, int destX, int destY, int currentX, int currentY)
{
	_imageInfo->x = destX;
	_imageInfo->y = destY;
	_imageInfo->currentFrameX = currentX;
	_imageInfo->currentFrameY = currentY;

	if (!_graphics) {
		_graphics = new Gdiplus::Graphics(hdc);
		//_graphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
		_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		_graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
		_graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);
		_graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);
	}

	_graphics->DrawImage(
		_bmp,
		Gdiplus::Rect(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight), // 이미지 그릴 위치
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		Gdiplus::UnitPixel, NULL, NULL, NULL);

	return false;
}


bool Image::plusFrameRender(HDC hdc, int destX, int destY, int tick, BYTE alpha, bool isLeft)
{
	if (_imageInfo->isLeft != isLeft) {
		_imageInfo->isLeft = isLeft;
		if (isLeft) {
			_imageInfo->currentFrameX = 0;
		}
		else {
			_imageInfo->currentFrameX = _imageInfo->maxFrame;
		}
		_img->RotateFlip(Gdiplus::RotateNoneFlipX);
		_bmp->RotateFlip(Gdiplus::RotateNoneFlipX);
	}
	

	if (_imageInfo->currentFrameY > _imageInfo->maxFrameY) {
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	_imageInfo->x = destX;
	_imageInfo->y = destY;

	Gdiplus::ImageAttributes imgAttr;
	imgAttr.SetColorKey(RGB(255,0,255), RGB(255, 0, 255), Gdiplus::ColorAdjustTypeBitmap);
	
	//if (!_blendImage) initForAlphaBlend();

	//_blendFunc.SourceConstantAlpha = alpha;

	//Gdiplus::CachedBitmap CB(_bmp, &gp);


	//HBITMAP hBitmap;
	//_bmp->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitmap);
	//SelectObject(_imageInfo->hMemDC, hBitmap);
	//BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
	//	_imageInfo->currentFrameX * _imageInfo->frameWidth,
	//	_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);


	if (!_graphics) {
		_graphics = new Gdiplus::Graphics(hdc);
		//_graphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
		_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		_graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
		_graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);
		_graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed);
	}

	_graphics->DrawImage(
		_bmp,
		Gdiplus::Rect(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight), // 이미지 그릴 위치
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		Gdiplus::UnitPixel, &imgAttr, NULL, NULL);

	/*gp.DrawImage(
		_bmp, 
		Gdiplus::Rect(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight),
		Gdiplus::Rect(_imageInfo->currentFrameX * _imageInfo->frameWidth,
						_imageInfo->currentFrameY * _imageInfo->frameHeight,
						_imageInfo->frameWidth,
						_imageInfo->frameHeight)
		);*/


	_imageInfo->count++;
	if (isLeft && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX++;
	}
	if (!isLeft && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX--;
	}


	if (isLeft && _imageInfo->currentFrameX > _imageInfo->maxFrameX) {
		_imageInfo->currentFrameX = _imageInfo->startFrameX;
		if (_imageInfo->callback != NULL) {
			_imageInfo->callback();
			_imageInfo->callback = NULL;
		}
		return true;
	}

	if (!isLeft && _imageInfo->currentFrameX < _imageInfo->maxFrame - _imageInfo->maxFrameX) {
		_imageInfo->currentFrameX = _imageInfo->maxFrameX - _imageInfo->startFrameX;
		if (_imageInfo->callback != NULL) {
			_imageInfo->callback();
			_imageInfo->callback = NULL;
		}
		return true;
	}

	return false;
}

HRESULT Image::warningAlert()
{
	MessageBox(_hWnd, TEXT("이미지 오류"), TEXT("에러"), MB_OK); 
	return E_FAIL;
}
