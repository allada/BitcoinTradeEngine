/*
 * File:   Transaction.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 8:53 PM
 */

#include "Transaction.h"

Transaction::Transaction(Order &buyOrder, Order &sellOrder, u_int64_t price, u_int64_t qty, u_int64_t transaction_id, u_int32_t timestamp) {
	this->buyOrder			= buyOrder;
	this->sellOrder			= sellOrder;
	this->price				= price;
	this->qty				= qty;
	this->transaction_id	= transaction_id;
	this->timestamp			= timestamp;
}
Transaction::Transaction(Order &buyOrder, Order &sellOrder, u_int64_t price, u_int64_t qty) {
	this->buyOrder			= buyOrder;
	this->sellOrder			= sellOrder;
	this->price				= price;
	this->qty				= qty;
	this->transaction_id	= Transaction::getNextId();
	this->timestamp			= std::time(0);
}
Transaction::save() {

}
Transaction::~Transaction() {
}

static u_int64_t Transaction::getNextId() {
	return Transaction::next_id++;
}