/*
 * File:   DB.h
 * Author: allada
 *
 * Created on January 1, 2014, 4:51 PM
 */

#ifndef DB_H
#define	DB_H
#include "mongo/client/dbclient.h"
#include "Order.h"
class DB {
public:
	static bool saveOrder(Order *order);
private:
	DB();
};

#endif	/* DB_H */

