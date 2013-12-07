/*
 * File:   Market.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */

#include <vector>
#include <iostream>

#include "Market.h"
#include "Transaction.h"

Market::Market(const Currency &currency1, const Currency &currency2) {
	this->currency1 = currency1;
	this->currency2 = currency2;
	Market::addMarket(this);
}

bool Market::addOrder(const Order &addOrder) {
	Transaction	*curTrans;
	Order		&sellOrder;
	Order		&buyOrder;
	std::vector<Order> &orderList;
	bool		reversed = false;
	if(addOrder->direction == SELL) {
		reversed = true;
		orderList = &(this->buyOrders);
	} else {
		buyOrder = &addOrder;
		orderList = &(this->sellOrders);
	}
	while(addOrder->price >= (sellOrder = orderList->back())->price) {
		if(reversed) {
			// TODO: This is fugly as shit, please redo it.
			Order &tmpOrder;
			tmpOrder = &sellOrder;
			sellOrder = &buyOrder;
			buyOrder = &sellOrder;
		}
		int qty = (sellOrder.qty > buyOrder->qty) ? buyOrder->qty : sellOrder.qty;
		curTrans = new Transaction(buyOrder, sellOrder, sellOrder.price, qty);
		if(!curTrans.save()){
			cout << "Error processing transaction between the following order id, " << buyOrder->order_id << " and " << sellOrder->order_id << endl;
			delete curTrans;
			return false;
		}
		bool needsRemoved = false;

		buyOrder->qty -= qty;
		if(buyOrder->qty <= 0) {
			buyOrder->status = FILLED;
			needsRemoved = true;
		} else {
			buyOrder->status = PARTIAL;
		}
		if(buyOrder->save()) {
			cout << "Error processing save order after transaction create " << buyOrder->order_id << endl;
			return false;
		}
		buyOrder->addTransaction(curTrans);
		if(needsRemoved) {
			delete buyOrder;
		}

		needsRemoved = false
		sellOrder.qty -= qty;
		if(sellOrder.qty <= 0) {
			sellOrder.status = FILLED;
			needsRemoved = true;
		} else {
			sellOrder.status = PARTIAL;
		}
		if(sellOrder.save()) {
			cout << "Error processing save order after transaction create " << sellOrder.order_id << endl;
			return false;
		}
		sellOrder.addTransaction(curTrans);
		if(needsRemoved) {
			delete buyOrder;
		}
		delete curTrans;
	}
}
void Market::removeOrder(const Order &order) {
	std::vector<Order> &orderList;
	if(order->direction == SELL) {
		orderList = &this->sellOrders;
	} else {
		orderList = &this->buyOrders;
	}
	for(std::vector<Order>::size_type i = orderList.size() - 1; i != 0; i--) {
		if(orderList[i] == order) {
			orderList.erase(i);
			return;
		}
	}
}
static void Market::addMarket(const Market &market) {
	this->markets->push_back(market);
}


Market::~Market() {

}

