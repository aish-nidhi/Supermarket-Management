
#include <iostream>
#include <iomanip>
#include <string>
#include "AdminSession.h"
#include "CustomerSession.h"
#include "Customer.h"
#include "Error.h"
#include "FileHelp.h"
#include <algorithm>

list<Customer> CustomerSession::getlist()
{
	list<Customer> li;
	string line = "";
	Customer obj;
	int i = 1;
	ifstream file("customer.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 4 == 0)
			{
				li.push_back(obj);
			}

			i++;
		}
	}
	else
		cout << "Unable to open the file\n";
	file.close();

	return li;
}

class searchCustomerById {

public:
	bool operator()(Customer c1, Customer c2)
	{

		return c1.getCustPhNum() < c2.getCustPhNum();
	}
};

bool CustomerSession::checkCustomer(Customer inCust)
{

	list<Customer> li = getlist();
	try
	{
		li.sort(searchCustomerById());
		return (binary_search(li.begin(), li.end(), inCust, searchCustomerById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

void CustomerSession::putIntoFile(Customer cust)
{
	ofstream outfile("customer.txt", ios::app);
	outfile << cust.getCustPhNum() << "!" << cust.getCustName() << "!" << cust.getCustPass() << "!" << cust.getCardPoints() << "!" << endl;
	outfile.close();
}

void CustomerSession::addCustomer(Customer inCust)
{
	list<Customer> li = getlist();
	try
	{
		li.push_back(inCust);
		putIntoFile(inCust);

	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

void CustomerSession::changePasswd(string inPass1) {

	try
	{
		list<Customer> li = getlist();
		list<Customer>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (customer.getCustPhNum() == itr->getCustPhNum() && customer.getCustPass() == itr->getCustPass())
			{
				itr->setPassword(inPass1);
				break;
			}
		}
		ifstream fin;
		fin.open("customer.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toUpdateLine = customer.getCustPass();
		while (getline(fin, line, '!'))
		{
			if (line == toUpdateLine)
			{
				line = inPass1;
			}
			if (line == "\n")
			{
				temp << line;
			}
			else
				temp << line << '!';
		}
		temp.close();
		fin.close();
		remove("customer.txt");
		rename("temp.txt", "customer.txt");
	}
	catch (Error inErr) {

		inErr.display();
	}
}

bool CustomerSession::Login() {

	int ch;
	cout << "\n**********************************************************\n";
	cout << "\n\t1. New Customer \n\t2. Existing Customer \n";
	cout << "\n**********************************************************\n";
	cout << "\n\tEnter your choice -----> ";
	cin >> ch;
	if (ch == 1) {
		//new customer
		try {
			Customer cust;
			cout << "\n\n\tEnter Your Mobile Number (this will be your User ID): ";
			string phnum;
			cin >> phnum;
			
			if (phnum.length() != 10)
			{
				cout << "\nInvalid phone number.\n";
				return 0;
			}
			else
			{
				for (int i = 0; i < phnum.length(); i++)
				{
					if (!(phnum[i]>='0' && phnum[i]<='9'))
					{
						cout << "\nPhone number must contain only digits.\n";
						return 0;
					}
				}
			}
			customer.setCustPhNum(phnum);

			cin.ignore();
			
			if (!checkCustomer(customer))
			{
				cout << "\n\tEnter Your Name: ";
				string name;
				getline(cin, name);
				if (!customer.setCustName(name))
				{
					return 0;
				}
				cout << "\n\tSet Password: (password can not contain ! and spaces)";

				string pass;
				int flag=1;
				cin >> pass;
				for (int x = 0; x < pass.length(); x++)
				{
					if (pass[x] == '!' || pass[x] == ' ')
					{
						cout << "\nInvalid password.Password should not have ! and spaces.\n";
						flag =  0;
					}
				}
				if (flag != 0)
				{
					customer.setPassword(pass);
					customer.setCardPoints("0");
					addCustomer(customer);
					cout << "\n-->Registration Successful.<--\n";
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				cout << "\n\tSeems like you are already a customer.Try login as existing customer.\n";
				return 0;
			}
		}
		catch (Error inerr)
		{
			inerr.display();
		}
	}
	else if (ch == 2)
	{
		//existing customer
		try
		{

			list<Customer> li;
			li = getlist();
			int flag = 0;
			cout << "\n\tEnter the Id: ";
			string id, corresPass;
			cin >> id;
			customer.setCustPhNum(id);
			list<Customer>::iterator itr;
			for (itr = li.begin(); itr != li.end(); itr++)
			{
				if (itr->getCustPhNum() == id)
				{
					customer.setCustName(itr->getCustName());
					customer.setCardPoints(itr->getCardPoints());
					corresPass = itr->getCustPass();
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				cout << "\nIncorrect ID or Not registered.\n";
				return 0;
			}
			cout << "\n\tEnter the password: ";
			string pass;
			cin >> pass;
			customer.setPassword(pass);

			if (pass != corresPass)
			{
				cout << endl << "Incorrect password.\n";
				return 0;
			}
			else
			{
				return 1;
			}
			return 0;
		}
		catch (Error inErr) {

			throw inErr;
		}
	}
	else
	{
		cout << "\n\tInvalid Choice.\n";
		return false;
	}
}

void CustomerSession::displayMenu() {

	char choice;
	system("COLOR 5F");
	do {
		system("cls");
		string catName;
		cout << "\n\t" << getDateString();
		cout << "\n\t\t\tWelcome " << customer.getCustName() << " !\n";
		cout << "\n\t\t\tSelect choice\n";
		cout << "********************************************************************************";
		cout << "\n\t\t\t1.Search Products by Category\n\n";
		cout << "\t\t\t2.View Card Points\n\n";
		cout << "\t\t\t3.Change Password\n\n";
		cout << "\t\t\t4.Logout\n\n";
		cout << "\n********************************************************************************\n";
		cout << "\n\t\tEnter your choice -----> ";
		cin >> choice;
		AdminSession ads;
		switch (choice)
		{
			case '1':
				try {
					Category cat;
					if (!cat.viewCategories())
					{
						return;
					}
					cout << "\n\tEnter the ID of the category you wish to browse: ";
					string cId;
					cin >> cId;
					list<Product> li = ads.getProdlist();
					list<Product>::iterator itr;
					int i = 1;
					cout << "\nList of Products Available in Store for selected category are: \n";
					cout << "\n   \tProduct Id\tProduct Name\t\tPrice\tAvailable Stock\n";
					for (itr = li.begin(); itr != li.end(); itr++)
					{
						if (itr == li.begin())
							itr++;
						if (itr->category.getCategoryId() != cId)
						{
							continue;
						}
						i = 0;
						cout << "   \t";
						cout << itr->getId();
						cout << "\t"<<setw(10) << itr->getProductName();
						cout << "\t"<<setw(10)<< itr->getPrice();
						cout << "\t"<<setw(10) << itr->getStock_available();
						i++;
						cout << endl;
					}
					if (i != 0)
					{
						cout << endl << "Sorry No products for this category available right now.We regret the inconvinience caused." << endl;
						return;
					}
				}
				catch (Error inErr) {
					inErr.display();
				}
				break;
			case '2':cout << endl << "\t\tTotal Shopping points earned are " << customer.getCardPoints() << "pts." << endl;
				break;
		case '3':
			try {

				cout << "\nEnter current password: ";
				string pswd;
				cin >> pswd;
				if (pswd != customer.getCustPass())
				{
					cout << endl << "Incorrect current password, try again.";
					return;
				}
				cout << "\n\tEnter the new Password: ";
				string pass1;
				cin >> pass1;
				cout << "\n\tConfirm Password: ";
				string pass2;
				cin >> pass2;
				if (pass1 == pass2)
				{
					changePasswd(pass1);
					cout <<endl<< "\t\tPassword successfully changed."; 
				}
				else
					cout << "\n\t-!!Passwords Entered Do not match each other.!!-\n";
			}
			catch (Error inErr) {
				inErr.display();
			}

			break;
		case '4':return;
			break;
		default:cout << "Invalid option.Try again.";
		}
		
			cout << "\n\tDo you want to continue as Customer?\n\t1.Yes 0. EXIT ---->  ";
			cin >> choice;
	} while (choice != '0' && choice == '1');
}