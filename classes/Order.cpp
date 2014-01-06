/*
 * File:   Order.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:51 PM
 */

#include "Order.h"
#include "mongo/client/dbclient.h"

Order::Order(Market *market, const uint32_t account_id, const order_type_t direction, const uint64_t qty, const uint64_t price, const uint64_t order_id, const uint32_t timestamp, const order_status_t status) {
	this->order_id	= order_id;
	this->account_id=account_id;
	this->market	= market;
	this->direction	= direction;
	this->qty		= qty;
	this->price		= price;
	this->timestamp	= timestamp;
	this->status	= status;
	if(this->status == ACTIVE || this->status == PARTIAL) {
		Order::orders.Insert(this->order_id)->value = this;
	}
}
Order::Order(Market *market, const uint32_t account_id, const order_type_t direction, const uint64_t qty, const uint64_t price) {
	this->market	= market;
	this->order_id	= Order::getNextId();
	this->account_id=account_id;
	this->direction	= direction;
	this->qty		= qty;
	this->price		= price;
	this->timestamp	= std::time(0);
	this->status	= ACTIVE;
	Order::orders.Insert(this->order_id)->value = this;
}
void Order::addTransaction(Transaction *trans) {

}
bool Order::remove() {
	Order::orders.Delete(this->order_id);
	return true;
}
bool Order::save() {
	return DB::saveOrder(this);
}

Order::~Order() {
	this->market->removeOrder(this);
	this->market = NULL;
}

Order *Order::getOrder(int order_id){
	return Order::orders.Lookup(order_id)->value;
};
uint32_t Order::getNextId() {
	return Order::next_id++;
}
void Order::lock() {
	pthread_mutex_lock(&Order::mutex);
}
void Order::unlock() {
	pthread_mutex_unlock(&Order::mutex);
}
void Order::init() {
	pthread_mutex_init(&Order::mutex, NULL);
}
void Order::unInit() {
	pthread_mutex_destroy(&Order::mutex);
}