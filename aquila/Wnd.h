#ifndef _AQUILA_WINDOWS_H_
#define _AQUILA_WINDOWS_H_

#include "Common.h"
#include "Windows.h"

class Wnd
{
public:
	Wnd();
	Wnd(WNDPROC aWndProc);
	void SetCallBack(WNDPROC aWndProc);

	bool Create(HINSTANCE hInstance, std::string aWindowName, int aWidth, int aHeight);
	void RePaint();
	void Show(bool aMaximized = false);
	void MsgLoop();
	void Destroy();

	//Event function
	//void OnKeyDown(unsigned int aKey);
	//void OnMouseMove(int aX, int aY);
	//void OnMouseWheel(int aZ);
	//void OnPaint();
	//void OnLButtonDown(int aX, int aY);
	//void OnResize();

private:
	std::string mWindowName;
	HWND mhWnd;
	int mWidth, mHeight, mX, mY, mLastX, mLastY;
	WNDPROC mWndProc;
};

#endif