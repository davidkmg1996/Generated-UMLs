#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Book.h"
#include "Member.h"

using namespace std;

class Transaction {

	friend class Book;

public:
	/*
	* The getMember() function is dedicated
	* to all of my ex girlfriends . . .
	*/

	Transaction(string date, string type, Member member, Book book, int transactionId) : date{ date }, type{ type }, member{ member }, book{ book }, transactionId{ transactionId } {

	}
	
	
	Member getMember() const {

		return member;
	}
	
	
	/*
	* . . . the getBook() function, however,
	* is not
	*/
	Book getBook() const {
		return book;
	}
	/*
	* Another S/O
	*/
	string getDate() const {
		return date;
	}

	string getType() const {
		/*
		* Not to be confused with the return type of
		* this function, which is, of course,
		* std::retarded
		*/
		return this->type;
	}

	/*
	* I could probably keep going but I'm tired
	* and it's not funny anymore
	*/
	int getTransactionId() const {
		return transactionId;
	}

	int setTransactionId() {


	}

private:
	int transactionId;
	Member member;
	Book book;
	string date;
	string type;

};
#endif
