/*
 * File:   SocketServer.cpp
 * Author: allada
 *
 * Created on December 7, 2013, 4:52 PM
 */

#include "SocketServer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#define MAX_THREADS 31
bool running = false;
bool runnable = false;
ThreadPool* threadPool;
void SocketServer::exit(int signum) {
	if(signum == SIGTERM) {
		printf("Destructing SocketServers\n");
		running = false;
	}
	return;
}
SocketServer::SocketServer(int port) {
	threadPool = new ThreadPool(MAX_THREADS);
	int ret = threadPool->initialize_threadpool();
	if(ret == -1) {
		std::cerr << "Failed to initialize thread pool!" << std::endl;
		return;
	}

	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	signal(SIGTERM, SocketServer::exit);
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("0.0.0.0");

	if(this->sock < 0) {
        perror("ERROR opening socket");
        return;
    }
	if(bind(this->sock, (const struct sockaddr *) &server, (uint32_t) sizeof(server)) < 0) {
		perror("ERROR binding stream socket");
		return;
	}
	if(listen(this->sock, MAX_THREADS) < 0){
		perror("Error listening to socket");
		return;
	}
	runnable = true;
}

void SocketServer::start() {
	int requestSock;
	fd_set fd, fd_master;
	timeval tv;
	if(!runnable) {
		return;
	}
	FD_ZERO(&fd_master);
    FD_ZERO(&fd);
    FD_SET(this->sock, &fd_master);

    tv.tv_sec = 1;
    tv.tv_usec = 0;
	memcpy(&fd, &fd_master, sizeof(fd_master));
	running = true;
	int sel;
	while(running && (sel = select(this->sock + 1, &fd, NULL, NULL, &tv)) >= 0) {
		if(sel) {
			//printf("%u\n", sel);
			requestSock = accept(this->sock, NULL, NULL);
			if(requestSock < 0) {
				perror("ERROR on accept");
				running = false;
				continue;
			}

			// No need to delete cr because it is deleted in the thread class when finished.
			ClientRequest *cr = new ClientRequest();
			cr->socket = requestSock;
			threadPool->add_task(cr);
		}
		memcpy(&fd, &fd_master, sizeof(fd_master));
	}
	close(this->sock);
	this->sock = 0;
}

SocketServer::~SocketServer() {
	try{
		close(this->sock);
	}catch (int e){}
}

