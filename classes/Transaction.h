/*
 * File:   Transaction.h
 * Author: allada
 *
 * Created on December 6, 2013, 8:53 PM
 */
#ifndef TRANSACTION_H
#define	TRANSACTION_H

class Transaction;

#include "Order.h"

class Transaction {
public:
	uint64_t	transaction_id;
	Order		*buyOrder;
	Order		*sellOrder;
	uint64_t	price;
	uint64_t	qty;
	uint32_t	timestamp;

	Transaction(Order *buyOrder, Order *sellOrder, uint64_t price, uint64_t qty, uint64_t transaction_id, uint32_t timestamp);
	Transaction(Order *buyOrder, Order *sellOrder, uint64_t price, uint64_t qty);
	virtual ~Transaction();

	bool process();
	bool save();

	/*static Transaction getTransaction(int transaction_id){

	}*/
private:
	static uint64_t next_id;
	static uint64_t getNextId();
	void init();
};

#endif	/* TRANSACTION_H */

