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
 * ...                            |* * * * * * * * * * * * * * * *       + 160
 *
 */
ClientRequest::ClientRequest(int requestSocket) {
	this->socket = requestSocket;
}

void *ClientRequest::threadFn() {
	unsigned char buffer[20];
	int n, len = 0;

	bzero(buffer,20);
	do {
		len += n = read(this->socket, buffer, 20);
		if(n < 0) {
			perror("ERROR reading from socket");
			exit(1);
		}
		if(len >= 19) {
			break;
		}
		usleep(10);
	} while(true);

	bool type = (buffer[0] >> 0x7) & 0x1;
	uint16_t market_id = buffer[0] & ~0x80;
	if(market_id > Market::markets.size() - 1) {
		perror("No market with that id");
		exit(1);
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

		Order *o = new Order(market, account_num, direction, qty, price);
		char order_id[4] = {
			(char) ((o->order_id >> 24) & 0xFF),
			(char) ((o->order_id >> 16) & 0xFF),
			(char) ((o->order_id >> 8) & 0xFF),
			(char) (o->order_id & 0xFF)
		};
		market->addOrder(o);

		Order::unlock();

		write(this->socket, order_id, sizeof(char) * 4);
	} else {
		// Is Cancel Order
	}
	close(this->socket);
	this->socket = 0;
	return (void *) NULL;
}

ClientRequest::~ClientRequest() {
	printf("Closing");
	if(this->socket) {
		close(this->socket);
	}
}

