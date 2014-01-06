/*
 * File:   DB.cpp
 * Author: allada
 *
 * Created on January 1, 2014, 4:51 PM
 */

#include "DB.h"
#include "mongo/bson/bsonobj.h"

mongo::DBClientConnection &getInstance() {
	static mongo::DBClientConnection instance;
	static bool ran = false;
	if(!ran) {
		ran = true;
		instance.connect("localhost");
	}
	return instance;
}
bool DB::saveOrder(Order *order) {
	mongo::BSONObjBuilder obj;
	obj.append("order_id",	(long long) order->order_id);
	obj.append("account_id",order->account_id);
	obj.append("market",	order->market);
	obj.append("direction",	order->direction);
	obj.append("qty",		(long long) order->qty);
	obj.append("price",		(long long) order->price);
	obj.append("timestamp",	order->timestamp);
	obj.append("status",	order->status);

	try {
		(getInstance()).insert("btct.orders", obj.obj());
	} catch(int e) {
		std::cout << "DB INSERT ERROR!!! " << e << "\n";
		return false;
	}
	return true;
}
