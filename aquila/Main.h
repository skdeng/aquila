#ifndef _AQUILA_MAIN_H
#define _AQUILA_MAIN_H

#include "Raytracer.h"
#include "Camera.h"
#include "Wnd.h"

class Main
{
public:
	static Main Instance;

	void Execute(HINSTANCE ahInstance);
private:
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			Main::Instance.mWnd.OnPaint();
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0;
	}
	Camera mCamera;
	Raytracer mRaytracer;
	Wnd mWnd;
};

#endif