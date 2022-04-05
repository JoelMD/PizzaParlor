#include"Food.h"
#include<string>
class Toppings : public Food
{
private:

public:
	Toppings()
	{

	}

	Toppings(string tname, float price)
		: Food(tname, price)
	{

	}

	friend ostream& operator<<(ostream& out, Toppings t)
	{
		out << "Name: " << t.getName() << endl << "Price: " << t.getPrice() << "$" << endl;
		return out;
	}
};