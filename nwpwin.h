
#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
#include <tchar.h>
#include "Dlgdef.h"

typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR> tstringstream;

class Application
{
public:
	int Run();
};

class End_Dialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
};

class Window
{
	HWND hw;

protected:
	virtual tstring ClassName();
	bool Register(const tstring& name);
	tstring GenerateClassName();

public:
	Window();

	bool Create(HWND parent, DWORD style, LPCTSTR caption = 0, int IdOrMenu = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);

	operator HWND();
	static LRESULT CALLBACK Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//	messages
protected:
	virtual int OnCreate(CREATESTRUCT*) { return 0; }
	virtual void OnCommand(int) { }
	virtual void OnDestroy() { }
	virtual void OnKeyDown(int key) { }
	virtual void OnKeyUp(int key) { }
	virtual void OnKeyLeft(int key) {}
	virtual void OnKeyRight(int key) {}
	virtual void OnPaint(HDC dc) {}


};