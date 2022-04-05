#pragma once
#include"Food.h"

class NonPizza : public Food
{
private:
	int id;
public:
	NonPizza()
	{

	}

	NonPizza(string npname, float price)
		: Food(npname, price)
	{

	}

	friend ostream& operator<<(ostream& out, NonPizza np)
	{
		out << np.getName() << " " << np.getPrice();
		return out;
	}
};