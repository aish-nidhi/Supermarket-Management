#pragma once
#include <string>
#include <fstream>

using namespace std;

class Employee {

private:
	string Id;
	string employeeName;
	string password;
	string phnNo;
	string address;

public:
	Employee() {}
	Employee(string inId, string inEmployeeName, string inEmployeePasswd) : Id(inId), employeeName(inEmployeeName), password(inEmployeePasswd) {}
	string getId();
	string getEmployeeContact();
	string getEmployeeAddress();
	string getEmployeeName();
	string getPassword();
	bool setEmployeeName(string inName);
	bool setEmployeeContact(string num);
	bool setEmployeeAddress(string);
	bool setEmployeeId(string);
	void setPassword(string);
	Employee& setListValue(Employee&, string, int);
	friend ostream& operator<<(ostream&, Employee&);
	friend ofstream& operator<<(ofstream&, Employee&);
	friend ifstream& operator>>(ifstream&, Employee&);
	bool operator==(const Employee);
	string getType()
	{
		return "Employee";
	}
};