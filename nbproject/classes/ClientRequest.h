/*
 * File:   ClientRequest.h
 * Author: allada
 *
 * Created on December 7, 2013, 11:52 PM
 */

#ifndef CLIENTREQUEST_H
#define	CLIENTREQUEST_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "Thread.h"

class ClientRequest : public Thread{
public:
	int socket;

	ClientRequest(int requestSocket);

	void *threadFn();

	virtual ~ClientRequest();
private:

};

#endif	/* CLIENTREQUEST_H */

