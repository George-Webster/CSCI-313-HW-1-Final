#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <time.h>
#include <stdlib.h>
using namespace std;  
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

template <typename Func>
long long TimeFunc(Func f)
{
	auto begin = steady_clock::now();
	f();
	auto end = steady_clock::now();

	return duration_cast<milliseconds>(end - begin).count();
}
//Part a: Filling them with random numbers
//Create a function that takes in a vector and a variable called size, then fills it with random numbers.
void VectorOfRandomNumbers(int size, vector<int> v) {
	for (int i = 0; i < size; i++) {
		v.push_back(rand());
	}
	
}

//Create a function that takes in a list and a variable called size, then fills it with random numbers.
void ListOfRandomNumbers(int size, list<int> l) {
	for (int i = 0; i < size; i++) {
		l.push_back(rand());
	}
}

//Part b: Filling them with random strings

//create a function to get random strings
string getRandomString(int length) {
	int flag;
	char* ch = new char[length] ;
	for (int i = 0; i < length - 1; i++) {
		flag = rand() % 3;
		switch (flag)
		{
			case 0:
				ch[i] = rand() % 26 + 'A';
				break;

			case 1:
				ch[i] = rand() % 26 + 'a';
				break;

		default:
			ch[i] = rand() % 10 + '0';
			break;
		}
	}
	ch[length - 1] = '\0';
	string str = ch;
	return str;
}

//Create a function that takes in a vector and a variable called size, then fills it with random strings.
void VectorOfRandomStrings(int size, vector<string> v) {
	for (int i = 0; i < size; i++) {
		int length = rand() % 50 + 1;
		string str = getRandomString(length);
		v.push_back(str);

	}
}
//Create a function that takes in a list and a variable called size, then fills it with random strings.
void ListOfRandomString(int size, list<string> l) {
	for (int i = 0; i < size; i++) {
		int length = rand() % 50 + 1;
		string str = getRandomString(length);
		l.push_back(str);
	}
}


//Part c: Doing the above with move semantics when filling with random strings
//Create a function that takes in a vector and a variable called size, then fills it with random strings(use move semantics).
void VectorOfRandomStrings_Move(int size, vector<string> v) {
	for (int i = 0; i < size; i++) {
		int length = rand() % 50 + 1;
		string str = getRandomString(length);
		v.push_back(move(str));

	}
}
//Create a function that takes in a list and a variable called size, then fills it with random strings(use move semantics).
void ListOfRandomString_Move(int size, list<string> l) {
	for (int i = 0; i < size; i++) {
		int length = rand() % 50 + 1;
		string str = getRandomString(length);
		l.push_back(move(str));
	}
}


int main()
{
	srand(time(nullptr));

	int const size = 10000;

	//part a
	cout << "Question1-Part-a:" << endl;
	vector <int> v1;
	list <int> l1;
	auto vectormilliseconds_int = TimeFunc([&]() {VectorOfRandomNumbers(size, v1); });
	auto listmilliseconds_int = TimeFunc([&]() {ListOfRandomNumbers(size, l1); });
	cout << "Filling a vector with 10,000 random numbers spend " << vectormilliseconds_int << " milliseconds\n";
	cout << "Filling a list with 10,000 random numbers spend   " << listmilliseconds_int << " milliseconds\n";
	if (vectormilliseconds_int < listmilliseconds_int) {
		cout << "Filling vector with random numbers is faster than list.\n";
	}
	else {
		cout << "Filling list with random numbers is faster than vector.\n";
	}
	
	cout << endl << endl;


	//part b
	cout << "Question1-Part-b:" << endl;
	vector <string> v2;
	list <string> l2;
	auto vectormilliseconds_string = TimeFunc([&]() {VectorOfRandomStrings(size, v2); });
	auto listmilliseconds_string = TimeFunc([&]() {ListOfRandomString(size, l2); });
	cout << "Filling a vector with 10,000 random strings spend " << vectormilliseconds_string << " milliseconds\n";
	cout << "Filling a list with 10,000 random strings spend   " << listmilliseconds_string << " milliseconds\n";
	if (vectormilliseconds_string < listmilliseconds_string) {
		cout << "Filling vector with random strings is faster than list.\n";
	}
	else {
		cout << "Filling list with random strings is faster than vector.\n";
	}
	cout << endl << endl;



	//part c
	cout << "Question1-Part-c:" << endl;
	vector <string> v3;
	list <string> l3;
	auto vectormilliseconds_string_move = TimeFunc([&]() {VectorOfRandomStrings_Move(size, v2); });
	auto listmilliseconds_string_move = TimeFunc([&]() {ListOfRandomString_Move(size, l2); });
	cout << "Filling a vector with 10,000 random strings use move semantics spend " << vectormilliseconds_string_move << " milliseconds\n";
	cout << "Filling a list with 10,000 random strings use move semantics spend   " << listmilliseconds_string_move << " milliseconds\n";
	if (vectormilliseconds_string_move < listmilliseconds_string_move) {
		cout << "Filling vector with random strings use move semantics is faster than list.\n";
	}
	else {
		cout << "Filling list with random strings use move semantics is faster than vector.\n";
	}
}