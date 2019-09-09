#include "nwpwin.h"
#include "resource1.h"
#include <windows.h>
#include <String.h>

class Button:public Window
{
public:
	std::string ClassName() { return "BUTTON"; }
};

class MyWindow : public Window {

	static WNDPROC origEditWndProc;

public:
	MyWindow() {};
protected:
	int OnCreate(CREATESTRUCT* psc)
	{
		Button start, setting, quit;
		char s[128];

		LoadString(0, IDS_STRING101, s, sizeof s);
		start.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_START, 150, 150, 200, 100);

		LoadString(0, IDS_STRING102, s, sizeof s);
		setting.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_SETTING, 400, 150, 200, 100);

		LoadString(0, IDS_STRING103, s, sizeof s);
		quit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_QUIT, 575, 500, 200, 50);

		return 0;
	}
	void OnCommand(int id)
	{
		switch (id)
		{
		/*case IDC_START:
			return 0;
		case IDC_SETTING:
			return 0;*/
		case IDC_QUIT:
			printf("qwer");
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

