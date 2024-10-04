#include<Windows.h>
#include<string>
#include"resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "First", "List", "Box"};

BOOL CALLBACK ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_LIST), NULL, ListProc, 0);
	return 0;
}

BOOL CALLBACK ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);

		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
		{

		}
		break;
		case IDOK: 
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);

			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			
			if (index != LB_ERR)
			{
				CHAR* text = new CHAR[SendMessage(hList, LB_GETTEXTLEN, (WPARAM)index, 0)];
				SendMessage(hList, LB_GETTEXT, (WPARAM)index, (LPARAM)text);

				std::string buffer = "Вы выбрали пункт №" + std::to_string(index);
				buffer += " со значением ";
				buffer += text;
				MessageBox(NULL, buffer.c_str(), "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
				MessageBox(NULL, "Вы не выбрали значение!", "Info", MB_OK | MB_ICONERROR);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}