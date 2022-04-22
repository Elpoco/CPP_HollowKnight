#pragma once

class Image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;
		BYTE		loadType;

		int count;
		int startFrameX;
		int startFrameY;
		bool isLeft;
		int maxFrame;

		function<void()> callback;
		function<void()> startCallback;
		function<void()> endCallback;
		int startTick;
		int endTick;
		bool stopFrame;

		bool isFlip;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;

			count = 0;
			startFrameX = 0;
			startFrameY = 0;
			isLeft = true;
			maxFrame = 0;

			callback = NULL;

			startCallback = NULL;
			endCallback = NULL;
			startTick = 0;
			endTick = 0;
			stopFrame = false;
			isFlip = false;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_isTrans;		// 배경색 유무
	COLORREF		_transColor;	// 배경색을 없앨 RGB값   RGB(각각 1바이트 0~255 농도 표현 가능)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

	Gdiplus::Graphics* _graphics;
	Gdiplus::Image* _img;
	Gdiplus::Bitmap* _bmp;

public:
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// gdi+
	HRESULT init(const WCHAR* fileName, int width = 0, int height = 0);
	HRESULT init(const WCHAR* fileName, int maxFrameX, int maxFrameY, int maxFrame);

	HRESULT initForAlphaBlend(void);

	void setTransColor(BOOL isTrans, COLORREF transColopr);

	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY, int tick, bool reverseFrameX = false, BYTE alpha = 0);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// ====
	// gdi+
	// ====
	void plusRender(HDC hdc, int destX, int destY, bool flipX = false, int angle = 0.0f, bool isCenter = false);
	void plusRender(HDC hdc, int destX, int destY, int width, int height, bool flipX = false, bool isCenter = false);
	bool plusFrameRender(HDC hdc, int destX, int destY, int currentX, int currentY);
	bool plusFrameRender(HDC hdc, int destX, int destY, int tick, BYTE alpha = 0, bool reverseFrameX = false);

	// ==============
	// # 인라인 함수 #
	// ==============

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline RECT boundingBox(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	inline RECT boundingBoxWithFrame(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) {
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		if (_imageInfo->currentFrameY == frameY) return;

		_imageInfo->currentFrameY = frameY;
		_imageInfo->currentFrameX = _imageInfo->isLeft ? 0 : _imageInfo->maxFrame;
	}

	inline void setFrameY(int frameY, int maxFrameX, int startFrameX) {
		if (_imageInfo->currentFrameY == frameY) return;

		_imageInfo->currentFrameY = frameY;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->startFrameX = startFrameX;

		_imageInfo->callback = NULL;

		_imageInfo->currentFrameX = _imageInfo->isLeft ? 0 : _imageInfo->maxFrame;

		if (frameY > _imageInfo->maxFrameY) {
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	typedef function<void()> func;

	inline void setFrameY(int frameY, int maxFrameX, func callback = NULL, int currentFrameX = 0, 
							func startTickCallback = NULL, int startTick = 0,
							func endTickCallback = NULL, int endTick = 0) {
		if (_imageInfo->currentFrameY == frameY && _imageInfo->maxFrameX == maxFrameX) return;

		if(callback != NULL) _imageInfo->callback = callback;
		_imageInfo->startCallback = startTickCallback;
		_imageInfo->endCallback = endTickCallback;
		_imageInfo->startTick = startTick;
		_imageInfo->endTick = endTick;

		_imageInfo->currentFrameY = frameY;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->startFrameX = currentFrameX;
		
		_imageInfo->currentFrameX = _imageInfo->isLeft ? currentFrameX : _imageInfo->maxFrame - currentFrameX;

		if (frameY > _imageInfo->maxFrameY) {
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline void setFrame(int frameX, int frameY, int maxFrameX, int startFrameX) {
		_imageInfo->currentFrameX = frameX;
		_imageInfo->currentFrameY = frameY;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->startFrameX = startFrameX;
	}

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


	inline void setMaxFrameX(int frameX) { _imageInfo->maxFrameX = frameX - 1; }
	inline void setStartFrameX(int startX) { _imageInfo->startFrameX = startX; }
	inline void setCallback(func callback) { _imageInfo->callback = callback; }
	void stopFrame() { _imageInfo->stopFrame = true; }
	void startFrame() { _imageInfo->stopFrame = false; }

	HRESULT warningAlert();

	Image();
	~Image() {}
};

