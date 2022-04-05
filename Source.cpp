#include"Store.h"
#include"Customer.h"
#include"Employee.h"
#include"Admin.h"
#include<cstring>

using namespace std;

class shortPass :public exception {
public:
	shortPass(string msg = "Please use a minimum of 8 characters") :exception(msg.c_str()) {}
};


int login(PizzaStore p, int& ind)
{
	int n;
	char* add = new char[20];
	char* pass = new char[20];

	cout << "\n\t\t\LOGIN MENU\n1) Login as customer\n2) Login as employee\n3) Login as admin\n4) Sign-up as customer\n5) Exit\n\nEnter your choice: ";
	cin >> n;

	do 
	{
		if (n == 5)
		{
			cout << "\nThank you for using our system!" << endl;
			system("pause");
			delete[] add;
			delete[] pass;
			exit(1);
		}

		if (n == 1 || n == 2 || n == 3)
		{
			ind = n;
			cout << "\nEnter your email address: ";
			cin >> add;
			cout << "\nEnter your password: ";
			cin >> pass;
			return p.validate(add, pass, n);
		}

		if (n == 4)
		{
			ind = 4;
			return 0;
		}

		else
			cout << "ENTER A VALID INPUT!" << endl;
		
	} while (n != 5);
}

int main()
{
	PizzaStore pstore("PIZZARIA");
	int ind, userindex;
	char* name = new char[20];
	char* no = new char[20];
	char* add = new char[20];
	char* eadd = new char[20];
	char* pass = new char[20];

	do
	{
		userindex = login(pstore, ind);
		if (userindex != -1)
		{
			if(ind==1)
				pstore.customerMenu(pstore.getCList()[userindex]);

			else if(ind == 2)
				pstore.empMenu(pstore.getEList()[userindex]);

			else if(ind ==3)
				pstore.adminMenu(pstore.getAList()[userindex]);

			else if (ind == 4)
			{
				cout << "Enter your full name: ";
				cin >> name;

				cout << "Enter your phone number: ";
				cin >> no;

				cout << "Enter your Home Address: ";
				cin >> add;

				cout << "Enter your email address: ";
				cin >> eadd;

				try
				{
					cout << "\nEnter your password (make sure it is atleast 8 characters): ";
					cin >> pass;
					if (strlen(pass) < 8) {
						throw shortPass();
					}

					Customer c(name, no, add, eadd, pass);
					pstore.addNewCustomer(c);

					cout << "Account added successfully!" << endl;
				}
				catch (shortPass  o) { cout << "Exception occurred: " << o.what() << endl; }

				
			}
		}

	} while (userindex != -1);

	delete[] name;
	delete[] no;
	delete[] add;
	delete[] eadd;
	delete[] pass;

	system("pause");
	return 0;
}