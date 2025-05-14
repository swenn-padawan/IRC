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

# include <poll.h>
# include <signal.h>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <netinet/in.h> 

class Server{
	public:
		Server();
		~Server();

	private:

};

