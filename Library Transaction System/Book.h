#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;


class Book {

public:

	friend class Transaction;

	Book(string title, string author, string isbn, bool available, string type) : title{ title }, author{ author }, isbn{ isbn }, available{ available }, type{ type } {}

	string getTitle() const {
		return title;
	}

	string getType() {
		return type;
	}

	string getAuthor() const {
		return author;
	}

	string getISBN() const {
		return isbn;
	}

	bool isAvailable() const {


		if (available == true) {
			return true;
		}

		return false;
	}

	bool setAvailability(bool tF) {

		if (tF = true) {
			available = true;
			return true;
		}
		available = false;
		return false;

	}
	/*
	* Overloaded equality operator needed to prevent compile - time
	  binary equality error
	*/
		
	bool operator==(const Book& other) const {
		return (title == other.title) && (author == other.author) && (isbn == other.isbn);
	}

private:
	string title;
	string author;
	string isbn;
	string type;
	bool available;

};

#endif