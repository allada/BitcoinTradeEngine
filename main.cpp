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

HashTable *Order::orders = new HashTable;
uint32_t Order::next_id = 0;
uint64_t Transaction::next_id = 0;

using namespace std;

/*
 * Main Entry function
 */
int main(int argc, char** argv) {

	return 0;
}

