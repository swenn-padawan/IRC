#pragma once

/*
 * @brief:
 * In this file, there will be all the classes and stuffs related to the server management
 *
 *
 * TODO:
 * [ ] - Analyse
 * [ ] - Send
*/

#include "client.hpp"
#include "macro.hpp"

#include <errno.h>
#include <string.h>
#include <iostream>
#include <signal.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <climits>

#define MAX_CLIENT 128
#define WELCOME "Welcome to Our IRC Chat, Please read the Documentation (RFC 2812)\n"

class Server
{
	GETSET(Server, int, port)
	GETSET(Server, std::string, password)
	GETTER(std::map<std::string COMMA std::vector<const Client*> >, chanelsMap)

	public:
		Server();
		Server(char *port, char *password);
		~Server();
		void	servLoop(void);
		int		addClient(void);
		int		executeCommand(Client &client);

	private:
		struct sockaddr_in	address;
		socklen_t		address_len;
		int				servSocket;
		int				nb_client;
		int				ipServ;
		std::vector<struct pollfd> pfds;
		std::map<int, Client>	clientMap;
};

EXCEPTION(socketFailedException, "socket failed");
EXCEPTION(bindFailedException, "bind failed");
EXCEPTION(listenFailedException, "listen failed");
EXCEPTION(fcntlFailedException, "fcntl failed");
EXCEPTION(acceptFailedException, "accept failed");
EXCEPTION(sigException, "End of the server");
EXCEPTION(convertionException, "Failed to convert the port");
EXCEPTION(recvFailedException, "recv failed");
