#ifndef _AQUILA_WINDOWS_H_
#define _AQUILA_WINDOWS_H_

#include "Common.h"
#include "Windows.h"
#include "Image.h"

class Wnd
{
public:
	Wnd(const Image* aImage);
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
	void OnPaint();
	//void OnLButtonDown(int aX, int aY);
	//void OnResize();

private:
	const Image* mImage;

	std::string mWindowName;
	HWND mhWnd;
	int mWidth, mHeight, mX, mY, mLastX, mLastY;
	WNDPROC mWndProc;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow);

#endif