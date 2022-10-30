#pragma once
#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Maths.h"
#include "def.h"

#pragma comment(lib, "Msimg32.lib") 

struct WindowData
{
	HWND hWnd;
	HDC hdc;

	HBITMAP backtexture;
	HDC backBuffer;

	UINT width;
	UINT height;

	void clear()
	{
		hWnd = nullptr;
		hdc = nullptr;
		width = 0;
		height = 0;
	}
};

struct Pen
{
private:
	HDC mHdc;
	HPEN mOldPen;
	HPEN mPen;

public:
	Pen(HDC hdc, HPEN pen)
		: mHdc(hdc)
		, mOldPen(NULL)
		, mPen(pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	}

	~Pen()
	{
		SelectObject(mHdc, mOldPen);
		DeleteObject(mPen);
	}
};

struct Brush
{
private:
	HDC mHdc;
	HBRUSH mOldBrush;
	HBRUSH mBrush;

public:
	Brush(HDC hdc, HBRUSH brush)
		: mHdc(hdc)
		, mOldBrush(NULL)
		, mBrush(brush)
	{
		mOldBrush = (HBRUSH)SelectObject(mHdc, brush);
	}

	~Brush()
	{
		SelectObject(mHdc, mOldBrush);
		DeleteObject(mBrush);
	}
};

struct Text
{
private:
	HDC mHdc;
	int mx;
	int my;

public:
	Text(HDC hdc, const wchar_t* text, int x, int y)
		: mHdc(hdc)
		, mx(x)
		, my(y)
	{
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, text);
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, x, y, szFloat, strLen);
	}

	~Text()
	{

	}
};