/*
 * File:   Order.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:51 PM
 */

#ifndef ORDER_H
#define	ORDER_H
/*
#include <boost/asio.hpp>
#include <cql/cql.hpp>
#include <cql/cql_connection.hpp>
#include <cql/cql_session.hpp>
#include <cql/cql_cluster.hpp>
#include <cql/cql_builder.hpp>
#include <cql/cql_result.hpp>
 */
enum order_type_t {
	SELL = 0,
	BUY
};
enum order_status_t {
	CANCELLED = 0,
	FILLED,
	ACTIVE,
	PARTIAL
};

class Order;

#include <stdlib.h>
#include <ctime>
#include <vector>
#include <pthread.h>

#include "Transaction.h"
#include "Market.h"
#include "HashTable.h"
class HashTable;

class Order {
public:
	uint64_t		order_id;
	uint32_t		account_id;
	Market			*market;
	order_type_t	direction;
	uint64_t		qty;
	uint64_t		price;
	uint32_t		timestamp;
	order_status_t	status;

	std::vector<Transaction *>	transactions;

	Order(Market *market, const uint32_t account_id, const order_type_t direction, const uint64_t qty, const uint64_t price, const uint64_t order_id, const uint32_t timestamp, const order_status_t status);
	Order(Market *market, const uint32_t account_id, const order_type_t direction, const uint64_t qty, const uint64_t price);
	virtual ~Order();

	void addTransaction(Transaction *trans);
	bool remove();
	bool save();

	static Order *getOrder(int order_id);
	static void lock();
	static void unlock();
	static void init();
	static void unInit();

	static HashTable orders;
	static uint32_t next_id;
	static pthread_mutex_t mutex;
	static uint32_t getNextId();
private:
};

#endif	/* ORDER_H */

