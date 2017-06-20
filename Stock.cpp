#ifndef PRICE_LOG_SRC_STOCK_CPP_
#define PRICE_LOG_SRC_STOCK_CPP_

#include "Stock.h"

Stock::Stock(std::string ticker_, int shares_, int price_)
{
	ticker = ticker_;
	shares = shares_;
	price = price_;
}

void Stock::buy(int shares_, int price_)
{
	price = ((price * shares) + (price_ * shares_)) / (shares + shares_);
	shares += shares_;
}

bool Stock::sell(int shares_)
{
	if (shares_ > shares) return false;
	shares -= shares_;
	return true;
}

float Stock::pricecheck(int price_)
{
	return ((float)price_ - price) / price;
}

std::string Stock::get_ticker()
{
	return ticker;
}

std::time_t Stock::get_time()
{
	return time;
}

int Stock::get_shares()
{
	return shares;
}

int Stock::get_price()
{
	return price;
}

#endif
