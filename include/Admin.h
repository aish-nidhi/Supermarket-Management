#pragma once

#include <string>
#include <fstream>

using namespace std;

class Admin {

private:
	string Id;
	string adminName;
	string password;

public:
	Admin() {}
	Admin(string inId, string inAdminName, string inAdminPasswd) : Id(inId), adminName(inAdminName), password(inAdminPasswd) {}
	string getId();
	string getAdminName();
	string getPassword();
	void setAdminName(string inName);
	void setId(string);
	void setPassword(string);
	Admin& setListValue(Admin&, string, int);
	friend ostream& operator<<(ostream&, Admin&);
	friend ofstream& operator<<(ofstream&, Admin&);
	friend ifstream& operator>>(ifstream&, Admin&);
	bool operator==(const Admin);
	string getType()
	{
		return "Admin";
	}
};