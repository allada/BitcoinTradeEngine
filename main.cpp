/*
 * File:   main.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 4:33 PM
 */
#include <iostream>
#include <string>
#include <map>
#include <stdint.h>
#include "classes/Currency.h"
#include "classes/Order.h"
#include "classes/Market.h"
#include "classes/Transaction.h"
#include "classes/SocketServer.h"
#include "classes/DB.h"

HashTable Order::orders;
std::map<uint8_t, Market *> Market::markets;
std::map<uint8_t, Currency *> Currency::currencies;
uint64_t Order::next_id = 1;
pthread_mutex_t Order::mutex;
uint64_t Transaction::next_id = 1;

using namespace std;

/*
 * Main Entry function
 */
int main(int argc, char** argv) {
	Order::init();

	DB::loadCurrencies();
	DB::loadMarkets();
	DB::loadOrders();

	SocketServer *server = new SocketServer(1197);
	server->start();
	Order::unInit();
	return 0;
}

