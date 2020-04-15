#pragma once

#include <string>
using namespace std;


//Error class
class Error {

private:

	string errmsg;
	int errcode;

public:

	Error() {}
	Error(string inerrmsg, int inerrcode) :errmsg(inerrmsg), errcode(inerrcode) {}
	void display();

};