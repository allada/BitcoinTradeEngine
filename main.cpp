/*
 * File:   main.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 4:33 PM
 */
#include <iostream>
#include <string>
#include "classes/Currency.h"
#include "classes/Order.h"
#include "classes/Market.h"
#include "classes/Transaction.h"
#include "classes/SocketServer.h"
#include "classes/DB.h"

#define BTC_USD 0
#define LTC_USD 1
#define BTC_LTC 2

HashTable Order::orders;
std::vector<Market *> Market::markets;
uint64_t Order::next_id = 1;
pthread_mutex_t Order::mutex;
uint64_t Transaction::next_id = 1;

using namespace std;

/*
 * Main Entry function
 */
int main(int argc, char** argv) {
	Order::init();

	Currency *usd = new Currency("usd");
	Currency *btc = new Currency("btc");
	Currency *ltc = new Currency("ltc");

	new Market(BTC_USD, usd, btc);
	new Market(LTC_USD, ltc, usd);
	new Market(BTC_LTC, btc, ltc);

	DB::loadOrders();

	SocketServer *server = new SocketServer(1197);
	server->start();
	Order::unInit();
	return 0;
}

