#pragma once

#include <string>
#include "Customer.h"
#include "UserSession.h"
#include "Product.h"
#include "Employee.h"

class EmployeeSession : public Session {

public:
	EmployeeSession() {}
	bool Login();
	list<Employee> getEmplist();
	Employee& setVal(Employee&);
	bool checkEmployee(Employee);
	void displayMenu();
	int updateStock(Product , int);
	int updateCardPoints(Customer&, int);

private:
	void changePasswd(string);
	bool billing();
	//void addOffers();
	void addDiscount();
	void addPointsToCard();
	void generateBill();
	void updateCart_File();
	void updateCardPoints_File();
	//void getCart();
	//date Members
	Employee employee;
	Customer customer;

};