#pragma once
#include<iostream>
#include<string>

using namespace std;

class Payment
{
private:
	string ccn;
	string edate;

public:
	Payment()
	{

	}

	void paymentMenu(float price)
	{
		cout << "THE TOTAL PRICE FOR YOUR ORDER IS: " << price << endl << endl;
		cout << "Enter the credit card number: ";
		cin >> ccn;
		cout << "Enter the expiry date: ";
		cin >> edate;

		cout << "\t\t YOUR ORDER HAS BEEN PROCESSED!";
	}

	void setCCN(string cccn)
	{
		ccn = cccn;
	}

	void setDate(string d)
	{
		edate = d;
	}
};