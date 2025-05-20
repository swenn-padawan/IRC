#pragma once

/*
 * @brief:
 * In this file, there will be all the classes and stuffs related to the server management
 *
 *
 * TODO:
 * [ ] - Initialisation
 * [ ] - Listen
 * [ ] - Receive
 * [ ] - Analyse
 * [ ] - Send
 * [ ] - Handle disconnect
 * [ ] - Handle Signals
*/

#include "macro.hpp"
#include <iostream>
# include <poll.h>
# include <signal.h>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h> 

#define MAX_CLIENT 128

class Server{
	public:
		Server();
		Server(char *port, char *password);
		~Server();
		SETTER(int, port);
		SETTER(std::string, password);
		GETTER(int, port);
		GETTER(std::string, password);

	private:
		int				port;
		std::string		password;
		int				servSocket;
		struct sockaddr_in	address;
		socklen_t		address_len;
		int				ipServ;
};

EXCEPTION(socketFailed, "socket failed");
EXCEPTION(bindFailed, "bind failed");
EXCEPTION(listenFailed, "listen failed");
EXCEPTION(fcntlFailed, "fcntl failed");
EXCEPTION(acceptFailed, "accept failed");
