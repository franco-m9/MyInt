/* Franco Marcoccia
COP3330 Section 6
Assignment 5
This is a class file which contains member data and functions and other data necessary for storing any non-negative integer program.
*/

#include <iostream>
using namespace std;
class MyInt																								// includes Bob's starter file
{
	friend MyInt operator+ (const MyInt& x, const MyInt& y);
	friend MyInt operator* (const MyInt& x, const MyInt& y);
	friend bool operator< (const MyInt& x, const MyInt& y);
	friend bool operator> (const MyInt& x, const MyInt& y);
	friend bool operator<= (const MyInt& x, const MyInt& y);
	friend bool operator>= (const MyInt& x, const MyInt& y);
	friend bool operator== (const MyInt& x, const MyInt& y);
	friend bool operator!= (const MyInt& x, const MyInt& y);
	friend ostream& operator<< (ostream& a, const MyInt& b);
	friend istream& operator>> (istream& a, MyInt& b);



public:
	MyInt(int n = 0);		// first constructor
	MyInt(char*num);		// second constructor
	~MyInt();				// destructor
	MyInt(const MyInt&d);	// copy constructor
	MyInt&operator=(const MyInt&d);
	MyInt& operator++();	// pre-increment
	MyInt operator++(int);	// post-increment

private:
	int maxsize;
	int currentsize=0;
	char*numbers;

};
