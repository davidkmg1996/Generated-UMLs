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

	wchar_t LIB_NAME[500] = L"Library";

	WNDCLASS winD = {};
	winD.lpfnWndProc = WindowProc;
	winD.hInstance = hInstance;
	winD.lpszClassName = LIB_NAME;
	//Prevent black bars/ghosting
	winD.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winD.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&winD);



	HWND hwnd = CreateWindowEx(
		0,
		LIB_NAME,
		L"Library Transaction System",
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindowAsync(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	//Use CreateMenu() for menuBar
	

	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}

	return (int)nMes.wParam;
}
