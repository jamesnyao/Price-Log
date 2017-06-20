#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

#include "Stock.h"

using namespace std;

int main(int argc, char **argv)
{
	string ticker, line;
	int shares, price, num_stocks, i;
	double price_f;
	list<Stock*>::iterator it;
	
	list<Stock*> *stocks = new list<Stock*>();
	
	ifstream log("stocks.log");
	if (log.is_open())
	{	
		for (num_stocks = 0; log >> ticker; num_stocks++)
		{
			log >> shares >> price;
			stocks->push_back(new Stock(ticker, shares, price));
		}
		log.close();
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
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		if ((line == "buy") || (line == "b"))
		{
			cin >> ticker >> shares >> price_f;
			transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					(*it)->buy(shares, (int)(price_f * 100));
					break;
				}
			}
			if (it == stocks->end())
			{
				stocks->push_back(new Stock(ticker, shares, (int)(price_f * 100)));
			}
		}
		else if ((line == "sell") || (line == "s"))
		{
			cin >> ticker >> shares;
			transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					if (!((*it)->sell(shares)))
					{
						cout << "Sell unsuccessful" << endl;
						break;
					}
					if ((*it)->get_shares() == 0) stocks->remove(*it);
					break;
				}
			}
		}
		else if ((line == "pricecheck") || (line == "pc"))
		{
			cin >> ticker >> price_f;
			transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
			for (it = stocks->begin(); it != stocks->end(); it++)
			{
				if ((*it)->get_ticker() == ticker)
				{
					cout << (*it)->pricecheck((int)(price_f * 100)) << '%' << endl;
					break;
				}
			}
			if (it == stocks->end())
			{
				cout << "Invalid ticker" << endl;
			}
		}
		else if ((line == "exit") || (line == "e") || (line == "x"))
		{
			break;
		}
		else
		{
			cout << "Invalid syntax" << endl;
		}
	}
	
	ofstream writeback("stocks.log");
	for (it = stocks->begin(); it != stocks->end(); it++)
	{
		writeback << (*it)->get_ticker() << ' ' << (*it)->get_shares() << ' ' << (*it)->get_price() << endl;
	}
	writeback.close();
	
	for (it = stocks->begin(); it != stocks->end(); delete *it, it++);
	delete stocks;
	return 0;
}
