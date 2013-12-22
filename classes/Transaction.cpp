/*
 * File:   Transaction.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 8:53 PM
 */

#include "Transaction.h"
#include "ClientRequest.h"

Transaction::Transaction(Order *buyOrder, Order *sellOrder, uint64_t price, uint64_t qty, uint64_t transaction_id, uint32_t timestamp) {
	this->buyOrder			= buyOrder;
	this->sellOrder			= sellOrder;
	this->price				= price;
	this->qty				= qty;
	this->transaction_id	= transaction_id;
	this->timestamp			= timestamp;
}
Transaction::Transaction(Order *buyOrder, Order *sellOrder, uint64_t price, uint64_t qty) {
	this->buyOrder			= buyOrder;
	this->sellOrder			= sellOrder;
	this->price				= price;
	this->qty				= qty;
	this->transaction_id	= Transaction::getNextId();
	this->timestamp			= std::time(0);
}
#define CHANGE_ORDER_STATUS(order) \
	if(!order->qty) { \
		order->status = FILLED; \
	} else if(order->status != PARTIAL) { \
		order->status = PARTIAL; \
	}
bool Transaction::process() {
	if(!this->save()){
		std::cout << "Error processing transaction between the following order id, " << this->buyOrder->order_id << " and " << this->sellOrder->order_id << std::endl;
		return false;
	}
	this->buyOrder->addTransaction(this);
	this->sellOrder->addTransaction(this);
	//printf("Buy was %u, sell was %u\n", this->buyOrder->qty, this->sellOrder->qty);
	//printf("Buy now %u, sell now %u\n", this->buyOrder->qty - this->qty, this->sellOrder->qty - this->qty);

	this->buyOrder->qty -= this->qty;
	this->sellOrder->qty -= this->qty;

	CHANGE_ORDER_STATUS(this->buyOrder);
	CHANGE_ORDER_STATUS(this->sellOrder);

	this->buyOrder->save();
	this->sellOrder->save();
	return true;
}
bool Transaction::save() {
	return true;
}
Transaction::~Transaction() {
}

uint64_t Transaction::getNextId() {
	return Transaction::next_id++;
}