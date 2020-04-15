#include <string>
#include <fstream>
#include "Error.h"
#include "Employee.h"
#include "FileHelp.h"

//EMPLOYEE CLASS

string Employee::getId()
{
	return Id;
}

string Employee::getEmployeeName()
{
	return employeeName;
}

string Employee::getPassword()
{
	return password;
}

ostream& operator<<(ostream &out, Employee &inEmployee) {

	out << "Id: " << inEmployee.Id << " Name: " << inEmployee.employeeName << endl;
	return out;

}

Employee& Employee::setListValue(Employee& obj, string str, int  i)
{
	//Employee obj;
	int j = i % 3;
	if (i > 3 && j == 1)
	{
		str = str.substr(1, str.length() - 1);
	}
	if (j == 1)
	{
		obj.setEmployeeId(str);
	}
	else if (j == 0)
	{
		obj.setPassword(str);
	}
	else if (j == 2)
	{
		obj.setEmployeeName(str);
	}
	return obj;
}

ofstream& operator<<(ofstream &fout, Employee &inEmployee) {

	//string gibberishPass;
	for (char a : inEmployee.password)
	{
		a = a - 25;
	}
	fout << "\n" << inEmployee.Id << "!" << inEmployee.employeeName << "!" << inEmployee.password;
	return fout;
}

ifstream& operator>>(ifstream &fin, Employee &inEmployee) {

	//string gibberishPass;
	fin >> inEmployee.Id >> inEmployee.employeeName >> inEmployee.password;
	for (char a : inEmployee.password)
	{
		a = a + 25;
	}
	return fin;

}

bool Employee::operator==(const Employee inEmployee)
{

	return Id == inEmployee.Id;
}

void Employee::setPassword(string inPass)
{
	password = inPass;
}

bool Employee::setEmployeeName(string inName)
{
	for (int i = 0; i < inName.length(); i++)
	{
		if (!((inName[i] >= 'A' && inName[i] <= 'Z') || (inName[i] >= 'a' && inName[i] <= 'z') || inName[i] == ' '))
		{
			cout << endl << "\tName can contain only alphabets ans spaces.";
			return 0;
		}
	}
	employeeName = inName;
	return 1;
}

bool Employee::setEmployeeId(string inId) 
{
	
	Id = inId;
	return 1;
}