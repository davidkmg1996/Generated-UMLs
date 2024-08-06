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

	void RegisterMember(Member *aMember) {
		aMember->getName() = name;
		aMember->getAddress() = address;
		memberId = aMember->getMemberId();
		members.push_back(*aMember);

		
		cout << "Member registered!\n" << endl;
		aMember->getMemberInfo();
	}

	void returnBook(Member m1, Book rBook) {


		string title = rBook.getTitle();
		
		removeBook(rBook);
	
		cout << title << " Returned!\n\nCurrent titles checked out : " << endl;
	
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
	string name;
	string address;
	vector<Book> books;
	int memberId;
	vector<Member> members;
	Member m;

		

};

#endif
