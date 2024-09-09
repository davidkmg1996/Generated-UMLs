#define NEW_BUTTON  2000
#define QUIT 1000
#define LOGIN 2250
#define	REGISTER 2500
#define TRUEREG 2750
#define BACK 3000
bool bEmpty;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL);
LRESULT CALLBACK login(HWND lwnd, UINT lMsg, WPARAM lParam, LPARAM lParamL);
LRESULT CALLBACK RegisterProc(HWND rwnd, UINT rMsg, WPARAM rParam, LPARAM rParamL);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	vector<Book> bVector;

	static wstring out;

	BS_PUSHBUTTON();

	Library lib;

	Book b1 = Book(L"A Farewell to Arms", L"Ernest Hemingway", L"1451658168", true, L"Fiction");
	Book b2 = Book(L"Lord of The Flies", L"William Golding", L"0399501487", true, L"Fiction");
	lib.addBook(b1);
	lib.addBook(b2);

	Member* m2;

	m2 = new Member(L"Victoria", L"Beverly Hills", 90210, bVector);

	static HWND textEdit;
	static HWND getAddress;

	switch (uMsg) {

	case WM_CREATE:
	{
		HINSTANCE inst = ((LPCREATESTRUCT)lParam)->hInstance;

		CreateWindowEx(0, L"button", L"Register Member", WS_CHILD | WS_VISIBLE, 300, 400, 175, 50, hwnd, (HMENU)NEW_BUTTON, inst, 0);
		textEdit = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 335, 250, 20, hwnd, 0, inst, 0);
		getAddress = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 370, 250, 20, hwnd, 0, inst, 0);
		wchar_t placeholder[] = L"Enter a member name";
		wchar_t pAddress[] = L"Please enter an address";
		Edit_SetCueBannerText(textEdit, placeholder);
		Edit_SetCueBannerText(getAddress, pAddress);

		HMENU menuBar = CreateMenu();
		HMENU fMenu = CreatePopupMenu();
		AppendMenu(fMenu, MF_STRING, 0, L"Open Catalog");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)fMenu, L"File");

		HMENU aMenu = CreatePopupMenu();
		AppendMenu(aMenu, MF_STRING, 0, L"About This Program");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)aMenu, L"About");


		HMENU oMenu = CreatePopupMenu();
		AppendMenu(oMenu, MF_STRING, QUIT, L"Quit");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)oMenu, L"Options");


		SetMenu(hwnd, menuBar);

		break;

	}

	case WM_COMMAND:
	{

		sqlite3* db;
		int getDb;

		getDb = sqlite3_open("users", &db);

		string name;
		string address;
		int sId;
		sqlite3_stmt* n;
		int errShow = SW_SHOWNORMAL;

		if (LOWORD(wParam) == NEW_BUTTON) {
			wchar_t tText[300];
			wchar_t tAddress[300];

			if (GetWindowText(textEdit, tText, 300) != NULL) {
				GetWindowText(textEdit, tText, 300);
			}
			else {
				return 0;
			}
			if (GetWindowText(getAddress, tAddress, 300) != NULL) {
				GetWindowText(getAddress, tAddress, 300);
			}
			else {
				return 0;
			}
			

			//Use null character

			for (int i = 0; tText[i] != '\0'; i++) {

				if (!iswalpha(tText[i])) {

				bEmpty = true;

				HINSTANCE nInst = GetModuleHandle(nullptr);
				wchar_t errorLib[50] = L"ERROR";

				WNDCLASS errorWindow = {};
				errorWindow.lpfnWndProc = nProc;
				errorWindow.hInstance = nInst;
				errorWindow.lpszClassName = errorLib;
				errorWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW);
				errorWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);

				RegisterClass(&errorWindow);

				HWND eMenu = CreateWindowEx(
					0,
					errorLib,
					L"Error",
					WS_OVERLAPPEDWINDOW,
					100, 100, 400, 100,
					nullptr,
					nullptr,
					nInst,
					nullptr

				);

				ShowWindow(eMenu, errShow);
				UpdateWindow(eMenu);
				break;

				}
				else {
					bEmpty = false;
					Member* m1 = new Member(tText, tAddress, 999, bVector);
					out = lib.RegisterMember(m1);

					ofstream nstream("users.txt", std::ios::app);

					wstring sName = m1->getName();
					string name2(sName.begin(), sName.end());
					name = name2;

					wstring sAddress = m1->getAddress();
					string address2(sAddress.begin(), sAddress.end());
					address = address2;


					sId = m1->getMemberId();
					
					string sInfoN(sName.begin(), sName.end());

					nstream << sInfoN << endl;
					nstream << sId << endl;


					InvalidateRect(hwnd, NULL, true);

				}

			}

			


			const char* createTable = "CREATE TABLE users(userName varchar(255), address varchar(255), memberId int, type varchar(255));";
			getDb = sqlite3_exec(db, createTable, 0, 0, 0);

			const char* sqlStatement = "INSERT INTO users(userName, address, memberId, type) VALUES (?, ?, ?, ?); ";

			getDb = sqlite3_prepare_v2(db, sqlStatement, -1, &n, 0);

			sqlite3_bind_text(n, 1, name.c_str(), name.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 2, address.c_str(), address.length(), SQLITE_STATIC);
			sqlite3_bind_int(n, 3, sId);
			sqlite3_bind_text(n, 4, "member", 10, SQLITE_STATIC);

			getDb = sqlite3_step(n);

			sqlite3_finalize(n);

		}

		if (LOWORD(wParam) == QUIT) {
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		break;
	}


	case WM_PAINT:

	{
		PAINTSTRUCT p;

			HDC hdc = BeginPaint(hwnd, &p);

			/*
			* TextOut(param1, param2, . . . , param5)
			* does not support carriage return
			*
			* and neither do I
			*/

			RECT r;

			GetClientRect(hwnd, &r);
			SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);

			if (bEmpty == false) {
				DrawText(hdc, out.c_str(), -1, &r, DT_WORDBREAK);
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


	case WM_PAINT:
		edc = BeginPaint(nwnd, &e);
		SetTextColor(edc, RGB(0, 0, 0));
		SetBkMode(edc, TRANSPARENT);
		GetClientRect(nwnd, &eR);
		DrawText(edc, L"Member Name must contain only alphabetic characters", -1, &eR, DT_WORDBREAK);
		EndPaint(nwnd, &e);
		break;

	case WM_CLOSE:
		DestroyWindow(nwnd);
		break;

	}

	return DefWindowProc(nwnd, eMsg, eParam, eParamL);

}

void showMainScreen() {

	wchar_t LIB_NAME[500] = L"Library";
	HINSTANCE hInstance = GetModuleHandle(nullptr);
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
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS winR = {};
	winR.lpfnWndProc = RegisterProc;
	winR.hInstance = hInstance;
	winR.lpszClassName = REG_NAME;
	//Prevent black bars/ghosting
	winR.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winR.hCursor = LoadCursor(nullptr, IDC_ARROW);

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
			DEFAULT_PITCH || FF_SWISS,
			TEXT("Helvetica"));

		InvalidateRect(lwnd, NULL, TRUE);

		static HWND userName;
		static HWND password;
		HINSTANCE inst2 = ((LPCREATESTRUCT)lParamL)->hInstance;
		userName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 40, 200, 20, lwnd, 0, inst2, 0);
		password = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 70, 200, 20, lwnd, 0, inst2, 0);
		CreateWindowEx(0, L"button", L"Login", WS_CHILD | WS_VISIBLE, 88, 100, 100, 40, lwnd, (HMENU)LOGIN, inst2, 0);
		CreateWindowEx(0, L"button", L"Register", WS_CHILD | WS_VISIBLE, 190, 100, 100, 40, lwnd, (HMENU)REGISTER, inst2, 0);
		wchar_t user[] = L"Username";
		wchar_t pass[] = L"Password";
		Edit_SetCueBannerText(userName, user);
		Edit_SetCueBannerText(password, pass);

		break;
	}

	case WM_COMMAND: {

		if (LOWORD(lParam) == LOGIN) {

			const char* openUsers = "SELECT users FROM registered;";
			//getDb = sqlite3_exec(db, openUsers, 0, 0, 0);

			DestroyWindow(lwnd);
			showMainScreen();
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

void showLoginWindow() {
	wchar_t LOG_NAME[500] = L"Login";
	HINSTANCE hInstance = GetModuleHandle(nullptr);
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

	ShowWindowAsync(lwnd, SW_SHOW);
	UpdateWindow(lwnd);



	//Use CreateMenu() for menuBar


	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}


}



LRESULT CALLBACK RegisterProc(HWND rwnd, UINT rMsg, WPARAM rParam, LPARAM rParamL) {

	

	static HWND firstName;
	static HWND lastName;
	static HWND address;
	static HWND userName;
	static HWND password;

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

		HINSTANCE inst3 = ((LPCREATESTRUCT)rParamL)->hInstance;
		firstName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 40, 200, 20, rwnd, 0, inst3, 0);
		lastName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 70, 200, 20, rwnd, 0, inst3, 0);
		address = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 100, 200, 20, rwnd, 0, inst3, 0);
		userName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 130, 200, 20, rwnd, 0, inst3, 0);
		password = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 160, 200, 20, rwnd, 0, inst3, 0);
		CreateWindowEx(0, L"button", L"Register", WS_CHILD | WS_VISIBLE, 88, 200, 100, 40, rwnd, (HMENU)TRUEREG, inst3, 0);
		CreateWindowEx(0, L"button", L"Back", WS_CHILD | WS_VISIBLE, 190, 200, 100, 40, rwnd, (HMENU)BACK, inst3, 0);
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


