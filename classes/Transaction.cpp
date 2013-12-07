/*
 * File:   Transaction.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 8:53 PM
 */

#include "Transaction.h"

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
bool Transaction::save() {
	return true;
}
Transaction::~Transaction() {
}

uint64_t Transaction::getNextId() {
	return Transaction::next_id++;
}