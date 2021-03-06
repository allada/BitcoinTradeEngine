/*
 * File:   ClientRequest.cpp
 * Author: allada
 *
 * Created on December 7, 2013, 11:52 PM
 */

#include "ClientRequest.h"
#include "Order.h"
#include "Market.h"
#include <unistd.h>
#include <stdio.h>

#if defined(__linux__)
#  include <endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__)
#  include <sys/endian.h>
#elif defined(__OpenBSD__)
#  include <sys/types.h>
#  define be64toh(x) betoh64(x)
#elif defined(__APPLE__)
#  define be64toh(x) x
#endif
#define ADD_ORDER 0
#define REMOVE_ORDER 1
/*
 * Data structure
 *
 * ADD ORDER
 * 0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7
 * T|   MARKET          MARKET    |          ACCOUNT NUMBER          ... + 0
 * ...                            |                QTY               ... + 32
 * ...                                                               ... + 64
 * ...                            |               PRICE              ... + 96
 * ...                                                               ... + 128
 * ...                            |D|* * * * * * * * * * * * * * *       + 160
 *
 *
 * CANCEL ORDER
 * 0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7|0 1 2 3 4 5 6 7
 * T|   MARKET          MARKET    |              ORDER NUM           ... + 0
 * ...                                                               ... + 32
 * ...                            |* * * * * * * * * * * * * * * *       + 160
 *
 */
void ClientRequest::run() {
	unsigned char buffer[20];
	int n, len = 0;

	bzero(buffer,20);
	do {
		len += n = read(this->socket, buffer, 20);
		if(n < 0) {
			perror("ERROR reading from socket");
			return;
		}
		if(n == 0){
			perror("Socket closed by client");
			return;
		}
		if(len >= 20) {
			break;
		}
		usleep(10);
	} while(true);

	bool type = (buffer[0] >> 0x7) & 0x1;
	uint16_t market_id = buffer[0] & ~0x80;
	if(market_id > Market::markets.size() - 1) {
		perror("No market with that id");
		return;
	}
	Market *market = Market::markets[market_id];
	if(type == ADD_ORDER) {
		// Is Add Order
		uint32_t account_num = buffer[1];
		account_num <<= 8;
		account_num |= buffer[2];

		uint64_t qty = buffer[3];
		qty <<= 8;
		qty |= buffer[4];
		qty <<= 8;
		qty |= buffer[5];
		qty <<= 8;
		qty |= buffer[6];
		qty <<= 8;
		qty |= buffer[7];
		qty <<= 8;
		qty |= buffer[8];
		qty <<= 8;
		qty |= buffer[9];
		qty <<= 8;
		qty |= buffer[10];

		uint64_t price = buffer[11];
		price <<= 8;
		price |= buffer[12];
		price <<= 8;
		price |= buffer[13];
		price <<= 8;
		price |= buffer[14];
		price <<= 8;
		price |= buffer[15];
		price <<= 8;
		price |= buffer[16];
		price <<= 8;
		price |= buffer[17];
		price <<= 8;
		price |= buffer[18];

		order_type_t direction = (order_type_t) ((buffer[19] >> 7) & 0x1);

		Order::lock();

		Order *o = new Order(market, account_num, direction, qty, qty, price);
		char order_id[8] = {
			(char) ((o->order_id >> 56) & 0xFF),
			(char) ((o->order_id >> 48) & 0xFF),
			(char) ((o->order_id >> 40) & 0xFF),
			(char) ((o->order_id >> 32) & 0xFF),
			(char) ((o->order_id >> 24) & 0xFF),
			(char) ((o->order_id >> 16) & 0xFF),
			(char) ((o->order_id >> 8) & 0xFF),
			(char) (o->order_id & 0xFF)
		};
		market->addOrder(o);
		if(o->qty == 0) {
			delete o;
		}

		Order::unlock();

		try{
			//std::printf("%llu\n", order_id);
			write(this->socket, order_id, 8);
		} catch (int e) {
			perror("Some socket error probably?\n");
			// do nothing maybe socket closed?
		}
	} else {
		// Is Cancel Order
		uint64_t order_id = buffer[0];
		order_id <<= 8;
		order_id |= buffer[1];
		order_id <<= 8;
		order_id |= buffer[2];
		order_id <<= 8;
		order_id |= buffer[3];
		order_id <<= 8;
		order_id |= buffer[4];
		order_id <<= 8;
		order_id |= buffer[5];
		order_id <<= 8;
		order_id |= buffer[6];
		order_id <<= 8;
		order_id |= buffer[7];
	}
	close(this->socket);
	this->socket = 0;
	return;
}

ClientRequest::~ClientRequest() {
	if(this->socket) {
		close(this->socket);
	}
	this->socket = 0;
}
