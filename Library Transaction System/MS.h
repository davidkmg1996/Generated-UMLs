#ifndef MS_H
#define MS_H
#include <iostream>
#include <string>
#include <vector>
#include "Member.h"
#include "Book.h"
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
		aMember->getName() = name;
		aMember->getAddress() = address;
		memberId = aMember->getMemberId();
		members.push_back(*aMember);
		const wstring m = aMember->getMemberInfo();
		const wstring n = L"Member Registered\n\n";

		return  n;
	}

	string toString(string h){


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
