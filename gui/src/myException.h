#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class InputException :public exception {
private:
	string msg;
public:
	InputException(string e) {
		msg = e;
	}
	const char* what() const throw() {
		cout << msg << endl;
		return msg.data();
	}
	string getMsg() const {
		return msg;
	}
};

class NumberException :public InputException {
public:
	NumberException() :
		InputException("N is out of range!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class OutOfRangeException :public InputException {
public:
	OutOfRangeException(int i, string str) :
		InputException("Line " + to_string(i) + ": \"" + str + "\"\nThe parameter(s) is(are) out of range!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class CoincideException :public InputException {
public:
	CoincideException(int i, string str) :
		InputException("Line " + to_string(i) + ": \"" + str + "\"\nThe two points coincide!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class CoverException :public InputException {
public:
	CoverException(int i, string str) :
		InputException("Line " + to_string(i) + ": \"" + str + "\"\nOverlap with added drawings!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class NumOfObjException :public InputException {
public:
	NumOfObjException() :
		InputException("The number of geometric objects is not equal to N!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class FormatException :public InputException {
public:
	FormatException(int i, string str) :
		InputException("Line " + to_string(i) + ": \"" + str + "\"\nThe format of input is illgal!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class LessThanZeroException :public InputException {
public:
	LessThanZeroException(int i, string str) :
		InputException("Line " + to_string(i) + ": \"" + str + "\"\nRadius of circle must be greater than zero!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class EmptyFileException :public InputException {
public:
	EmptyFileException() :
		InputException("The input file is empty!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};

class NoNException :public InputException {
public:
	NoNException() :
		InputException("The first line of input file is not a number!\n") {};
	const char* what() const throw() {
		cout << getMsg() << endl;
		return getMsg().data();
	}
};
