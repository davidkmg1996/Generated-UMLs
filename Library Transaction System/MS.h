#ifndef MS_H
#define MS_H
#include <iostream>
#include <string>
#include <vector>
#include "Member.h"
#include "Book.h"
#include "tchar.h"
#include "Transaction.h"


using namespace std;

class Library{

	friend class Book;

	/*
	* TAKE ME INTO LOVING ARMS
	* KISS ME UNDER THE LIGHT OF
	* A THOUSAND STARS
	*/

public:


	Library() : memberId{ 0 }, name{ name }, address{ address }, books { books }, members{ members } {


	}

	void addBook(Book aBook) {

		books.push_back(aBook);
	}


	void removeBook(Book rBook) {
		books.erase(remove(books.begin(), books.end(), rBook));

	}

	const wstring RegisterMember(Member *aMember) {
		members.push_back(*aMember);
		wstring info = L"Member Registered!\n\n";
		info += L"Member Name: " + aMember->getName() + L"\n";
		info += L"Member Address: " + aMember->getAddress() + *L"\n";
		info += L"Member ID: " + to_wstring(aMember->getMemberId()) + *L"\n";
		const wchar_t* n = L"Member Registered\r\n\n";
		static wchar_t BUFFER[1000];

		wstring result = info;
		
		//wcsncat_s(BUFFER, sizeof(BUFFER) / sizeof(wchar_t), aMember->getName().c_str(), _TRUNCATE);

		 
		return result;
	}

	

	void returnBook(Member m1, Book rBook) {


		string title = rBook.getTitle();
		
		removeBook(rBook);
	
		cout << title << " Returned!\n\nCurrent titles checked out : " << endl;
		rBook.setAvailability(true);
		if (m1.borrowedBooks.size() > 0) {
			for (auto e : m1.borrowedBooks) {
				cout << e.getTitle() << endl;
			}

		}

		if (m1.borrowedBooks.size() == 0) {
			cout << "No books currently checked out.";
		}
	}


private:
	wstring name;
	wstring address;
	vector<Book> books;
	int memberId;
	vector<Member> members;
	Member m;

		

};

#endif
