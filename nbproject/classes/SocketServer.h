/*
 * File:   SocketServer.h
 * Author: allada
 *
 * Created on December 7, 2013, 4:52 PM
 */

#ifndef SOCKETSERVER_H
#define	SOCKETSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <vector>
#include "Thread.h"

class SocketServer{
public:
	SocketServer(const char *path);
	static void exit(int signum);

	void start();
	static std::vector<SocketServer *> instances;

	virtual ~SocketServer();
private:
	int sock;
};

#endif	/* SOCKETSERVER_H */

