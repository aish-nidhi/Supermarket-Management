#pragma once

#include<list>
#include "UserSession.h"
#include "Product.h"
#include "Admin.h"
#include "Employee.h"
//#include "COffers.h"

class AdminSession : public Session {

private:

	//data members
	Admin admin;
	Employee employee;
	Product product;
	//  Offers adminOffers;

		//private functions which are called in the public member function displayMenu();
		//two strings for the new password and confirm password



public:
	AdminSession() {}
	int convertStringToInt(string);
	string convertIntToString(int);
	void changePasswd(string);
	bool checkAdmin(Admin);
	void addAdmin(Admin);
	void removeAdmin(Admin);
	void addEmployee(Employee);
	list<Employee> getEmplist();
	bool checkEmployee(Employee);
	void removeEmployee(Employee);
	void addProduct(Product);
	bool checkProduct(Product);
	void removeProduct(Product);
	void addOffers(); //to do
	void updateOffers(); //to do
	//void updateStock(Product, unsigned);
	void displayLowStockProducts();
	bool Login();
	void displayMenu();
	list<Admin> getlist();
	list<Product> getProdlist();
	void putAdminInFile(Admin);
	void putEmpInFile(Employee);
	void putProdInFile(Product);
	Admin& setAdminValue(Admin&);
	Employee& setEmpValue(Employee&);
	Product& setProdValue(Product&);
	void updateStock(Product, int);
};