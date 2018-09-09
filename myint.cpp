/* Franco Marcoccia
COP3330 Section 6
Assignment 5
This is a cpp file which contains function definitions from the header file, in which the purpose is to store large numbers that are beyond int storage using dynamic arrays.
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
#include "myint.h"

using namespace std;

int C2I(char c)													
// function given by Bob Myers and used in the program
// converts character into integer (returns -1 for error)
{
	if (c < '0' || c > '9')	return -1;	// error
	return (c - '0');				// success
}

char I2C(int x)												
// function given by Bob Myers and used in the program
// converts single digit integer into character (returns '\0' for error)
{
	if (x < 0 || x > 9)		return '\0';	// error
	return (static_cast<char>(x) + '0'); 	// success
}

MyInt::MyInt(int n)
// default/constructor which takes in int values and stores into a dynamic array
{

	if (n <= 0)	
		// error checking + storage into the array, with the max capacity being 5 more than the current stored size
	{
		currentsize = 1;
		maxsize = 6;
		numbers = new char[maxsize];
		numbers[0] = I2C(0);
	}
	else
	{
		int temp = n;
		while (temp > 0)	
		// while loop which checks how many digits in the number entered
		{
			temp = temp / 10;
			currentsize++;
		}

		maxsize = currentsize + 5;
		numbers = new char[maxsize];

		int digit;
		int divisor = pow(10, currentsize - 1);

		for (int i = 0; i < currentsize; i++)
			// for loop to extract digits one at a time using the base powers of 10
		{
			digit = n / divisor;
			numbers[i] = I2C(digit);
			n = n % divisor;
			divisor = divisor / 10;
		}

	}

}
MyInt::MyInt(char*num)				// second constructor which takes in a c-style string
{
	int length = strlen(num);				// uses strlen to find out the size/length of string parameter
	maxsize = length + 5;
	currentsize = length;
	numbers = new char[maxsize];
	for (int i = 0; i < length; i++)		// error checking if string isn't stricly values 0-9
	{
		if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' && num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
		{
			maxsize = 6;
			currentsize = 1;
			numbers = new char[maxsize];
			numbers[0] = I2C(0);
			break;
		}
		else
			numbers[i] = num[i];
	}
}

MyInt::~MyInt()						// destructor
{
	delete[] numbers;
	numbers = 0;
}

MyInt::MyInt(const MyInt&d)			// copy constructor as a copy of d 
{
	maxsize = d.maxsize;
	currentsize = d.currentsize;
	numbers = new char[d.maxsize];

	for (int i = 0; i < currentsize; i++)
		numbers[i] = d.numbers[i];
}

MyInt&MyInt::operator=(const MyInt&d)	// assignment operator of d
{
	if (this != &d)
	{
		delete[] numbers;
		maxsize = d.maxsize;
		currentsize = d.currentsize;
		numbers = new char[d.maxsize];

		for (int i = 0; i < currentsize; i++)
			numbers[i] = d.numbers[i];
	}
	return *this;
}

ostream& operator<< (ostream& a, const MyInt& b)	// overload of insertion operator to display (cout) the number stored in array
{
	for (int i = 0; i < b.currentsize; i++)
		a << C2I(b.numbers[i]);

	return a;
}

istream& operator>> (istream& a, MyInt& b)	// extraction operator which ignores whitespace and reads up to digits only
{
	char*num1;
	char*num2;
	int s = 0;

	delete[] b.numbers;

	b.currentsize = 0;
	num1 = new char[1];
	
	while (isspace(a.peek()))
	{
		a.ignore();
	}
	char check = a.get();
	while (isdigit(check))
	{
		num1[s++] = (check);
		num2 = new char[s + 1];
		for (int i = 0; i < s; i++)
			num2[i] = num1[i];
		delete[] num1;
		num1 = num2;
		check = a.get();
	}
	b.currentsize = s;
	b.numbers = num1;

		return a;
}

bool operator< (const MyInt& x, const MyInt& y)		// compares two MyInt objects and sets up availability for other overloaded comparison operators
{
	if (x.currentsize == y.currentsize)
	{
		if (C2I(x.numbers[0]) < C2I(y.numbers[0]))
			return true;
		else if (C2I(x.numbers[0]) > C2I(y.numbers[0]))
			return false;
		else
		{
			for (int i = 0; i < x.currentsize; i++)
			{
				if (C2I(x.numbers[i]) < C2I(y.numbers[i]))
				{
					return true;
					break;
				}
				else if (C2I(x.numbers[i]) > C2I(y.numbers[i]))
				{
					return false;
					break;
				}
				else if (i == x.currentsize - 1)
				{
					if (C2I(x.numbers[x.currentsize - 1]) == C2I(y.numbers[y.currentsize - 1]))
						return false;
				}
			}
		}
	}
	else if (x.currentsize < y.currentsize)
		return true;
	else if (x.currentsize > y.currentsize)
		return false;
}

bool operator> (const MyInt& x, const MyInt& y)
{
	return(y < x);
}

bool operator<= (const MyInt& x, const MyInt& y)
{
	return (x < y || x == y);
}

bool operator>= (const MyInt& x, const MyInt& y)
{
	return (y < x || x == y);
}

bool operator== (const MyInt& x, const MyInt& y)
{
	if (x.currentsize != y.currentsize)
		return false;

	else if (x.currentsize == y.currentsize)
	{
		for (int i = 0; i < x.currentsize; i++)
		{
			if (C2I(x.numbers[i]) != C2I(y.numbers[i]))
				return false;
		}
	}
	else
		return true;
}

bool operator!= (const MyInt& x, const MyInt& y)
{
	return !(x == y);
}

MyInt operator+ (const MyInt& x, const MyInt& y)	// addition operator overload
{
	int remainder=0;
	int biggestsize, additiontotal;
	MyInt d;

	char tempi1, tempi2, tempd;
	char*temp1 = new char[x.maxsize];
	char*temp2 = new char[y.maxsize];

	for (int i = 0; i < x.currentsize; i++)	
		// creates new dynamic array to reverse contens of array for easier operation
		temp1[i] = x.numbers[i];
	if (x.currentsize % 2 == 0)
	{
		for (int i = 0; i < x.currentsize / 2; i++)
		{
			tempi1 = temp1[x.currentsize - 1 - i];
			temp1[x.currentsize - 1 - i] = temp1[i];
			temp1[i] = tempi1;
		}
	}
	else
	{
		for (int i = 0; i < (x.currentsize - 1) / 2; i++)
		{
			tempi1 = temp1[x.currentsize - 1 - i];
			temp1[x.currentsize - 1 - i] = temp1[i];
			temp1[i] = tempi1;
		}
	}

	for (int i = 0; i < y.currentsize; i++)	
		// creates new dynamic array to reverse contens of array for easier operation
		temp2[i] = y.numbers[i];
	if (y.currentsize % 2 == 0)
	{
		for (int i = 0; i < y.currentsize / 2; i++)
		{
			tempi2 = temp2[y.currentsize - 1 - i];
			temp2[y.currentsize - 1 - i] = temp2[i];
			temp2[i] = tempi2;
		}
	}
	else
	{
		for (int i = 0; i < (y.currentsize - 1) / 2; i++)
		{
			tempi2 = temp2[y.currentsize - 1 - i];
			temp2[y.currentsize - 1 - i] = temp2[i];
			temp2[i] = tempi2;
		}
	}
	
	if (x.currentsize > y.currentsize)
		biggestsize = x.currentsize;
	else if (x.currentsize < y.currentsize)
		biggestsize = y.currentsize;
	else if (x.currentsize == y.currentsize)
		biggestsize = x.currentsize;
	
	delete[]d.numbers;

	int inc = biggestsize + 1;
	char*array = new char[biggestsize];
	int add1, add2;
			for (int i=0; i<biggestsize; i++)
			{
				if (i >= x.currentsize)
					add1 = 0;
				else
					add1 = C2I(temp1[i]);
				if (i >= y.currentsize)
					add2 = 0;
				else
					add2 = C2I(temp2[i]);

				
						additiontotal = add1+add2+remainder;
						remainder = additiontotal / 10;
						additiontotal = additiontotal % 10;
						array[i] = I2C(additiontotal);

						if (i + 1 == biggestsize && remainder != 0)
						{
							char*temp = new char[inc];
							for (int j = 0; j < biggestsize; j++)
								temp[j] = array[j];
							temp[inc-1] = I2C(remainder);
							delete[]array;
							array = temp;
							d.numbers = array;
							d.currentsize = inc;
							d.maxsize = inc + 5;
						}
						else if (i + 1 == biggestsize && remainder == 0)
						{
							d.numbers = array;
							d.currentsize = biggestsize;
							d.maxsize = biggestsize + 5;
						}
						
			}
			
		if (d.currentsize % 2 == 0)
		{
			for (int i = 0; i < (d.currentsize / 2); i++)
				// reverse back to original for display
			{
				tempd = d.numbers[d.currentsize - 1 - i];
				d.numbers[d.currentsize - 1 - i] = d.numbers[i];
				d.numbers[i] = tempd;
			}
		}
		else
		{
			for (int i = 0; i < (d.currentsize - 1) / 2; i++)
			{
				tempd = d.numbers[d.currentsize - 1 - i];
				d.numbers[d.currentsize - 1 - i] = d.numbers[i];
				d.numbers[i] = tempd;
			}
		}
		delete[] temp1;
		delete[] temp2;
		temp1 = 0;
		temp2 = 0;
		
		return d;
}

MyInt operator* (const MyInt& x, const MyInt& y) // multiplication operator overload
{
	int remainder = 0;
	int biggestsize, additiontotal;
	MyInt f;

	char tempi1, tempi2, tempd;
	char*temp1 = new char[x.maxsize];
	char*temp2 = new char[y.maxsize];

	for (int i = 0; i < x.currentsize; i++)		// creates new dynamic array to reverse contens of array for easier operation
		temp1[i] = x.numbers[i];
	if (x.currentsize % 2 == 0)
	{
		for (int i = 0; i < x.currentsize / 2; i++)
		{
			tempi1 = temp1[x.currentsize - 1 - i];
			temp1[x.currentsize - 1 - i] = temp1[i];
			temp1[i] = tempi1;
		}
	}
	else
	{
		for (int i = 0; i < (x.currentsize - 1) / 2; i++)
		{
			tempi1 = temp1[x.currentsize - 1 - i];
			temp1[x.currentsize - 1 - i] = temp1[i];
			temp1[i] = tempi1;
		}
	}

	for (int i = 0; i < y.currentsize; i++)	
		// creates new dynamic array to reverse contens of array for easier operation
		temp2[i] = y.numbers[i];
	if (y.currentsize % 2 == 0)
	{
		for (int i = 0; i < y.currentsize / 2; i++)
		{
			tempi2 = temp2[y.currentsize - 1 - i];
			temp2[y.currentsize - 1 - i] = temp2[i];
			temp2[i] = tempi2;
		}
	}
	else
	{
		for (int i = 0; i < (y.currentsize - 1) / 2; i++)
		{
			tempi2 = temp2[y.currentsize - 1 - i];
			temp2[y.currentsize - 1 - i] = temp2[i];
			temp2[i] = tempi2;
		}
	}

	if (x.currentsize > y.currentsize)
		biggestsize = x.currentsize;
	else if (x.currentsize < y.currentsize)
		biggestsize = y.currentsize;
	else if (x.currentsize == y.currentsize)
		biggestsize = x.currentsize;

	delete[]f.numbers;

	int inc = (biggestsize*2)+1;
	char*array = new char[biggestsize];
	int carry1, carry2;

	for (int i = 0; i < biggestsize; i++)
	{

		if (i >= x.currentsize)
			carry1 = 1;
		else
			carry1 = C2I(temp1[i]);
		if (i >= y.currentsize)
			carry2 = 1;
		else
			carry2 = C2I(temp2[i]);

		for (int j = 0; j < biggestsize; j++)
		{
			int multiplytotal = carry1 + carry2 + remainder;
			remainder = multiplytotal / 10;
			additiontotal = multiplytotal % 10;
			array[i] = I2C(multiplytotal);
		}

		if (i + 1 == biggestsize && remainder != 0)
		{
			char*temp = new char[inc];
			for (int j = 0; j < biggestsize; j++)
				temp[j] = array[j];
			temp[inc - 1] = I2C(remainder);
			delete[]array;
			array = temp;
			f.numbers = array;
			f.currentsize = inc;
			f.maxsize = inc + 5;
		}
		else if (i + 1 == biggestsize && remainder == 0)
		{
			f.numbers = array;
			f.currentsize = biggestsize;
			f.maxsize = biggestsize + 5;
		}

	}

	if (f.currentsize % 2 == 0)
	{
		for (int i = 0; i < (f.currentsize / 2); i++)	
			// reverse back to original for display
		{
			tempd = f.numbers[f.currentsize - 1 - i];
			f.numbers[f.currentsize - 1 - i] = f.numbers[i];
			f.numbers[i] = tempd;
		}
	}
	else
	{
		for (int i = 0; i < (f.currentsize - 1) / 2; i++)
		{
			tempd = f.numbers[f.currentsize - 1 - i];
			f.numbers[f.currentsize - 1 - i] = f.numbers[i];
			f.numbers[i] = tempd;
		}
	}
	delete[] temp1;
	delete[] temp2;
	temp1 = 0;
	temp2 = 0;

	return f;
}

MyInt&MyInt::operator++() 
// pre-increment overload assuming +operator works , should theoretically work
{
	*this = *this + 1;
	return *this;
}

MyInt MyInt::operator++(int)
// post-increment overload assuming +operator works
{
	MyInt temp = *this;
	numbers = numbers + 1;
	return temp;
}