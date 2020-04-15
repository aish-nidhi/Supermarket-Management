#include <string>
#include <fstream>
#include "Error.h"
#include "Admin.h"
#include "FileHelp.h"

//ADMIN CLASS

string Admin::getId()
{
	return Id;
}

string Admin::getAdminName()
{
	return adminName;
}

string Admin::getPassword()
{
	return password;
}

void Admin::setAdminName(string inName)
{
	adminName = inName;
}

ostream& operator<<(ostream &out, Admin &inAdmin) {

	out << "Id: " << inAdmin.Id << " Name: " << inAdmin.adminName << endl;
	return out;

}

Admin& Admin::setListValue(Admin& obj, string str, int  i)
{
	//Admin obj;
	int j = i % 3;
	if (i > 3 && j == 1)
	{
		str = str.substr(1, str.length() - 1);
		//cout << str;
	}
	//cout << j;
	if (j == 1)
	{
		obj.setId(str);
	}
	else if (j == 0)
	{
		//cout << endl << str;
		obj.setPassword(str);
		//cout << obj.getPassword();
	}
	else if (j == 2)
	{
		obj.setAdminName(str);
	}
	return obj;
}

ofstream& operator<<(ofstream &fout, Admin &inAdmin) {

	//string gibberishPass;
	for (char a : inAdmin.password)
	{
		a = a - 25;
	}
	fout << "\n" << inAdmin.Id << "!" << inAdmin.adminName << "!" << inAdmin.password;
	return fout;
}

ifstream& operator>>(ifstream &fin, Admin &inAdmin) {

	//string gibberishPass;
	fin >> inAdmin.Id >> inAdmin.adminName >> inAdmin.password;
	for (char a : inAdmin.password)
	{
		a = a + 25;
	}
	return fin;

}

bool Admin::operator==(const Admin inAdmin)
{

	return Id == inAdmin.Id;
}

void Admin::setPassword(string inPass) {


	password = inPass;

}

void Admin::setId(string inId) {

	Id = inId;

}