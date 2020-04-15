#pragma once

#include <string>
using namespace std;

//Abstract Session class
class Session {

public:
	Session() {}
	virtual bool Login() = 0;
	virtual void displayMenu() = 0;
};


class SessionFactory {

public:
	SessionFactory() {}
	static Session* createSession(string);

};