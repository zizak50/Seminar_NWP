#include <windows.h>
#include "Dlgdef.h"
#include "resource1.h"
#include <map>



INT CALLBACK Dialog::Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	static std::map<HWND, Dialog*> wmap;
	if (Message == WM_INITDIALOG)
	{
		Dialog* pThis = reinterpret_cast<Dialog*>(lParam);
		pThis->hw = hwnd;
		wmap[hwnd] = pThis;
		return pThis->OnInitDialog(hwnd);
	}
	Dialog* pThis = wmap[hwnd];
	if (Message == WM_COMMAND)
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			pThis->OnCancel();
			return EndDialog(hwnd, IDCANCEL);
		}
		return pThis->OnCommand(LOWORD(wParam), HIWORD(wParam));
	}
	if (Message == WM_DESTROY)
		wmap.erase(hwnd);
	return 0;
}

int Dialog::DoModal(HINSTANCE hInst, HWND parent)
{
	return DialogBoxParam(hInst, MAKEINTRESOURCE(IDD()), parent, Proc,
		reinterpret_cast<LPARAM>(this));
}