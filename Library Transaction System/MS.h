#ifndef MS_H
#define MS_H
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Member.h"

using namespace std;

class Library {

	/*
	* TAKE ME INTO LOVING ARMS
	* KISS ME UNDER THE LIGHT OF
	* A THOUSAND STARS
	*/

public:

	Library(Member m, string name, string address) : memberId{ 0 }, name{ name }, address{ address }, books { books }, members{ members } {

		this->m = m;

	}

	void addBook(Book *aBook) {
		books.push_back(*aBook);
	}

	void removeBook(Book *rBook) {
		books.erase(remove(books.begin(), books.end(), *rBook));
	}

	void RegisterMember(Member *aMember) {
		aMember->getName() = name;
		aMember->getAddress() = address;
		memberId = aMember->getMemberId();
		members.push_back(*aMember);


		cout << "Member registered!" << endl;
		aMember->getMemberInfo();
	}

	void issueBook(Member iMember, Book mBook) {
		//iMember, do you member?
		members.push_back(iMember);
		books.erase(remove(books.begin(), books.end(), mBook));

	}
	void returnBook(Book rBook) {
		books.erase(remove(books.begin(), books.end(), rBook));
	}


private:
	string name;
	string address;
	Member m;
	vector<Book> books;
	int memberId;
	vector<Member> members;

};

#endif
