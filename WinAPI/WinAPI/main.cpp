#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - экземпляр запущенного *.ехе-файла нашей программы
	//hPrevInst - не используется
	//LPSTR - Long Pointer to STRing
	//lpCmdLine - CommandLine(Командная строка с параметрами запуска приложения)
	//nCmdShow - режим отображения окна
	//Префиксы: n..., lp..., это Венгерская нотация
	//	n - Number
	//	lp - Long Pointer
	//	h - HINSTANCE
	// Модальное окно блокирует родительское окно

	/*MessageBox
	(
		NULL,
		"Hello, Windows!\nThis is MessageBox()",
		"Window title",
		MB_CANCELTRYCONTINUE | MB_HELP | MB_DEFBUTTON3
		| MB_ICONINFORMATION 
	);*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*hwnd - Handler to window.Обработчик ил дескриптор окна - это число при помощи которого можно
	  обратиться к окну
	  uMsg - cooбщение которое отправляется окну
	  wParam, lParam - параметры сообщения, у каждого сообщения свой набор параметров.
	*/
	switch (uMsg)
	{
	case WM_INITDIALOG: // Это сообщение отправляется 1 раз при инициализации окна
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
	}
		break;
	case WM_COMMAND: // Обрабатывает нажатие кнопок и др. действия пользовотеля
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strcmp(sz_buffer, "") == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			}
			//EN_ - edit Notification
		}
			break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};

			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0); 
		break;
	}
	return FALSE;
}