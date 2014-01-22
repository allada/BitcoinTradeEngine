/*
 * File:   DB.h
 * Author: allada
 *
 * Created on January 1, 2014, 4:51 PM
 */

#ifndef DB_H
#define	DB_H
#include "client/dbclient.h"
#include "Order.h"
#include "Transaction.h"
class DB {
public:
	static bool saveOrder(Order *order);
	static bool saveTransaction(Transaction *transaction);
	static void loadOrders();
private:
	DB();
};

#endif	/* DB_H */

