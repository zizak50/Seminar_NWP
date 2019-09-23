#include <windows.h>
#include "Dlgdef.h"
#include "resource1.h"

INT CALLBACK Dialog::Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	//TODO: read number of moves made
	int i = 0;
	switch (Message)
	{
	case WM_INITDIALOG:

		if (i <= 7)
		{
			SetDlgItemText(hwnd, IDC_STATIC_RESULT, "PRO");

		}
		if (i >= 9)
		{
			SetDlgItemText(hwnd, IDC_STATIC_RESULT, "AVRAGE");
		}
		else
		{
			SetDlgItemText(hwnd, IDC_STATIC_RESULT, "NOOB");
		}
		//SetDlgItemText(hwnd, IDC_STATIC_MOVES,"%d"i);
		return TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_QUIT:
			EndDialog(hwnd, IDOK);
			::PostQuitMessage(0);
			break;
		case ID_NewGame:

			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	}
	return FALSE;
}

int Dialog::DoModal(HINSTANCE hInst, HWND parent)
{
	return DialogBoxParam(hInst, MAKEINTRESOURCE(IDD()), parent, Proc,
		reinterpret_cast<LPARAM>(this));
}