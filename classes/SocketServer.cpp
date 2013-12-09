/*
 * File:   SocketServer.cpp
 * Author: allada
 *
 * Created on December 7, 2013, 4:52 PM
 */

#include "SocketServer.h"
#include "ClientRequest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
bool running = false;
bool runnable = false;
char *master_path;
void SocketServer::exit(int signum) {
	if(signum == SIGTERM) {
		printf("Destructing SocketServers\n");
		SocketServer::instances.clear();
		running = false;
	}
	return;
}

SocketServer::SocketServer(const char *path) {
	struct sockaddr_un server;
	signal(SIGTERM, SocketServer::exit);
	this->sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(this->sock < 0) {
        perror("ERROR opening socket");
        return;
    }
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, path);
	master_path = (char *) path;
	if(bind(this->sock, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) < 0) {
		perror("ERROR binding stream socket");
		return;
	}
	if(listen(this->sock, 5) < 0){
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
    FD_SET(sock, &fd_master);

    tv.tv_sec = 1;
    tv.tv_usec = 0;
	running = true;
	int sel;
	while(running && (sel = select(0, &fd, NULL, NULL, &tv)) >= 0) {

		try{
			requestSock = accept(this->sock, NULL, NULL);
		}catch(int e){
			perror("ERROR on accept");
			running = false;
			continue;
		}
		if(requestSock < 0) {
			perror("ERROR on accept");
			running = false;
			continue;
		}
		ClientRequest *cr = new ClientRequest(requestSock);
		cr->start();
		fd = fd_master;
	}
	close(this->sock);
	unlink(master_path);
	this->sock = 0;
}

SocketServer::~SocketServer() {

}

