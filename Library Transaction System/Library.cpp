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


int main(_TCHAR* argv[]) {

	SetConsoleTitle(_T("Library Transaction System"));
	vector<Book> bVector;

	Library lib;

	Book b1 = Book("A Farewell to Arms", "Ernest Hemingway", "1451658168", true, "Fiction");
	Book b2 = Book("Lord of The Flies", "William Golding", "0399501487", true, "Fiction");
	lib.addBook(b1);
	lib.addBook(b2);

	Member* m1;

	m1 = new Member("David", "Sesame Street", 999, bVector);

	lib.RegisterMember(m1);

	m1->borrowBook(b1);
	cout << b1.isAvailable();
	m1->borrowBook(b2);
	m1->returnBook(b1);

	string h;
	/*
	* Once program ends window title defaults
	* to debug, which is slightly annoying
	*/
	cin >> h;

	
	lib.returnBook(*m1, b1);
	



	return 0;
}

