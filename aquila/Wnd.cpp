#include "Wnd.h"

bool Wnd::Create(HINSTANCE hInstance, std::string aWindowName, int aWidth, int aHeight)
{
	WNDCLASSEX WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = mWndProc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = "Project Aquila";

	if (RegisterClassEx(&WndClassEx) == 0)
	{
		DEBUG_LOG("RegisterClassEx failed");
		return false;
	}

	mWindowName = aWindowName;
	mWidth = aWidth;
	mHeight = aHeight;

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ((mhWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassEx.lpszClassName, mWindowName.c_str(), Style, 0, 0, mWidth, mHeight, nullptr, nullptr, hInstance, nullptr)) == NULL)
	{
		DEBUG_LOG("CreateWindowEx failed");
		return false;
	}

	return true;
}

void Wnd::RePaint()
{
	mX = mY = 0;
	InvalidateRect(mhWnd, nullptr, false);
}

void Wnd::Show(bool aMaximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(mhWnd, &wRect);
	GetClientRect(mhWnd, &cRect);

	wRect.right += mWidth - cRect.right;
	wRect.bottom += mHeight - cRect.bottom;

	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;

	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(mhWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

	ShowWindow(mhWnd, aMaximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);

}

void Wnd::MsgLoop()
{
	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void Wnd::Destroy()
{
	DestroyWindow(mhWnd);
}

void Wnd::OnKeyDown(unsigned int aKey)
{

}