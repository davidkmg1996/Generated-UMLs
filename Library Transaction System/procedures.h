#include "vars.h"
#include <windows.h>
#define ABOUT 2250
#define QUIT 1000
#define OPEN 2255
#define LOGIN 2250
#define	REGISTER 2500
#define TRUEREG 2750
#define BACK 3000
#define MEMBER 3250
#define LOGOUT 3300
varsH v;
bool bEmpty;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL);
LRESULT CALLBACK login(HWND lwnd, UINT lMsg, WPARAM lParam, LPARAM lParamL);
LRESULT CALLBACK RegisterProc(HWND rwnd, UINT rMsg, WPARAM rParam, LPARAM rParamL);

void showLoginWindow() {
	HICON hIcon = (HICON)LoadImage(NULL, L"newlts.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wchar_t LOG_NAME[500] = L"Login";
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS winL = {};
	winL.lpfnWndProc = login;
	winL.hInstance = hInstance;
	winL.lpszClassName = LOG_NAME;
	winL.hIcon = hIcon;
	//Prevent black bars/ghosting
	winL.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winL.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&winL);

	HWND lwnd = CreateWindowEx(
		0,
		LOG_NAME,
		L"Login",
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		100, 100, 700, 500,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindowAsync(lwnd, SW_SHOW);
	UpdateWindow(lwnd);



	//Use CreateMenu() for menuBar


	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}


}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static HFONT font;

	static wstring out;

	BS_PUSHBUTTON();

	switch (uMsg) {

	case WM_CREATE:
	{
		font = CreateFont(
			20,
			0,
			0,
			0,
			FW_NORMAL,
			FALSE,
			FALSE,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH || FF_SWISS,
			TEXT("Helvetica"));

		InvalidateRect(hwnd, NULL, TRUE);

		HINSTANCE inst = ((LPCREATESTRUCT)lParam)->hInstance;
	
		HMENU menuBar = CreateMenu();
		HMENU fMenu = CreatePopupMenu();
		AppendMenu(fMenu, MF_STRING, OPEN, L"Open Catalog");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)fMenu, L"File");


		HMENU aMenu = CreatePopupMenu();
		AppendMenu(aMenu, MF_STRING, ABOUT, L"About This Program");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)aMenu, L"About");

		HMENU oMenu = CreatePopupMenu();
		AppendMenu(oMenu, MF_STRING, QUIT, L"Quit");
		AppendMenu(oMenu, MF_STRING, LOGOUT, L"Log Out");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)oMenu, L"Options");

		SetMenu(hwnd, menuBar);

		break;

	}

	case WM_COMMAND:
	{	

		if (LOWORD(wParam) == QUIT) {
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}

		if (LOWORD(wParam) == LOGOUT) {
			DestroyWindow(hwnd);
			showLoginWindow();
		}

		if (LOWORD(wParam) == ABOUT) {
			MessageBox(hwnd, L"Library Management System\n\nVersion 0.2.1\n\nCreated by: davidkmg1996", L"About", MB_OK | MB_ICONINFORMATION);
		}

		if (LOWORD(wParam) == OPEN) {
			ShellExecute(NULL, L"open", L"C:\\", NULL, NULL, SW_SHOWDEFAULT);
		}

		break;
	}


	case WM_PAINT:

	{
			PAINTSTRUCT p;
			RECT r;
			HDC hdc = BeginPaint(hwnd, &p);
			HFONT oFont = (HFONT)SelectObject(hdc, font);
	
			/*
			* TextOut(param1, param2, . . . , param5)
			* does not support carriage return
			*
			* and neither do I
			*/

			GetClientRect(hwnd, &r);
			SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);

			if (bEmpty == false) {
				DrawText(hdc, out.c_str(), -1, &r, DT_WORDBREAK | DT_CENTER);
			}
		

			EndPaint(hwnd, &p);
			break;



	}

	/*
	* If you're going to close the window,
	* just close the window.
	* kthx
	*/

	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}

	case WM_DESTROY: {

		PostQuitMessage(0);
		break;

	}
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL) {

	PAINTSTRUCT e;
	HDC edc;
	RECT eR;

	switch (eMsg) {
		
	case WM_PAINT: {
		edc = BeginPaint(nwnd, &e);
		SetTextColor(edc, RGB(0, 0, 0));
		SetBkMode(edc, TRANSPARENT);
		GetClientRect(nwnd, &eR);
		DrawText(edc, L"Member Name must contain only alphabetic characters", -1, &eR, DT_WORDBREAK);
		EndPaint(nwnd, &e);
		break;
	}

	case WM_CLOSE:
		DestroyWindow(nwnd);
		break;

	}

	return DefWindowProc(nwnd, eMsg, eParam, eParamL);

}


void showMainScreen() {
	wchar_t LIB_NAME[500] = L"Library";
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	HICON hIcon = (HICON)LoadImage(NULL, L"newlts.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	WNDCLASS winD = {};
	winD.lpfnWndProc = WindowProc;
	winD.hInstance = hInstance;
	winD.lpszClassName = LIB_NAME;
	winD.hIcon = hIcon;
	//Prevent black bars/ghosting
	winD.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winD.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&winD);
	wstring header = L"Library Transaction System (" + v.getUsername() + L")";
	LPCWSTR head = header.c_str();

	HWND hwnd = CreateWindowEx(
		0,
		LIB_NAME,
		head,
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	

	ShowWindowAsync(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = {};

	/*
	* NEVER FORGET TO TRANSLATE AND
	* DISPATCH MESSAGE
	*/
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	

}


void registrationWindow() {

	wchar_t REG_NAME[500] = L"Register";
	HICON hIcon = (HICON)LoadImage(NULL, L"newlts.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS winR = {};
	winR.lpfnWndProc = RegisterProc;
	winR.hInstance = hInstance;
	winR.lpszClassName = REG_NAME;
	//Prevent black bars/ghosting
	winR.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winR.hCursor = LoadCursor(nullptr, IDC_ARROW);
	winR.hIcon = hIcon;

	RegisterClass(&winR);

	HWND rwnd = CreateWindowEx(
		0,
		REG_NAME,
		L"Register",
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		100, 100, 400, 300,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindowAsync(rwnd, SW_SHOW);
	UpdateWindow(rwnd);

	MSG msg2 = {};

	while (GetMessage(&msg2, nullptr, 0, 0)) {
		TranslateMessage(&msg2);
		DispatchMessage(&msg2);
	}


}



LRESULT CALLBACK login(HWND lwnd, UINT lMsg, WPARAM lParam, LPARAM lParamL) {

	static HFONT font;
	wchar_t userN[256];
	wchar_t passN[256];
	static HWND userName;
	static HWND password;
	static HWND getU;
	static HWND getP;

	switch (lMsg) {
		
		RECT lm;

	case WM_CREATE: {

		font = CreateFont(
			20,
			0,
			0,
			0,
			FW_NORMAL,
			FALSE,
			FALSE,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			TEXT("Helvetica"));

		InvalidateRect(lwnd, NULL, TRUE);

		
		HINSTANCE inst2 = ((LPCREATESTRUCT)lParamL)->hInstance;
		userName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT, 235, 280, 200, 24, lwnd, 0, inst2, 0);
		password = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 235, 310, 200, 24, lwnd, 0, inst2, 0);
		getU = CreateWindowEx(0, L"button", L"Login", WS_CHILD | WS_VISIBLE, 233, 340, 100, 40, lwnd, (HMENU)LOGIN, inst2, 0);
		getP = CreateWindowEx(0, L"button", L"Register", WS_CHILD | WS_VISIBLE, 335, 340, 100, 40, lwnd, (HMENU)REGISTER, inst2, 0);
		wchar_t user[] = L"Username";
		wchar_t pass[] = L"Password";
		SendMessage(userName, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(password, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(getU, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(getP, WM_SETFONT, (WPARAM)font, TRUE);	
		Edit_SetCueBannerText(userName, user);
		Edit_SetCueBannerText(password, pass);


		break;
	}

	case WM_COMMAND: {

		if (LOWORD(lParam) == LOGIN) {

			GetWindowText(userName, userN, sizeof(userN) / sizeof(wchar_t));
		
			sqlite3* db;
			int getDb = sqlite3_open("registered", &db);;
			const char* openUsers = "SELECT * FROM registered WHERE username = ?";
			sqlite3_stmt* n;

		
			getDb = sqlite3_prepare_v2(db, openUsers, -1, &n, nullptr);
			string username(userN, userN + wcslen(userN));
			v.setUsername(userN);
			sqlite3_bind_text(n, 1, username.c_str(), -1, SQLITE_TRANSIENT);

			getDb = sqlite3_step(n);

			if (getDb != SQLITE_OK && getDb != SQLITE_ROW && getDb != SQLITE_DONE) {
				MessageBox(lwnd, L"Failed to prepare statement", L"Error", MB_OK | MB_ICONERROR);
				MessageBoxA(lwnd, sqlite3_errmsg(db), "SQLite Error", MB_OK | MB_ICONERROR);
				sqlite3_close(db);
				return 0;
			}


			if (getDb == SQLITE_ROW) {
				
				DestroyWindow(lwnd);
				showMainScreen();
			}
			else if (getDb == SQLITE_DONE) {
				
				DestroyWindow(lwnd);
				registrationWindow();
			}

			sqlite3_finalize(n);
			sqlite3_close(db);

			
			break;
		}

		else if (LOWORD(lParam) == REGISTER) {
			DestroyWindow(lwnd);
			registrationWindow();
			break;

		}
	}



	case WM_PAINT: {

		PAINTSTRUCT w;
		HDC loginMessage = BeginPaint(lwnd, &w);

		HFONT oFont = (HFONT)SelectObject(loginMessage, font);
		SetTextColor(loginMessage, RGB(0, 0, 0));;
		SetBkMode(loginMessage, TRANSPARENT);
		GetClientRect(lwnd, &lm);
		DrawText(loginMessage, L"Please Enter Username and Password", -1, &lm, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
		EndPaint(lwnd, &w);
		break;
	}

	case WM_CLOSE:
		DestroyWindow(lwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(lwnd, lMsg, lParam, lParamL);
}


LRESULT CALLBACK RegisterProc(HWND rwnd, UINT rMsg, WPARAM rParam, LPARAM rParamL) {


	static HWND firstName;
	static HWND lastName;
	static HWND address;
	static HWND userName;
	static HWND password;
	static HWND reg;
	static HWND regb;
	static HFONT font;

	string firstN;
	string lastN;
	string addr;
	string userN;
	string passW;

	switch (rMsg) {

		PAINTSTRUCT r;
		HDC regMessage;
		RECT rm;
		
	case WM_CREATE: {

		font = CreateFont(
			20,
			0,
			0,
			0,
			FW_NORMAL,
			FALSE,
			FALSE,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			TEXT("Helvetica"));


		HINSTANCE inst3 = ((LPCREATESTRUCT)rParamL)->hInstance;
		firstName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 40, 200, 24, rwnd, 0, inst3, 0);
		lastName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 70, 200, 24, rwnd, 0, inst3, 0);
		address = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 100, 200, 24, rwnd, 0, inst3, 0);
		userName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 130, 200, 24, rwnd, 0, inst3, 0);
		password = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_PASSWORD, 88, 160, 200, 24, rwnd, 0, inst3, 0);
		reg =CreateWindowEx(0, L"button", L"Register", WS_CHILD | WS_VISIBLE, 88, 200, 100, 40, rwnd, (HMENU)TRUEREG, inst3, 0);
		regb = CreateWindowEx(0, L"button", L"Back", WS_CHILD | WS_VISIBLE, 190, 200, 100, 40, rwnd, (HMENU)BACK, inst3, 0);
		wchar_t first[] = L"Enter your first Name";
		wchar_t last[] = L"Enter your Last Name";
		wchar_t add[] = L"Enter your Address";
		wchar_t user[] = L"Choose a Username";
		wchar_t pass[] = L"Choose a Password";

		Edit_SetCueBannerText(firstName, first);
		Edit_SetCueBannerText(lastName, last);
		Edit_SetCueBannerText(address, add);
		Edit_SetCueBannerText(userName, user);
		Edit_SetCueBannerText(password, pass);

		SendMessage(firstName, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(lastName, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(address, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(userName, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(password, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(reg, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(regb, WM_SETFONT, (WPARAM)font, TRUE);
		
	}

	case WM_COMMAND:

		sqlite3* db;
		int getDb;
		sqlite3_stmt* n;
		/*
		* think, squarepants, think!
		*/
		getDb = sqlite3_open("registered", &db);

		if (LOWORD(rParam) == BACK) {
			DestroyWindow(rwnd);
			showLoginWindow();
			break;
		}
		else if (LOWORD(rParam) == TRUEREG) {

			wchar_t fName[300];
			wchar_t lName[300];
			wchar_t add[300];
			wchar_t uName[300];
			wchar_t tText[300];
			wchar_t pWord[300];

			const char* regTable = "CREATE TABLE registered(firstName varchar(255), lastName varchar(255), address varchar(255), username varchar(255) UNIQUE, password varchar(255));";
			getDb = sqlite3_exec(db, regTable, 0, 0, 0);

			const char* sqlStatement = "INSERT INTO registered(firstName, lastName, address, username, password) VALUES (?, ?, ?, ?, ?);";

			if ((GetWindowText(firstName, fName, 300) != NULL) && (GetWindowText(lastName, lName, 300) != NULL) && (GetWindowText(address, add, 300) != NULL) && (GetWindowText(userName, uName, 300) != NULL) && (GetWindowText(password, pWord, 300) != NULL)) {
				GetWindowText(firstName, fName, 300);
				GetWindowText(lastName, lName, 300);
				GetWindowText(address, add, 300);
				GetWindowText(userName, uName, 300);
				GetWindowText(password, pWord, 300);
			}
			else {
				return 0;
			}

			wstring firstN3 = fName;
			string firstN2(firstN3.begin(), firstN3.end());
			firstN = firstN2;

			wstring lastN3 = lName;
			string lastN2(lastN3.begin(), lastN3.end());
			lastN = lastN2;

			wstring addr3 = add;
			string addr2(addr3.begin(), addr3.end());
			addr = addr2;

			wstring userN3 = uName;
			string userN2(userN3.begin(), userN3.end());
			userN = userN2;

			wstring passW3 = pWord;
			string passW2(passW3.begin(), passW3.end());
			passW = passW2;


			getDb = sqlite3_prepare_v2(db, sqlStatement, -1, &n, 0);

			sqlite3_bind_text(n, 1, firstN.c_str(), firstN.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 2, lastN.c_str(), lastN.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 3, addr.c_str(), addr.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 4, userN.c_str(), userN.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 5, passW.c_str(), passW.length(), SQLITE_STATIC);

			getDb = sqlite3_step(n);


			sqlite3_finalize(n);
		}


		/*
		* WM_PAINT must come after
		* WM_COMMAND to prevent unintended
		* conseqeunces
		*/

	case WM_PAINT:
		regMessage = BeginPaint(rwnd, &r);
		SetTextColor(regMessage, RGB(0, 0, 0));
		SetBkMode(regMessage, TRANSPARENT);
		GetClientRect(rwnd, &rm);
		DrawText(regMessage, L"Enter Registration Details Below", -1, &rm, DT_CENTER | DT_WORDBREAK);
		EndPaint(rwnd, &r);
		break;


	case WM_CLOSE:
		DestroyWindow(rwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(rwnd, rMsg, rParam, rParamL);


}




