
#include <iostream>
#include <vector>
#include <algorithm>
#include "MS.h"
#include "Book.h"
#include "Member.h"
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


int main() {


	vector<Book> bVector;

	Book b1 = Book("A Farewell to Arms", "Ernest Hemingway", "1451658168", true);

	Member m1("David", "Sesame Street", 999, bVector);

	m1.getMemberInfo();
	



	return 0;
}