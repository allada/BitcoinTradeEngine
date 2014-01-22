/*
 * File:   DB.cpp
 * Author: allada
 *
 * Created on January 1, 2014, 4:51 PM
 */

#include "DB.h"
#include "mongo/bson/bsonobj.h"
#include "Order.h"
#include "Market.h"
#include "Transaction.h"

#ifndef __APPLE__
#include "/root/btct.password"
#endif

mongo::DBClientConnection &getInstance() {
	static mongo::DBClientConnection instance;
	static bool ran = false;
	if(!ran) {
		ran = true;
#ifdef __APPLE__
		instance.connect("localhost");
#else
		instance.connect(MONGO_IP);
		instance->auth(BSON("user" << MONGO_USER <<
                "userSource" << MONGO_SOURCE <<
                "pwd" << MONGO_PASSWORD <<
                "mechanism" << MONGO_MECHANISM));
#endif
	}
	return instance;
}
bool DB::saveOrder(Order *order) {
	try {
		//getInstance().insert("btct.orders", obj.obj());
		getInstance().update("btct.orders", QUERY(
				"_id"			<< (long long) order->order_id
		), BSON(
				"_id"			<< (long long) order->order_id <<
				"account_id"	<< order->account_id <<
				"market_id"		<< order->market->market_id <<
				"direction"		<< (bool) order->direction <<
				"qty"			<< (long long) order->qty <<
				"orig_qty"		<< (long long) order->orig_qty <<
				"price"			<< (long long) order->price <<
				"timestamp"		<< order->timestamp <<
				"status"		<< (u_int8_t) order->status
		), true, false);
		std::string err = getInstance().getLastError();
		if(!err.empty()){
			std::cout << "DB INSERT ERROR!!! " << getInstance().getLastError() << "\n";
		}
	} catch(int e) {
		std::cout << "DB INSERT ERROR!!! " << e << "\n";
		return false;
	}
	return true;
}
bool DB::saveTransaction(Transaction *transaction) {
	mongo::BSONObjBuilder obj;
	obj.append("_id",			(long long) transaction->transaction_id);
	obj.append("buy_order_id",	(long long) transaction->buyOrder->order_id);
	obj.append("sell_order_id",	(long long) transaction->sellOrder->order_id);
	obj.append("price",			(long long) transaction->price);
	obj.append("qty",			(long long) transaction->qty);
	obj.append("timestamp",		transaction->timestamp);
	try {
		getInstance().insert("btct.transactions", obj.obj());
		std::string err = getInstance().getLastError();
		if(!err.empty()){
			std::cout << "DB INSERT ERROR!!! " << getInstance().getLastError() << "\n";
		}
	} catch(int e) {
		std::cout << "DB INSERT ERROR!!! " << e << "\n";
		return false;
	}
	return true;
}
void DB::loadOrders() {
	mongo::BSONObj o_max = getInstance().findOne("btct.orders", mongo::Query().sort("_id", -1));
	mongo::BSONObj t_max = getInstance().findOne("btct.transactions", mongo::Query().sort("_id", -1));
	uint64_t o_next_id = o_max.getField("_id").Long();
	if(o_next_id <= 1000){
		o_next_id = 1000;
	}
	uint64_t t_next_id = t_max.getField("_id").Long();
	if(t_next_id <= 1){
		t_next_id = 1;
	}
	Order::next_id = o_next_id + 1;
	Transaction::next_id = t_next_id + 1;

	std::auto_ptr<mongo::DBClientCursor> cursor = getInstance().query("btct.orders", QUERY("qty" << mongo::GT << 0));
	int order_count = 0;
	printf("Loading orders...\n");
	while (cursor->more()) {
		mongo::BSONObj p = cursor->next();
		Market *market = Market::markets[p.getIntField("market_id")];
		Order *o = new Order(
				market,
				(const uint32_t) p.getIntField("account_id"),
				(const order_type_t) p.getBoolField("direction"),
				(const uint64_t) p.getField("qty").Long(),
				(const uint64_t) p.getField("orig_qty").Long(),
				(const uint64_t) p.getField("price").Long(),
				(const uint64_t) p.getField("_id").Long(),
				(const uint32_t) p.getIntField("timestamp"),
				(const order_status_t) p.getIntField("status"));
		market->addOrder(o);
		order_count++;
	}
	printf("Loaded %u orders\n", order_count);
	printf("Biggest order number: %u\n", o_next_id);
}