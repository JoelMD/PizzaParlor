#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"Pizza.h"
#include"Store.h"
#include"NonPizza.h"
#include"Food.h"
#include"Payment.h"
using namespace std;

class Order
{
private:
	char* oname;
	vector<Pizza*> pizzalist;
	vector<NonPizza> nplist;
	string orderStatus;
	float tprice;
	Payment p;

public:
	Order()
	{
		oname = new char[20];
		p.setCCN("NOTHING");
		p.setDate("NOTHING");
	}

	void setPrice(float price)
	{
		tprice = price;
	}

	void orderMenu(vector<Toppings>& tlist, vector<NonPizza>& nlist)
	{
		int n;

		do 
		{
			cout << "\n\n\t\tORDER MENU\n\n1) Create a pizza\n2) Customize pizza\n3) Remove a pizza\n4) Duplicate Pizza\n5) Add side dish/drink\n6) Remove side dish/drink\n7) Display Order\n8) Exit\n\nEnter your choice: ";
			cin >> n;

			switch (n)
			{
			case 1: createPizza(tlist);
				break;
			case 2: customizePizza(tlist);
				break;
			case 3: removePizza();
				break;
			case 4: duplicatePizza();
				break;
			case 5: addNonPizza(nlist);
				break;
			case 6: removeNonPizza();
				break;
			case 7: viewOrder();
				break;
			case 8: exitOrder();
				break;
			default:
				cout << "\nINVALID INPUT PLEASE TRY AGAIN!" << endl;
			}
		} while (n != 8);

	}

	void createPizza(vector<Toppings>& tlist)
	{
		string name;
		Pizza* p = new Pizza;
		Toppings t;
		int i, n;
		float price=15;

		cout << "\n\t\t THE LIST OF AVAILABLE TOPPINGS ARE:\n\n";
		for (i = 0; i < tlist.size(); i++)
			cout << tlist[i] << endl;
	
		cout << "Enter the number of toppings you would like to add: ";
		cin >> n;

		if (isalpha(n))
		{
			do
			{
				cout << "Enter a number!" << endl;
				cout << "Enter the number of Side dishes/drinks you would like to add: ";
				cin >> n;

			} while (isalpha(n));
		}

		for (int i = 0; i < n; i++)
		{
			bool flag = 0;
			cout << "Enter the name of the topping you would like to add: ";
			cin >> name;

			for (int i = 0; i < tlist.size(); i++)
			{
				if (name == tlist[i].getName())
				{
					t = tlist[i];
					price += tlist[i].getPrice();
					p->addToppings(t);
					cout << "Topping added successfully!" << endl;
					flag = 1;
					break;
				}
			}

			if (flag == 0)
			{
				cout << "No such topping present!" << endl;
				i--;
			}
		}

		cout << "\n Enter the pizza name: ";
		cin >> name;
		p->setName(name);
		p->setPrice(price);
		pizzalist.push_back(p);

		cout << "Your order has been successfully added." << endl;
	}

	void customizePizza(vector<Toppings> tlist)
	{
		viewOrder();
		string name;
		int n;

		cout << "Enter the name of the pizza you want to customize: ";
		cin >> name;

		for (int i = 0; i < pizzalist.size(); i++)
		{
			if (pizzalist[i]->getName() == name)
			{
				cout << "1) Add Topping\n2) Remove Topping\n\nChoose your option: ";
				cin >> n;

				if (n == 1)
				{
					Pizza* p = pizzalist[i];
					pizzalist.erase(pizzalist.begin() + i);

					Toppings t;
					int k;
					float price = p->getPrice();
					cout << "\n\t\t THE LIST OF AVAILABLE TOPPINGS ARE:\n\n";
					for (int i = 0; i < tlist.size(); i++)
						cout << tlist[i] << endl;

					cout << "Enter the number of toppings you would like to add: ";
					cin >> k;
					for (int j = 0; j < k; j++)
					{
						cout << "Enter the name of the topping you would like to add: ";
						cin >> name;

						for (int l = 0; l < tlist.size(); l++)
						{
							if (name == tlist[l].getName())
							{
								t = tlist[l];
								price += tlist[l].getPrice();
								p->addToppings(t);
								cout << "Topping added successfully!" << endl;
								break;
							}
						}
					}

					p->setPrice(price);
					pizzalist.push_back(p);
				}

				if (n == 2)
				{
					Pizza* p = new Pizza;
					string tname;
					float price = 0;
					p->setName(pizzalist[i]->getName());
					p->setPrice(pizzalist[i]->getPrice());

					cout << "Enter the name of the topping you would like to delete: ";
					cin >> tname;

					for (int k = 0; k < pizzalist[i]->getTlist().size(); k++)
					{
						if (tname != pizzalist[i]->getTlist()[k].getName())
						{
							p->addToppings(pizzalist[i]->getTlist()[k]);
							price += pizzalist[i]->getTlist()[k].getPrice();
							p->setPrice(price);
							cout << "Topping has been deleted successfully!";
						}

					}

					pizzalist.erase(pizzalist.begin() + i);
					pizzalist.push_back(p);
					
				}
			
			}
		}

	}

	void removePizza()
	{
		viewOrder();
		string name;

		cout << "Enter the name of the pizza you want to remove: ";
		cin >> name;

		for (int i = 0; i < pizzalist.size(); i++)
		{
			if (pizzalist[i]->getName() == name)
			{
				pizzalist.erase(pizzalist.begin() + i);
				cout << "Pizza removed successfully!" << endl;
			}
		}

	}

	void duplicatePizza()
	{
		string pname;
		Pizza* p = new Pizza;

		for (int i = 0; i < pizzalist.size(); i++)
		{
			cout << pizzalist[i]->getName() << endl;
		}

		cout << "Enter the name of the pizza you want to duplicate: ";
		cin >> pname;

		for (int i = 0; i < pizzalist.size(); i++)
		{
			if (pname == pizzalist[i]->getName())
			{
				p = pizzalist[i];
			}
		}

		pizzalist.push_back(p);

	}

	void addNonPizza(vector<NonPizza> nlist)
	{
		string name;
		cout << "\n\t\t THE LIST OF AVAILABLE SIDE DISHES/DRINKS ARE:\n\n";
		for (int i = 0; i < nlist.size(); i++)
		{
			cout << "Name: " << nlist[i].getName() << endl << "Price: " << nlist[i].getPrice() << "$" << endl << endl;
		}

		int n;
		cout << "Enter the number of Side dishes/drinks you would like to add: ";
		cin >> n;

		if (isalpha(n))
		{
			do
			{
				cout << "Enter a number!" << endl;
				cout << "Enter the number of Side dishes/drinks you would like to add: ";
				cin >> n;
			} while (isalpha(n));
		}

		for (int i = 0; i < n; i++)
		{
			bool flag = 1;

			cout << "Enter the name of the Side dish/drink you would like to add: ";
			cin >> name;

			for (int j = 0; j < nlist.size(); j++)
			{
				if (name == nlist[j].getName())
				{
					nplist.push_back(nlist[i]);
					cout << "Item added successfully!" << endl;
					flag = 0;
					break;
				}
			}

			if(flag==1)
			{
				cout << "No such item present!" << endl;	
				i--;
			}
		}
	}

	void removeNonPizza()
	{
		viewOrder();
		string name;

		cout << "Enter the name of the Side dish/drink you want to remove: ";
		cin >> name;

		for (int i = 0; i < nplist.size(); i++)
		{
			if (nplist[i].getName() == name)
			{
				nplist.erase(nplist.begin() + i);
				cout << "Item removed successfully removed successfully!" << endl;
				break;
			}
		}
	}

	void viewOrder()
	{
		for (int i = 0; i < pizzalist.size(); i++)
		{
			cout << "\nPizza name: " << pizzalist[i]->getName() << endl << "Pizza Toppings: ";
			for (int j = 0; j < pizzalist[i]->getTlist().size(); j++)
			{
				cout << pizzalist[i]->getTlist()[j].getName() << ", ";
			}

			cout << endl << "Pizza price: " << pizzalist[i]->getPrice() << endl;
		}

		for (int i = 0; i < nplist.size(); i++)
		{
			cout << "\nSide dish name: " << nplist[i].getName() << endl << "Side dish price: " << nplist[i].getPrice() << endl;
		}

	}

	char* getName()
	{
		return oname;
	}

	vector<Pizza*>& getPizzaList()
	{
		return pizzalist;
	}

	vector<NonPizza>& getNonPizzaList()
	{
		return nplist;
	}

	void setName(char* name)
	{
		strcpy(oname,name);
	}

	string getOrderStatus()
	{
		return orderStatus;
	}

	Payment getPayment()
	{
		return p;
	}

	float getPrice()
	{
		return tprice;
	}

	void setStatus(string stat)
	{
		orderStatus = stat;
	}

	void exitOrder()
	{
		cout << "Exiting menu!" << endl;
		float price = 0;
		for (int i = 0; i < pizzalist.size(); i++)
			price += pizzalist[i]->getPrice();
		for (int i = 0; i < nplist.size(); i++)
			price += nplist[i].getPrice();
		tprice = price;
	}

	friend ostream& operator<<(ostream& out, Order o)
	{
		for (int i = 0; i < o.pizzalist.size(); i++)
		{
			out << o.pizzalist[i]->getName() << endl;
			cout << "Toppings:" << endl;
			for (int j = 0; j < o.pizzalist[i]->getTlist().size(); j++)
				cout << o.pizzalist[i]->getTlist()[j] << endl;
		}
		cout << "Non-Pizza:" << endl;
		for (int i = 0; i < o.nplist.size(); i++)
		{
			out << o.nplist[i].getName() << endl;
		}

		out << "Your order status is: " << o.orderStatus;

		return out;
	}
};
