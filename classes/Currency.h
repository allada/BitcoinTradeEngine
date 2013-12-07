/*
 * File:   Currency.h
 * Author: allada
 *
 * Created on December 6, 2013, 5:29 PM
 */
#define DECIMAL_PERCISION 10000000000
#include <string>

#ifndef CURRENCY_H
#define	CURRENCY_H
class Currency {
public:
	const std::string name;
	std::string getName() { return this->name; }
	Currency(const std::string &name);

	virtual ~Currency();
private:
	void setName(const std::string name) { this->name = name; }
};

#endif	/* CURRENCY_H */

