/*
 * File:   Market.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */
#include "Market.h"
#include <sys/param.h>
#include <stdio.h>

Market::Market(uint8_t market_id, Currency *currency1, Currency *currency2) {
	this->market_id		= market_id;
	this->currency1		= currency1;
	this->currency2		= currency2;
	this->buyOrders		= new std::vector<Order *>;
	this->sellOrders	= new std::vector<Order *>;
	Market::addMarket(this);
}
bool Market::addBuyOrder(Order *order) {
	Order *o;
	uint32_t i = Market::buyOrders->size();
	for (; i > 0; i--) {
		o = Market::buyOrders->at(i-1);
		if(o->price <= order->price) {
			break;
		}
	}
	Market::buyOrders->insert(Market::buyOrders->begin() + i, order);
	return true;
}
bool Market::addSellOrder(Order *order) {
	Order *o;
	uint32_t i = Market::sellOrders->size();
	for (; i > 0; i--) {
		o = Market::sellOrders->at(i-1);
		if(o->price >= order->price) {
			break;
		}
	}
	Market::sellOrders->insert(Market::sellOrders->begin() + i, order);
	return true;
}
bool _addSellOrder(Market *market, Order *sellOrder) {
	Transaction *curTrans;
	Order *buyOrder;
	market->addSellOrder(sellOrder);
	bool trans_made = false;
	if(market->buyOrders->size()) {
		for(buyOrder = market->buyOrders->back(); market->buyOrders->size() && sellOrder->qty != 0 && (buyOrder->price >= sellOrder->price); buyOrder = market->buyOrders->back()) {
			uint64_t qty = (buyOrder->qty > sellOrder->qty)?sellOrder->qty:buyOrder->qty;
			curTrans = new Transaction(buyOrder, sellOrder, buyOrder->price, qty);
			trans_made = true;
			if(!curTrans->process()) {
				std::cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << std::endl;
				delete curTrans;
				return false;
			}
			delete curTrans;
			if(buyOrder->qty == 0) {
				delete buyOrder;
			}
		}
	}
	if(!trans_made) {
		sellOrder->save();
	}
	return true;
}
bool _addBuyOrder(Market *market, Order *buyOrder) {
	Transaction *curTrans;
	Order *sellOrder;
	market->addBuyOrder(buyOrder);
	bool trans_made = false;
	if(market->sellOrders->size()) {
		for(sellOrder = market->sellOrders->back(); market->sellOrders->size() && buyOrder->qty != 0 && (buyOrder->price >= sellOrder->price); sellOrder = market->sellOrders->back()) {
			uint64_t qty = (buyOrder->qty > sellOrder->qty)?sellOrder->qty:buyOrder->qty;
			curTrans = new Transaction(buyOrder, sellOrder, sellOrder->price, qty);
			trans_made = true;
			if(!curTrans->process()) {
				std::cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << std::endl;
				delete curTrans;
				return false;
			}
			delete curTrans;
			if(sellOrder->qty == 0) {
				delete sellOrder;
			}
		}
	}
	if(!trans_made) {
		buyOrder->save();
	}
	return true;
}
std::time_t lasttime;
bool Market::addOrder(Order *addOrder) {
	if(!lasttime){
		lasttime = std::time(0);
	}
	if(lasttime + 2 < std::time(0)){
		printf("Num of orders: %u\n", this->sellOrders->size() + this->buyOrders->size() );
		//printf("Total orders processed: %u\n", Order::next_id);
		lasttime = std::time(0);
		/*
		for(uint32_t j = 0; j < addOrder->market->sellOrders->size(); j++) {
			printf("S %llu -> %u\n", addOrder->market->sellOrders->at(j)->price, addOrder->market->sellOrders->at(j)->qty);
		}

		for(uint32_t j = addOrder->market->buyOrders->size(); j-- > 0;) {
			printf("B %llu -> %u\n", addOrder->market->buyOrders->at(j)->price, addOrder->market->buyOrders->at(j)->qty);
		}*/
	}
	if(addOrder->direction == SELL) {
		if(!_addSellOrder(this, addOrder)) {
			std::cout << "Error Adding order " << addOrder->order_id << std::endl;;
			return false;
		}
	} else {
		if(!_addBuyOrder(this, addOrder)) {
			std::cout << "Error Adding order " << addOrder->order_id << std::endl;;
			return false;
		}
	}
	return true;
}
void Market::removeOrder(Order *order) {
	std::vector<Order *> *orderList;
	if(order->direction == SELL) {
		orderList = this->sellOrders;
	} else {
		orderList = this->buyOrders;
	}
	for (unsigned int i = orderList->size(); i-- > 0; ) {
		if(orderList->at(i)->order_id == order->order_id) {
			orderList->erase(orderList->begin() + i);
			return;
		}
	}
	// should never reach here
	return;
}

Market::~Market() {
	delete this->buyOrders;
	delete this->buyOrders;
}

void Market::addMarket(Market *market) {
	Market::markets[market->market_id] = market;
}