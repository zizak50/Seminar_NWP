#include "nwpwin.h"

int Application::Run(){
	MSG msg;

	while (::GetMessage(&msg, NULL, 0, 0)) 
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

tstring Window::ClassName() {
	return tstring();
}

bool Window::Register(const tstring& name) {

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = Proc;
	wc.lpszClassName = name.c_str();
	wc.cbWndExtra = sizeof(Window*);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	

	return RegisterClass(&wc) != 0;
}

tstring Window::GenerateClassName() {
	tstringstream ss;
	ss << _T("Maze Game");
	return ss.str();
}

Window::Window() :hw(0) {}

bool Window::Create(HWND parent, DWORD style, LPCTSTR caption, int IdOrMenu, int x, int y, int widht, int hight) 
{
	tstring cn = ClassName();
	if (cn.empty())
	{
		Register(cn = GenerateClassName());
	}

	hw = ::CreateWindow(cn.c_str(), caption, style, x, y, widht, hight, parent, (HMENU)IdOrMenu, 0, this);

	return hw != 0;
}

Window::operator HWND() { return hw; }

POINT GetPoint(LPARAM lp)
{
	POINT p;
	p.x = GET_X_LPARAM(lp);
	p.y = GET_Y_LPARAM(lp);
	return p;
}

LRESULT CALLBACK Window::Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE) {
		CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* pw = reinterpret_cast<Window*>(pcs->lpCreateParams);
		::SetWindowLong(hwnd, 0, reinterpret_cast<long>(pw));
		pw->hw = hwnd;
		return pw->OnCreate(pcs);
	}

	Window* pThis = reinterpret_cast<Window*>(::GetWindowLong(hwnd, 0));
	switch (message)
	{
	case WM_COMMAND:		pThis->OnCommand(LOWORD(wParam));			return 0;
	case WM_DESTROY:		pThis->OnDestroy();							return 0;
	case WM_KEYUP:  pThis->OnKeyUp(wParam); return 0;
	case WM_KEYDOWN: pThis->OnKeyDown(wParam); return 0;
	case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			pThis->OnPaint(hdc);
			EndPaint(hwnd, &ps);
			return 0;
	}
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}