/*
 * File:   Currency.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:29 PM
 */
#define DECIMAL_PERCISION 10000000000

#ifndef CURRENCY_H
#define	CURRENCY_H

class Currency;

#include <string>
#include <vector>
#include <map>

class Currency {
public:
	static std::map<u_int8_t, Currency *> currencies;
	u_int8_t id;
	std::string name;

	Currency(const u_int8_t id, const std::string &name);

	virtual ~Currency();
	static void addCurrency(Currency *currency);
private:
};

#endif	/* CURRENCY_H */

