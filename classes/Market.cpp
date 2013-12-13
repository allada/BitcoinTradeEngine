/*
 * File:   Market.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */
#include "Market.h"

Market::Market(u_int8_t market_id, Currency *currency1, Currency *currency2) {
	this->market_id = market_id;
	this->currency1 = currency1;
	this->currency2 = currency2;
	this->buyOrders = new std::vector<Order *>;
	this->sellOrders = new std::vector<Order *>;
	Market::addMarket(this);
}

bool _addSellOrder(Market *market, Order *sellOrder) {
	Transaction *curTrans;
	Order *buyOrder;
	market->sellOrders->push_back(sellOrder);
	if(market->buyOrders->size()) {
		for(buyOrder = market->buyOrders->back(); buyOrder && (buyOrder->price >= sellOrder->price); buyOrder = market->buyOrders->back()) {
			int qty = (buyOrder->qty > sellOrder->qty)?sellOrder->qty:buyOrder->qty;
			curTrans = new Transaction(buyOrder, sellOrder, buyOrder->price, qty);
			if(!curTrans->process()) {
				std::cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << std::endl;
				delete curTrans;
				return false;
			}
			curTrans->process();
			delete curTrans;
			delete buyOrder;
		}
	}
	return true;
}
bool _addBuyOrder(Market *market, Order *buyOrder) {
	Transaction *curTrans;
	Order *sellOrder;
	market->buyOrders->push_back(buyOrder);
	if(market->sellOrders->size()) {
		for(buyOrder = market->sellOrders->back(); buyOrder && (buyOrder->price >= sellOrder->price); buyOrder = market->sellOrders->back()) {
			int qty = (buyOrder->qty > sellOrder->qty)?sellOrder->qty:buyOrder->qty;
			curTrans = new Transaction(buyOrder, sellOrder, sellOrder->price, qty);
			if(!curTrans->process()) {
				std::cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << std::endl;
				delete curTrans;
				return false;
			}
			curTrans->process();
			delete curTrans;
			delete sellOrder;
		}
	}
	return true;
}
bool Market::addOrder(Order *addOrder) {
	if(addOrder->direction == SELL) {
		if(!_addSellOrder(this, addOrder)) {
			std::cout << "Error Adding order " << addOrder->order_id << std::endl;;
			return false;
		}
	} else {
		if(!_addSellOrder(this, addOrder)) {
			std::cout << "Error Adding order " << addOrder->order_id << std::endl;;
			return false;
		}
	}
	return true;
	/*
	Transaction	*curTrans;
	Order		*sellOrder;
	Order		*buyOrder = addOrder;
	std::vector<Order *> *orderList;
	bool		reversed = false;

	if(addOrder->direction == SELL) {
		reversed = true;
		orderList = this->buyOrders;
		this->sellOrders->push_back(addOrder);
	} else {
		orderList = this->sellOrders;
		this->buyOrders->push_back(addOrder);
	}
	if(orderList->size()){
		sellOrder = orderList->back();
		while(sellOrder && (addOrder->price >= sellOrder->price)) {
			if(reversed) {
				// TODO: This is fugly as shit, please redo it.
				Order *tmpOrder;
				tmpOrder = sellOrder;
				sellOrder = buyOrder;
				buyOrder = sellOrder;
			}
			int qty = (sellOrder->qty > buyOrder->qty) ? buyOrder->qty : sellOrder->qty;
			curTrans = new Transaction(buyOrder, sellOrder, sellOrder->price, qty);
			if(!curTrans->save()){
				std::cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << std::endl;
				delete curTrans;
				return false;
			}
			bool needsRemoved = false;

			needsRemoved = false;
			sellOrder->qty -= qty;
			if(sellOrder->qty <= 0) {
				sellOrder->status = FILLED;
				needsRemoved = true;
			} else {
				sellOrder->status = PARTIAL;
			}
			if(!sellOrder->save()) {
				std::cout << "Error processing save order after transaction create " << sellOrder->order_id << std::endl;
				return false;
			}
			sellOrder->addTransaction(*curTrans);
			if(needsRemoved) {
				// Removal from vector done in destructor
				// Do not remove if it's going to be returned
				if(addOrder->order_id != sellOrder->order_id) {
					delete sellOrder;
				}
			}

			buyOrder->qty -= qty;
			if(buyOrder->qty <= 0) {
				buyOrder->status = FILLED;
				needsRemoved = true;
			} else {
				buyOrder->status = PARTIAL;
			}
			if(!buyOrder->save()) {
				std::cout << "Error processing save order after transaction create " << buyOrder->order_id << std::endl;
				return false;
			}
			buyOrder->addTransaction(*curTrans);
			if(needsRemoved) {
				// Removal from vector done in destructor
				// Do not remove if it's going to be returned
				if(addOrder->order_id != buyOrder->order_id) {
					delete buyOrder;
				}
			}

			delete curTrans;
			sellOrder = orderList->back();
		}
	}
	return true;
	 */
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
}

Market::~Market() {
	delete this->buyOrders;
	delete this->buyOrders;
}

void Market::addMarket(Market *market) {
	Market::markets.push_back(market);
}