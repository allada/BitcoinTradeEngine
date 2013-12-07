/*
 * File:   Market.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:44 PM
 */
#include <string>
#include "Currency.cpp"

#ifndef MARKET_H
#define	MARKET_H
class Market {
public:
	Currency currency1;
	Currency currency2;

	std::string getName() { return this->currency1->name + '_' + this->currency2->name; }
	Market(const Currency &currency1, const Currency &currency2);
	virtual ~Market();
private:

};

#endif	/* MARKET_H */

