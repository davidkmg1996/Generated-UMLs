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

	friend class Transaction;
	friend class Member;
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

	void RegisterMember(Member *aMember) {
		aMember->getName() = name;
		aMember->getAddress() = address;
		memberId = aMember->getMemberId();
		members.push_back(*aMember);

		
		cout << "Member registered!\n" << endl;
		aMember->getMemberInfo();
	}

	void returnBook(Book rBook) {

		removeBook(rBook);
		cout << "Book Returned! Current titles checked out: " << endl;

		
		if (books.size() >= 1) {
			for (auto e : books) {
				cout << e.getTitle() << endl;
			}
		} else if (books.size() == 0) {
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
