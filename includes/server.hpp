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
#include <sys/poll.h>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
#include <vector>

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
		void	servLoop(void);

	private:
		int				port;
		std::string		password;
		int				servSocket;
		struct sockaddr_in	address;
		socklen_t		address_len;
		int				ipServ;
		std::vector<pollfd> pfds;
};

EXCEPTION(socketFailedException, "socket failed");
EXCEPTION(bindFailedException, "bind failed");
EXCEPTION(listenFailedException, "listen failed");
EXCEPTION(fcntlFailedException, "fcntl failed");
EXCEPTION(acceptFailedException, "accept failed");
EXCEPTION(sigException, "End of the server");
EXCEPTION(convertionException, "Failed to convert the port");
