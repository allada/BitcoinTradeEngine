/*
 * File:   Market.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */

#ifndef MARKET_H
#define	MARKET_H

class Market;

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <stdint.h>
//#include "ClassList.h"
#include "Currency.h"
#include "Transaction.h"
#include "Order.h"

class Order;

class Market {
public:
	static std::map<uint8_t, Market *> markets;

	uint16_t market_id;
	Currency *currency1;
	Currency *currency2;
	std::vector<Order *> *buyOrders;
	std::vector<Order *> *sellOrders;

	std::string getName() { return this->currency1->name + '_' + this->currency2->name; }
	Market(uint8_t market_id, Currency *currency1, Currency *currency2);

	bool addOrder(Order *addOrder);
	void removeOrder(Order *order);
	bool addBuyOrder(Order *order);
	bool addSellOrder(Order *order);

	static void addMarket(Market *market);

	virtual ~Market();
private:
};

#endif	/* MARKET_H */

