#ifndef PRICE_LOG_SRC_STOCK_H_
#define PRICE_LOG_SRC_STOCK_H_

#include <string>
#include <ctime>
#include <string>

class Stock
{
	private:
	
	std::string ticker;
	std::time_t time;
	int shares;
	int price;
	
	public:
	
	Stock(std::string ticker_, int shares_, int price_);
	void buy(int shares_, int price_);
	bool sell(int shares_);
	float pricecheck(int price_);
	std::string get_ticker();
	std::time_t get_time();
	int get_shares();
	int get_price();
};

#endif
