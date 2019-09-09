#include "nwpwin.h"
#include "resource1.h"
#include <windows.h>
#include <String.h>


class MyWindow : public Window {

	Button start, setting, quit;
	Window game;

	static WNDPROC origEditWndProc;

public:
	MyWindow() {};
protected:
	int OnCreate(CREATESTRUCT* psc)
	{
		char s[128];
		LoadString(0, IDS_STRING101, s, sizeof s);
		start.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, (int)(HMENU)IDC_BUTTON1, 150, 150, 200, 100);

		LoadString(0, IDS_STRING102, s, sizeof s);
		setting.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, (int)(HMENU)IDC_BUTTON2, 450, 150, 200, 100);

		LoadString(0, IDS_STRING103, s, sizeof s);
		quit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, (int)(HMENU)IDC_BUTTON3, 575, 450, 200, 100);


		return 0;
	}
	void OnCommand(int id)
	{
		if (id == 1) {
			MessageBox(NULL, "one", "NWP", MB_OK | MB_ICONWARNING);
		}

	}

	void OnDestroy()
	{
		::PostQuitMessage(0);
	}

	static LRESULT CALLBACK EditWndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
	{
		if (msg == WM_CHAR)
			return 0;
		return CallWindowProc(origEditWndProc, hw, msg, wp, lp);
	}

};

WNDPROC MyWindow::origEditWndProc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MyWindow wnd;
	
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	char s[128];
	LoadString(0, IDS_STRING104, s, sizeof s);
	wnd.Create(NULL, WS_OVERLAPPED | WS_VISIBLE,s, (int)hMenu, CW_USEDEFAULT, CW_USEDEFAULT,800,600);

	return app.Run();
}

