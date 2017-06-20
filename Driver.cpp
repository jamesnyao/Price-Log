#include <iostream>
#include <fstream>
#include <list>

#include "Stock.h"

using namespace std;

int main(int argc, char **argv)
{
	string ticker, line;
	int shares, price, num_stocks, i;
	list<Stock*>::iterator it;
	
	list<Stock*> *stocks = new list<Stock*>();
	
	fstream log("stocks.log");
	if (log.is_open())
	{	
		for (num_stocks = 0; log >> ticker; num_stocks++)
		{
			log >> shares >> price;
			stocks->push_back(new Stock(ticker, shares, price));
		}
	}
	else
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}
	
	while (true)
	{
		cout << "TICKER\tSHARES\tPRICE" << endl;
		for (it = stocks->begin(); it != stocks->end(); it++)
		{
			cout << (*it)->get_ticker() << '\t'
				<< (*it)->get_shares() << '\t'
				<< (((float)(*it)->get_price()) / 100) << endl;
		}
		cin >> line;
		if ((line == "buy") || (line == "BUY"))
		{
			cin >> ticker;
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					cin >> shares >> price;
					(*it)->buy(shares, price);
					break;
				}
			}
			if (it == stocks->end())
			{
				stocks->push_back(new Stock(ticker, shares, price));
			}
		}
		else if ((line == "sell") || (line == "SELL"))
		{
			cin >> ticker;
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					cin >> shares;
					if (!((*it)->sell(shares))) cout << "Sell unsuccessful" << endl;
					break;
				}
			}
		}
		else if ((line == "pricecheck") || (line == "PRICECHECK"))
		{
			cin >> ticker;
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					cin >> price;
					cout << (*it)->pricecheck(price) << endl;
					break;
				}
			}
		}
		else if ((line == "exit") || (line == "EXIT"))
		{
			break;
		}
		else
		{
			cout << "Invalid syntax" << endl;
		}
	}
	
	for (it = stocks->begin(); it != stocks->end(); delete *it, it++);
	delete stocks;
	return 0;
}
