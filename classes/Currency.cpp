/*
 * File:   Currency.cpp
 * Author: allada
 *
 * Created on December 6, 2013, 5:29 PM
 */

#include <stdlib.h>

#include "Currency.h"

Currency::Currency(const u_int8_t id, const std::string &name) {
	this->id = id;
	this->name = name;
	Currency::addCurrency(this);
}

Currency::~Currency() {
}
void Currency::addCurrency(Currency *currency) {
	Currency::currencies.insert(currency.id, currency);
}

