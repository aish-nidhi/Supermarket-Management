#include <iostream>
#include "HomepageUI.h"
#include "Error.h"
#include "UserSession.h"
#include <windows.h>
#include "FileHelp.h"

using namespace std;

void UserInterface::displayUI() {

	char choice;

	do {
		system("cls");
		system("Color F0");
		cout << "\n\n\n\n\t\tSUPERMARKET - The One Stop Shop.";
		Sleep(5000);
		cout << "\n\t" << getDateString();
		cout << "\n\nSelect User Type from the given Menu to start the session\n";
		cout << "\n\t**             1.Admin                    **" << endl;
		cout << "\t**             2.Customer                 **" << endl;
		cout << "\t**             3.Employee                 **" << endl;
		cout << "\t**             4.EXIT                     **" << endl;
		cout << "\n\t********************************************\n";
		cout << "\n\tEnter your choice-----> ";
		cin >> choice;
		cout << "\n\n";


		switch (choice) {

		case '1': try {
			sessn = SessionFactory::createSession("Admin");
			if (sessn->Login())
				sessn->displayMenu();
			else
				cout << "\n\tLogin Failed";
		}
				  catch (Error inErr) {
					  inErr.display();
				  }
				  break;

		case '2':  try {
			sessn = SessionFactory::createSession("Customer");
			if (sessn->Login())
				sessn->displayMenu();

		}
				   catch (Error inErr) {
					   inErr.display();
				   }
				   break;

		case '3': try {
			sessn = SessionFactory::createSession("Employee");
			if (sessn->Login())
				sessn->displayMenu();
			else
				cout << "\n\tInvalid Id or Password.";
		}
				  catch (Error inErr) {
					  inErr.display();
				  }
				  break;

		case '4': return;
		default:
			cout << "\n\tInvalid Choice";
			break;

		}
		if (choice != '0')
		{
			cin.clear();
			cin.sync();
			cout << "\n\n\n\tDo you want another login session?\n\tPress 1 to continue. 0. EXIT----> ";
			cin >> choice;
		}
		system("cls");

	} while (choice != '0' && choice == '1');

}