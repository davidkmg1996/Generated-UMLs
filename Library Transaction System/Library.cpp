#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <commctrl.h>
#include <fstream>
#include <array>
#include "sqlite3.h"
#include "MS.h"
#include "Book.h"
#include "Member.h"
#include "tchar.h"
#include "Transaction.h"
#include "procedures.h"

using namespace std;

/*
* Based off of UML suggestion with
* screenshots provided.
*
* All relevant documentation included
* in MS header file, though none of it is
* revelant so I wouldn't bother being nosey
*/

HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	wchar_t LOG_NAME[500] = L"Login";

	WNDCLASS winL = {};
	winL.lpfnWndProc = login;
	winL.hInstance = hInstance;
	winL.lpszClassName = LOG_NAME;
	//Prevent black bars/ghosting
	winL.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winL.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&winL);

	HWND lwnd = CreateWindowEx(
		0,
		LOG_NAME,
		L"Login",
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		100, 100, 400, 200,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindowAsync(lwnd, nCmdShow);
	UpdateWindow(lwnd);

	

	//Use CreateMenu() for menuBar
	

	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}



	return (int)nMes.wParam;
}
