/*
 * File:   Order.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:51 PM
 */

#ifndef ORDER_H
#define	ORDER_H

#include "HashTable.h"
#include "Transaction.h"

enum order_type_t {
	SELL = 0,
	BUY
} order_type;
enum order_status_t {
	CANCELLED = 0,
	FILLED,
	ACTIVE,
	PARTIAL
} order_status;

class Order {
public:
	u_int64_t		order_id;
	u_int32_t		account_id;
	Market			market;
	order_type_t	direction;
	u_int64_t		qty;
	u_int64_t		price;
	u_int32_t		timestamp;
	order_status_t	status;

	std::vector<Transaction>	transactions;

	Order(const Market &market, const order_type_t direction, const u_int64_t qty, const u_int64_t price, const int order_id, const u_int32_t timestamp, const order_status_t status);
	Order(const Market &market, const order_type_t direction, const u_int64_t qty, const u_int64_t price);
	virtual ~Order();

	void addTransaction(const Transaction &trans);
	bool remove();
	bool save();

	static Order getOrder(int order_id){
		return Order::orders->Lookup(order_id);
	}
private:
	static HashTable orders;
	static u_int64_t next_id;
	static u_int64_t Order::getNextId();
	Order::init();
};

#endif	/* ORDER_H */

