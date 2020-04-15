
#include "EmployeeSession.h"
#include "AdminSession.h"
#include "CustomerSession.h"
#include <fstream>
#include "Error.h"
#include <string.h>
#include <algorithm>
#include "Product.h"
#include <iostream>
#include "FileHelp.h"

using namespace std;

int EmployeeSession::updateCardPoints(Customer& cust, int pnts)
{
	AdminSession ads;
	CustomerSession cSess;
	string currPoints = cust.getCardPoints();
	if ((ads.convertStringToInt(currPoints) + pnts) >= 100)
	{
		pnts = 0;
	}
	else
	{
		try
		{
			list<Customer> li = cSess.getlist();
			list<Customer>::iterator itr;
			for (itr = li.begin(); itr != li.end(); itr++)
			{
				if (cust.getCustPhNum() == itr->getCustPhNum())
				{
					itr->setCardPoints(ads.convertIntToString(pnts + ads.convertStringToInt(currPoints)));
					pnts = pnts + ads.convertStringToInt(currPoints);
					break;
				}
			}
		}
		catch (Error inErr)
		{
			inErr.display();
		}
	}
			ifstream fin;
			fin.open("customer.txt");
			ofstream temp;
			temp.open("temp.txt");
			string line, prevLine;
			while (getline(fin, line, '!'))
			{
				if (line == currPoints && prevLine == cust.getCustPass())
				{
					line = ads.convertIntToString(pnts);
				}
				if (line == "\n")
				{
					temp << line;
				}
				else
				{
					temp << line << '!';
					prevLine = line;
				}
			}
			temp.close();
			fin.close();
			remove("customer.txt");
			rename("temp.txt", "customer.txt");
		
		return pnts;
}

Employee& EmployeeSession::setVal(Employee& emp)
{
	list<Employee> li = getEmplist();
	list<Employee>::iterator itr;
	int flag = 0;
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (itr->getId() == emp.getId())
		{
			emp.setEmployeeName(itr->getEmployeeName());
			emp.setPassword(itr->getPassword());
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "User ID not found.";
	}
	return emp;
}

list<Employee> EmployeeSession::getEmplist()
{
	list<Employee> li;
	string line = "";
	Employee obj;
	int i = 1;
	ifstream file("employee.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 3 == 0)
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

class searchEmployeeById {

public:
	bool operator()(Employee e1, Employee e2)
	{

		return e1.getId() < e2.getId();
	}
};

bool EmployeeSession::checkEmployee(Employee inEmployee)
{

	list<Employee> li = getEmplist();
	try
	{
		li.sort(searchEmployeeById());
		return (binary_search(li.begin(), li.end(), inEmployee, searchEmployeeById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

bool EmployeeSession::Login() {

	try {
		list<Employee> li;
		li = getEmplist();
		int flag = 0;
		string id;
		cout << "\n\tEnter the Id: ";
		cin >> id;
		employee.setEmployeeId(id);
		employee = setVal(employee);
		cout << "\n\tEnter the password: ";
		string pass;
		cin >> pass;

		if (pass != employee.getPassword())
		{
			cout << endl << "Incorrect Password";
			return 0;
		}
		else
		{
			return 1;
		}
		return 0;
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

/*Function to modify the details(Password) of the employee*/
void EmployeeSession::changePasswd(string inPass1) {

	try
	{
		list<Employee> li = getEmplist();

		list<Employee>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (employee.getId() == itr->getId() && employee.getPassword() == itr->getPassword())
			{
				itr->setPassword(inPass1);
				break;
			}
		}
		ifstream fin;
		fin.open("employee.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toUpdateLine = employee.getPassword();
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
		remove("employee.txt");
		rename("temp.txt", "employee.txt");
	}
	catch (Error inErr)
	{
		inErr.display();
	}


}

/*bool EmployeeSession::billing() {

	multimap<unsigned long, Product> mapfrom;
	list<Product> li;
	list<Customer> liC;
	list<Customer>::iterator itrC;

	//getting the cart details along with the customer id  from the Cart.txt into a multimap
	mapfrom = getCart_FromFile(CART_FILE);
	unsigned long tempcustid = 0;
	double tempamt = 0;

	multimap<unsigned long, Product>::iterator itr;

	if (!mapfrom.empty())
	{
		for (itr = mapfrom.begin(); itr != mapfrom.end(); itr++) {

			if (tempcustid != itr->first)
			{
				cout << "\n\tCust id: " << itr->first << endl;
				tempcustid = itr->first;
			}
		}

		cout << "\n\tEnter the customer id to display its Cart: ";
		cin >> tempcustid;
		customer.setCustId(tempcustid);
		cout << endl << endl;
		cout << "\n\tCart for Customer Id: " << tempcustid << endl;
		for (itr = mapfrom.begin(); itr != mapfrom.end(); itr++)
		{
			if (itr->first == tempcustid)
			{
				cout << "\n\t" << itr->second << endl;
				li.push_back(itr->second);
				tempamt += itr->second.getProductCost();

			}
		}
		cout << "\n\tCart Total: " << tempamt;

		//setting the product list in the private data member of the object bill in the employe Session
		bill.setBillList(li);
		bill.setBillAmt(tempamt);

		//setting up customer for the current bill procedure
		liC = getList_FromFile<Customer>(CUSTOMER_FILE);

		for (itrC = liC.begin(); itrC != liC.end(); itrC++)
		{
			if (itrC->getCustId() == tempcustid)
			{
				customer.setCardNumber(itrC->getCardNumber());
				customer.setCardPoints(itrC->getCardPoints());
				customer.setCustPhNum(itrC->getCustPhNum());
			}
		}

		return true;

	}
	else
	{
		return false;
	}


}

//setting up the bill discount from the current card points
void EmployeeSession::addDiscount() {


	if (customer.getCardPoints() > 99)
	{
		bill.setBillDiscount(10.0);
		customer.setCardPoints(0);
	}
	else
		bill.setBillDiscount(0);
}

//setting the card points on the total bill amount
void EmployeeSession::addPointsToCard() {


	if (bill.getBillAmt() > 1000)
	{
		customer.setCardPoints(customer.getCardPoints() + 10);
	}

}

//generate the bill and print on the screen after setting the Bill date and number
void EmployeeSession::generateBill() {

	bill.setBillDate(getDateString());
	bill.setBillTime(getTimeString());
	bill.printBill(customer, employee);
	bill.storeBill(customer, employee);
}


void EmployeeSession::updateCart_File() {

	multimap<unsigned long, Product> mapC = getCart_FromFile(CART_FILE);
	multimap<unsigned long, Product>::iterator itr;

	ofstream fileout;
	fileout.open(CART_FILE);
	for (itr = mapC.begin(); itr != mapC.end(); itr++) {

		if (itr->first != customer.getCustId())
		{
			fileout << itr->second << " " << itr->first;
		}

	}
	fileout.close();

}

void EmployeeSession::updateCardPoints_File() {

	list<Customer> li = getList_FromFile<Customer>(CUSTOMER_FILE);

	list<Customer>::iterator itr;

	for(itr=li.begin();itr!=li.end();itr++)
	{
	cout<<*itr;
	}

	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (customer.getCustId() == itr->getCustId())
		{
			itr->setCardPoints(customer.getCardPoints());
		}

	}

	putList_InFile(CUSTOMER_FILE, li);
}*/

int EmployeeSession::updateStock(Product inprod, int inStock) {

	try
	{
		AdminSession ads;
		list<Product> li = ads.getProdlist();
		string prevStock, avlStock;
		list<Product>::iterator itr;
		int amt=0;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (inprod.getId() == itr->getId())
			{
				int stock = 0;
				amt = ads.convertStringToInt(itr->getPrice());
				prevStock = itr->getStock_available();
				avlStock = prevStock;
				stock = ads.convertStringToInt(avlStock);
				stock -= inStock;
				if (stock < 0)
				{
					cout << "Sorry for the inconvinience! Insufficient Stock. Order can not be placed.";
					return -1;
				}
				avlStock = ads.convertIntToString(stock);
				inprod.setStock_available(avlStock);
			}
		}
		ifstream fin;
		fin.open("product.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		while (getline(fin, line, '!'))
		{
			if (line == prevStock)
			{
				line = avlStock;
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
		remove("product.txt");
		rename("temp.txt", "product.txt");
		amt = amt * inStock;
		return amt;
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

/*Menu for the Employee Session*/
void EmployeeSession::displayMenu()
{
	char choice;
	system("COLOR B1");

	do {
		system("cls");
		cout << "\n\t" << getDateString();
		cout << "\n\t\t\tWELCOME " << employee.getEmployeeName() << "\n";
		cout << "\n\t\t\tEnter the choice to enter into\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tSelf Service Options Modify Details\n\n";
		cout << "\t\t\t 1.Change your Password\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\n\t\t\tBilling Related Options\n\n";
		cout << "\t\t\t 2.Billing\n";
		cout << "------------------------------------------------------------------\n\n";
		cout << "\t\t\t 3.LOGOUT\n";
		cout << "\n------------------------------------------------------------------\n";
		cout << "\n\tEnter your choice----> ";
		cin >> choice;

		switch (choice) {

			//case 1 employee is allowed to modify the password. 
		case '1':
			try {
				cout << "\nEnter current password: ";
				string pswd;
				cin >> pswd;
				if (pswd != employee.getPassword())
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
					cout << endl << "\tPassword successfully changed.";
				}
				else
					cout << "\n\t-!!Passwords Entered Do not match each other.!!-\n";
			}
			catch (Error inErr) {
				inErr.display();
			}

			break;

			//Get Cart Details and display.
		case '2':
			try 
			{
				CustomerSession custSess;
				Customer cust;
				string phnNo;
				cout << "Enter Customer Phone Number : " << endl;
				cin >> phnNo;
				cust.setCustPhNum(phnNo);
				if (custSess.checkCustomer(cust))
				{
					list<Customer> custList = custSess.getlist();
					for (list<Customer>::iterator i = custList.begin(); i != custList.end(); i++)
					{
						if (i->getCustPhNum() == cust.getCustPhNum())
						{
							cust.setCustName(i->getCustName());
							cust.setCardPoints(i->getCardPoints());
							cust.setPassword(i->getCustPass());
						}
					}
					AdminSession ads;
					char ch = '1';
					Product prod;
					list<Product> li = ads.getProdlist();
					list<Product>::iterator itr;
					int i = 1, amount = 0;
					cout << endl << "\t\tBilling for " << cust.getCustName() << " with Card Points = " << cust.getCardPoints();
					cout << "\nList of Products Available in Store: \n";
					cout << endl << "   \tProduct ID" << "\tProduct Name\t" << "Price" << "\tAvaialble Stock" << endl;
					for (itr = li.begin(); itr != li.end(); itr++)
					{
						if (itr == li.begin())
							continue;
						cout << i << "->\t";
						cout << itr->getId() << "\t\t" << itr->getProductName();
						cout << "\t\t" << itr->getPrice();
						cout << "\t" << itr->getStock_available();
						i++;
						cout << endl;
					}
					do
					{
						cout << "\n\t\tEnter the Product Id of the product to be billed: ";
						string pid;
						cin >> pid;
						prod.setId(pid);
						cout << "\n\t\tEnter the quantity: ";
						string quan;
						cin >> quan;
						int quantity;
						quantity = ads.convertStringToInt(quan);
						amount += updateStock(prod, quantity);
						if (amount == -1)
						{
							break;
						}
						cout << "\n\t\tTotal amount = " << amount;
						cout << "\nDo you want to bill more items?1-->YES (Press any other key to exit billing) : ";
						cin >> ch;
					} while (ch == '1');
					int points = amount / 100;
					float disc;
					points = updateCardPoints(cust, points);
					if (points == 0)
					{
						cout << endl << "Congrats!! 100 points reached. You get a discount of 20% on the bill amount." << endl;
						disc = 0.2*amount;
						amount -= disc;
						cout << endl << "You get a total discount of Rs." << disc << "\nThe net payable amount is Rs." << amount;
					}
					else
					{
						cout << "\nTotal points after the current billing = " << points << endl;
					}
				}
				else
				{
					cout << "Customer not registered.";
					return;
				}
			}
			catch (Error inErr) {
				inErr.display();
			}

			break;

		case '3': return;

		default:
			cout << "\n\tInvalid Choice";
			break;

		}

			cout << "\n\n\tDo you want to continue as Employee?\n\tPress 1 to continue. 0. EXIT ----> ";
			cin >> choice;
	} while (choice != '0' && choice == '1');
	system("COLOR F0");
}