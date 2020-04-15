#pragma once

#include "Customer.h"
#include "UserSession.h"

using namespace std;

class CustomerSession : public Session {

private:

	//data members
	Customer customer;

public:
	CustomerSession() {}
	bool Login();
	void addCustomer(Customer);
	bool checkCustomer(Customer);
	void putIntoFile(Customer);
	void changePasswd(string);
	list<Customer> getlist();
	void displayMenu();
	~CustomerSession() {
	}

};
