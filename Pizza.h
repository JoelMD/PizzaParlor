#pragma once
#include"Food.h"
#include"Toppings.h"

class Pizza : public Food
{
	vector<Toppings> tlist;

public:
	Pizza()
	{

	}

	Pizza(string pname, float price)
		: Food(pname, price)
	{
	
	}

	void addToppings(Toppings t)
	{
		tlist.push_back(t);
	}

	vector<Toppings>& getTlist()
	{
		return tlist;
	}

	void setTlist(vector<Toppings> ptlist)
	{
		tlist = ptlist;
	}

	Pizza& operator=(Pizza p)
	{
		setName(p.getName());
		setPrice(p.getPrice());
		setTlist(p.getTlist());
		return *this;
	}

	friend ostream& operator<<(ostream& out, Pizza* p)
	{
		out << p->getName() << " " << p->getPrice();
		return out;
	}

};