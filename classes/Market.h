/*
 * File:   Market.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */

#ifndef MARKET_H
#define	MARKET_H
#define ORDER_SORT_GROUP_COUNT 20

class Market;

#include <vector>
#include <iostream>
#include <string>
//#include "ClassList.h"
#include "Currency.h"
#include "Transaction.h"
#include "Order.h"

class Order;

class Market {
public:
	static std::vector<Market> markets;

	Currency *currency1;
	Currency *currency2;
	std::vector<Order *> buyOrders;
	std::vector<Order *> sellOrders;
	u_int64_t buyOrderGroups[ORDER_SORT_GROUP_COUNT];
	u_int64_t sellOrderGroups[ORDER_SORT_GROUP_COUNT];

	std::string getName() { return this->currency1->name + '_' + this->currency2->name; }
	Market(Currency *currency1, Currency *currency2);

	bool addOrder(Order *addOrder);
	void removeOrder(Order *order);

	static void addMarket(Market *market);

	virtual ~Market();
private:
};

#endif	/* MARKET_H */

