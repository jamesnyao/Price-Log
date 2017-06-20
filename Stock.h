#ifndef PRICE_LOG_SRC_STOCK_H_
#define PRICE_LOG_SRC_STOCK_H_

#include <string>
#include <string>

class Stock
{
	private:
	
	std::string ticker;
	int shares;
	int price;
	
	public:
	
	Stock(std::string ticker_, int shares_, int price_);
	void buy(int shares_, int price_);
	bool sell(int shares_);
	float pricecheck(int price_);
	std::string get_ticker();
	int get_shares();
	int get_price();
};

#endif
