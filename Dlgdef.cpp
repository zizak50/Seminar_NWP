#include <windows.h>
#include "Dlgdef.h"
#include "resource1.h"

INT CALLBACK Dialog::Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	//TODO: read number of moves made
	int i =9;

	char s[128];

	switch (Message)
	{
	case WM_INITDIALOG:

		if (i <= 7)
		{
			LoadString(0, IDS_STRING107, s, sizeof s);
			SetDlgItemText(hwnd, IDC_STATIC_RESULT, s);

		}
		if (i >= 9)
		{
			LoadString(0, IDS_STRING106, s, sizeof s);
			SetDlgItemText(hwnd, IDC_STATIC_RESULT, s);
		}
		if (i>=11)
		{
			LoadString(0, IDS_STRING105, s, sizeof s);
			SetDlgItemText(hwnd, IDC_STATIC_RESULT,s);
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