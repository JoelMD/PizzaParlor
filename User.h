#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include"Order.h"
using namespace std;

class User
{
private:
	char* eadd;
	char* pass;
	int ind;
	vector<Order> orderlist;

public:
	User()
	{
		eadd = new char[20];
		pass = new char[20];
	}

	User(const char* ueadd, const char* upass, int uind)
	{
		eadd = new char[20];
		pass = new char[20];

		strcpy(eadd,ueadd);
		strcpy(pass,upass);
		ind = uind;
	}

	User(const User& u)
	{
		eadd = new char[20];
		pass = new char[20];

		strcpy(eadd, u.eadd);
		strcpy(pass, u.pass);
		ind = u.ind;
		setOrderList(u.getOrderList());
	}

	User& operator=(const User& u)
	{
		strcpy(eadd, u.eadd);
		strcpy(pass, u.pass);
		ind = u.ind;
		orderlist = u.getOrderList();

		return *this;
	}

	virtual ~User()
	{
		delete[] eadd;
		delete[] pass;
	}

	char* getEAdd()
	{
		return eadd;
	}

	char* getPass()
	{
		return pass;
	}

	void setEadd(char* ueadd)
	{
		strcpy(eadd, ueadd);
	}

	void setPass(char* upass)
	{
		strcpy(pass, upass);
	}

	int getInd()
	{
		return ind;
	}

	void setInd(int uind)
	{
		ind = uind;
	}

	const vector<Order>& getOrderList() const
	{
		return orderlist;
	}

	void setOrderList(vector<Order> aorderlist)
	{
		orderlist = aorderlist;
	}
};
