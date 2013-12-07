/*
 * File:   Transaction.h
 * Author: allada
 *
 * Created on December 6, 2013, 8:53 PM
 */

#ifndef TRANSACTION_H
#define	TRANSACTION_H

#include "Order.h"

class Transaction {
public:
	u_int64_t	transaction_id;
	Order		buyOrder;
	Order		sellOrder;
	u_int64_t	price;
	u_int64_t	qty;
	u_int32_t	timestamp;

	Transaction(Order *BuyOrder, Order *SellOrder, u_int64_t price, u_int64_t qty, u_int64_t transaction_id, u_int32_t timestamp);
	Transaction(Order *BuyOrder, Order *SellOrder, u_int64_t price, u_int64_t qty);
	virtual ~Transaction();

	save();

	static Transaction getTransaction(int transaction_id){

	}
private:
	static u_int64_t next_id;
	static u_int64_t Order::getNextId();
	Transaction::init();
};

#endif	/* TRANSACTION_H */

