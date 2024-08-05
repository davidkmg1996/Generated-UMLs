#ifndef MEMBER_H
#define MEMBER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Member {

public:

	Member(string name, string address, int memberId, vector<Book> borrowedBooks) : name{ name }, 
		address{ address }, borrowedBooks{ borrowedBooks } {

		this->memberId = generateId();
		memberId = this->memberId;
	
	}

	Member() {

	}

	void getMemberInfo() {

		cout << "Member Name: " << name << "\n";
		cout << "Member Address: " << address << "\n";
		cout << "Member Id: " << memberId << endl;
	}

	string getName() const {
		return name;
	}

	int getMemberId() const {
		return memberId;
	}

	string getAddress() const {
		return address;
	}

	void borrowBook(Book aBook) {
		borrowedBooks.push_back(aBook);
		aBook.setAvailability(false);
	}

	void returnBook(Book rBook) {
		borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), rBook));
		rBook.setAvailability(true);
	}

	void getBorrowedBooks() {

		for (int i = 0; i < borrowedBooks.size(); i++) {
			cout << borrowedBooks.at(i).getTitle();
		}
	}

	int generateId(){

		srand(time(NULL));
		int id = rand();
		return id;

	}

	/*
	* Overloaded equality operator needed to prevent compile-time
	* binary equality error
	*/
	bool operator==(const Member& other) const {
		return (name == other.name) && (memberId == other.memberId) && (borrowedBooks == other.borrowedBooks);
	}

private:
	/*
	* Cannot use unary address of operator and const explicitly
	* deletes function, causes compile-time error
	*/
	string name;
	string address;
	int memberId;
	vector<Book> borrowedBooks;

};

#endif