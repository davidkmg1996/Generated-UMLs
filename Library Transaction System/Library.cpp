#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "MS.h"
#include "Book.h"
#include "Member.h"
#include "tchar.h"
#include "Transaction.h"


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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	wchar_t LIB_NAME[500] = L"Library";

	WNDCLASS winD = {};
	winD.lpfnWndProc = WindowProc;
	winD.hInstance = hInstance;
	winD.lpszClassName = LIB_NAME;
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

	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}

	return (int)nMes.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	vector<Book> bVector;

	Library lib;

	Book b1 = Book("A Farewell to Arms", "Ernest Hemingway", "1451658168", true, "Fiction");
	Book b2 = Book("Lord of The Flies", "William Golding", "0399501487", true, "Fiction");
	lib.addBook(b1);
	lib.addBook(b2);

	Member* m1;

	m1 = new Member(L"David", L"Sesame Street", 999, bVector);

	lib.returnBook(*m1, b1);

		PAINTSTRUCT paint;
		HDC begin = BeginPaint(hwnd, &paint);

		TextOut(begin, 10, 10, lib.RegisterMember(m1).c_str(), wcslen(lib.RegisterMember(m1).c_str()));

		m1->borrowBook(b1);
		cout << b1.isAvailable();
		m1->borrowBook(b2);
		m1->returnBook(b1);

		switch (uMsg) {
		
		/*
		* If you're going to close the window,
		* just close the window.
		* kthx
		*/
		case WM_CLOSE: {

			DestroyWindow(hwnd);
			break;
			}

		case 0x0002: {

			PostQuitMessage(0);
			break;

			}
		}


	
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}