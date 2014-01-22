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
	if(listen(this->sock, 1) < 0){
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
			requestSock = accept(this->sock, NULL, NULL);
			if(requestSock < 0) {
				perror("ERROR on accept");
				running = false;
				continue;
			}
			ClientRequest *cr = new ClientRequest(requestSock);
			cr->start();
		}
		memcpy(&fd, &fd_master, sizeof(fd_master));
	}
	close(this->sock);
	unlink(master_path);
	this->sock = 0;
}

SocketServer::~SocketServer() {

}

