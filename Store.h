#pragma once

#include"Payment.h"
#include"Food.h"
#include"Customer.h"
#include"Admin.h"
#include"Employee.h"
#include"Pizza.h"
#include"NonPizza.h"

#include<vector>
#include<cstring>
#include<fstream>
#include<string>
#include<ctype.h>

using namespace std;

class PizzaStore
{
private:
	string name;
	vector<Customer> custlist;		//LIST OF THE CUSTOMERS
	vector<Employee> elist;			//LIST OF ALL THE EMPLOYEES
	vector<Admin> adlist;			//LIST OF THE ADMINS
	vector<Order> orderlist;		//LIST OF ALL THE ORDERS MADE BY CUSTOMERS
	vector<Toppings> tlist;			//LIST OF ALL THE TOPPINGS WHICH THE CUSTOMER CAN ADD
	vector<NonPizza> nplist;		//LIST OF ALL THE NON PIZZA ITEMS WHICH THE PIZZA CAN ADD

public:

	PizzaStore(string pname)
	{
		name = pname;
		readAdminList();
		readCustomerList();
		readEmployeeList();
		readNonPizzaList();
		readToppingsList();
		readOrderList();
	}

	int readOrderList()
	{
		ifstream fin("OrderList.txt");
		Order o;
		Pizza *p = new Pizza;
		NonPizza np;
		Toppings t;
		int n, tn, n1;
		char ch;
		char* name = new char[20];
		string thing, thing2, thing3, thing4, thing5, thing6, tname;
		float price, price1, price2, price3;

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin.getline(name, 20))
		{
			o.setName(name);

			fin >> thing;

			if (thing == "PizzaList")
			{
				fin >> n;
				for (int i = 0; i < n; i++)
				{
					fin >> tname >> price >> tn;
					p->setName(tname);
					p->setPrice(price);

					for (int j = 0; j < tn; j++)
					{
						fin >> thing2 >> price1;
						t.setName(thing2);
						t.setPrice(price1);
						p->addToppings(t);
					}

					o.getPizzaList().push_back(p);
				}

			}

			fin >> thing3;
			fin >> n1;

			for (int i = 0; i < n1; i++)
			{
				fin >> thing4 >> price2;
				np.setName(thing4);
				np.setPrice(price2);

				o.getNonPizzaList().push_back(np);
			}

			getline(fin, thing5);
			getline(fin, thing5);

			o.setStatus(thing5);
			fin >> price3;
			o.setPrice(price3);

			orderlist.push_back(o);
		}
		return 0;
	}

	void readCustomerList()
	{
		ifstream fin("Customer.txt");
		char* name = new char[20];
		char* no = new char[20];
		char* add = new char[20];
		char* eadd = new char[20];
		char* pass = new char[20];

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin.getline(name,20))
		{
			fin.getline(no, 20);
			fin.getline(add, 20);
			fin.getline(eadd, 20);
			fin.getline(pass, 20);

			Customer c(name, no, add, eadd, pass);
			custlist.push_back(c);
		}

		delete[] name;
		delete[] no;
		delete[] add;
		delete[] eadd;
		delete[] pass;
		fin.close();
	}

	void readAdminList()
	{
		ifstream fin("Admin.txt");
		char* eadd = new char[20];
		char* pass = new char[20];

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin >> eadd)
		{
			fin >> pass;

			Admin a(eadd, pass);
			adlist.push_back(a);
		}

		delete[] eadd;
		delete[] pass;
		fin.close();
	}

	void readEmployeeList()
	{
		ifstream fin("Employee.txt");
		char* eadd = new char[20];
		char* pass = new char[20];

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin >> eadd)
		{
			fin >> pass;

			Employee e(eadd, pass);
			elist.push_back(e);
		}

		delete[] eadd;
		delete[] pass;
		fin.close();
	}

	void readNonPizzaList()
	{
		ifstream fin("NonPizza.txt");
		string pname;
		float price;

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin>>pname)
		{
			fin >> price;
			NonPizza np(pname, price);
			nplist.push_back(np);
		}

		fin.close();
	}

	void readToppingsList()
	{
		ifstream fin("Toppings.txt");
		string tname;
		float price;

		if (fin.fail())
		{
			cout << "\n ERROR NO SUCH FILE PRESENT";
			exit(1);
		}

		while (fin >> tname)
		{
			fin >> price;
			Toppings t(tname, price);
			tlist.push_back(t);
		}

		fin.close();
	}

	int validate(char* eadd, char* pass, int ind)
	{
		if (ind == 1)
		{
			for (int i = 0; i < custlist.size(); i++)
			{
				if (strcmp(eadd, custlist[i].getEAdd()) == 0 && strcmp(pass, custlist[i].getPass()) == 0)
				{
					return i;
				}
			}
		}

		else if (ind == 2)
		{
			for (int i = 0; i < elist.size(); i++)
			{
				if (strcmp(eadd,elist[i].getEAdd()) == 0 && strcmp(pass,elist[i].getPass()) == 0 )
					return i;
			}
		}

		else if (ind == 3)
		{
			for (int i = 0; i < adlist.size(); i++)
			{
				if (strcmp(eadd,adlist[i].getEAdd()) == 0 && strcmp(pass,adlist[i].getPass()) == 0)
					return i;
			}
		}
		return -1;
	}
	
	void customerMenu(Customer c)
	{
		Order o;
		int n;
		do
		{
			cout << "\n\t\t CUSTOMER MENU\n\n";
			cout << "1) Go to Order Menu" << endl;
			cout << "2) Proceed to checkout" << endl;
			cout << "3) View order list and status" << endl;
			cout << "4) Exit to main menu" << endl;
			cout << "\n Enter your choice: ";
			cin >> n;

			switch (n)
			{
			case 1:
				o.orderMenu(tlist,nplist);
				o.setName(c.getName());
				break;
			case 2:
				o.getPayment().paymentMenu(o.getPrice());
				o.setStatus("PAID. FOOD BEING MADE.");
				orderlist.push_back(o);
				n = 4;
				storeVar();
				break;
			case 3:
				for (int i = 0; i < orderlist.size(); i++)
				{
					if (strcmp(c.getName(), orderlist[i].getName()) == 0)
					{
						cout << "\t\t ORDER " << i + 1 << ": " << endl;
						cout << "The status of your order is: " << orderlist[i].getOrderStatus() << endl <<endl;
					}
				}
				break;
			case 4: storeVar();
			}
		} while (n != 4);
	}

	void empMenu(Employee e) //KHALED -> NEEDS TO COMPLETE THIS
	{
		int n;
		do
		{
			cout << "\n\t\t EMPLOYEE MENU\n\n";
			cout << "1) View Order List" << endl;
			cout << "2) Mark Orders" << endl;
			cout << "3) Exit" << endl;

			cout << "\n Enter your choice: ";
			cin >> n;

			switch(n)
			{
			case 1: e.viewOrder(orderlist);
				break;
			case 2: e.orderStatus(orderlist);
				break;
			case 3: cout << "Exiting Employee Menu" << endl;
				break;
			}

		} while (n != 3);
	}

	void adminMenu(Admin a) //LOTF -> NEEDS TO COMPLETE ALL THE OTHER OPTIONS IN THIS
	{
		int n;
		Order o;
		char* name = new char[20];

		do
		{
			cout << "\n\t\t ADMIN MENU\n\n";
			cout << "1) Add Order" << endl;
			cout << "2) Delete the Order or something in it" << endl;
			cout << "3) Edit Order" << endl;
			cout << "4) Edit Toppings and it's price" << endl;
			cout << "5) Edit Non-Pizza Products and it's price" << endl;
			cout << "6) Edit Employees" << endl;
			cout << "7) Exit" << endl;
			cout << "\n Enter your choice: ";
			cin >> n;

			switch (n)
			{
			case 1: a.addOrder(tlist,nplist,orderlist);
				break;
			case 2: a.deleteOrder(o,orderlist);
				break;
			case 3: a.editOrder(orderlist,tlist,nplist);
				break;
			case 4: a.editToppings(tlist);
				break;
			case 5: a.editNonPizza(nplist);
				break;
			case 6: setEList(a.editEmployees(elist));
				break;
			case 7:cout << "Exiting menu!" << endl;
				break;
			}

		} while (n != 7);
	}

	void addNewCustomer(Customer c)
	{
		custlist.push_back(c);
	}

	vector<Order> getOList()
	{
		return orderlist;
	}

	void setOList(vector<Order> o)
	{
		orderlist = o;
	}

	void setEList(vector<Employee> e)
	{
		elist = e;
	}

	vector<Customer> getCList()
	{
		return custlist;
	}

	vector<Employee> getEList()
	{
		return elist;
	}

	vector<Admin> getAList()
	{
		return adlist;
	}

	void storeVar()
	{
		ofstream fout("Orderlist.txt");

		for (int i = 0; i < orderlist.size(); i++)
		{
			fout << orderlist[i].getName() << endl;

			for (int j = 0; j < orderlist[i].getPizzaList().size(); j++)
			{
				if (j == 0)
				{
					fout << "PizzaList" << endl;

					fout << orderlist[i].getPizzaList().size() << endl;

				}

				fout << orderlist[i].getPizzaList()[j]->getName() << endl << orderlist[i].getPizzaList()[j]->getPrice() << endl << orderlist[i].getPizzaList()[j]->getTlist().size() << endl;

				for (int k = 0; k < orderlist[i].getPizzaList()[j]->getTlist().size(); k++)
				{
					fout << orderlist[i].getPizzaList()[j]->getTlist()[k].getName() << endl << orderlist[i].getPizzaList()[j]->getTlist()[k].getPrice() << endl;
				}
			}

			for (int j = 0; j < orderlist[i].getNonPizzaList().size(); j++)
			{
				if (j == 0)
				{
					fout << "NP" << endl;

					fout << orderlist[i].getNonPizzaList().size() << endl;

				}
				fout << orderlist[i].getNonPizzaList()[j].getName() << endl << orderlist[i].getNonPizzaList()[j].getPrice() << endl;
			}
			fout << orderlist[i].getOrderStatus() << endl << orderlist[i].getPrice();
		}

		fout.close();
		ofstream foutt("Customer.txt");
		for (int i = 0; i < custlist.size(); i++)
		{
			foutt << custlist[i].getName() << endl << custlist[i].getNumber() << endl << custlist[i].getAdd() << endl << custlist[i].getEAdd() << endl << custlist[i].getPass() << endl;
		}

		foutt.close();

		ofstream fouttt("Employee.txt");
		for (int i = 0; i < elist.size(); i++)
		{
			fouttt << elist[i].getEAdd() << endl << elist[i].getPass() << endl;
		}

		fouttt.close();

		ofstream foutttt("NonPizza.txt");
		for (int i = 0; i < nplist.size(); i++)
		{
			foutttt << nplist[i].getName() << endl << nplist[i].getPrice() << endl;
		}

		foutttt.close();

		ofstream fout1("Employee.txt");
		for (int i = 0; i < elist.size(); i++)
		{
			fout1 << elist[i].getEAdd() << endl << elist[i].getPass() << endl;
		}
	}

};
