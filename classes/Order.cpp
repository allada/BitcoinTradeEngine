/*
 * File:   Order.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:51 PM
 */

#include <stdlib.h>
#include <ctime>
#include <vector>

#include "Order.h"
#include "Market.h"


Order::Order() {
}

Order::Order(const Market &market, const u_int32_t account_id, const order_type_t direction, const u_int64_t qty, const u_int64_t price, const u_int64_t order_id, const u_int32_t timestamp, const order_status_t status) {
	this->order_id	= order_id;
	this->account_id=account_id;
	this->market	= market;
	this->direction	= direction;
	this->qty		= qty;
	this->price		= price;
	this->timestamp	= timestamp;
	this->status	= status;
}
Order::Order(const Market &market, const u_int32_t account_id, const order_type_t direction, const u_int64_t qty, const u_int64_t price) {
	this->market	= market;
	this->order_id	= Order::getNextId();
	this->account_id=account_id;
	this->direction	= direction;
	this->qty		= qty;
	this->price		= price;
	this->timestamp	= std::time(0);
	this->status	= ACTIVE;
}
Order::init(){
	if(this->status == ACTIVE || this->status == PARTIAL)
		Order::orders->Insert(this->order_id)->value = this;
}
Order::addTransaction(const Transaction &trans) {

}
Order::remove() {
	Order::orders->Delete(this->order_id);
}
Order::save() {

}

Order::~Order() {
	this->market->removeOrder(this);
	this->market = NULL;
}

static u_int64_t Order::getNextId() {
	return Order::next_id++;
}