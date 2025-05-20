#include "irc.hpp"

Server::Server(){}

Server::Server(char *port, char *password){
	IRC_LOG("Server Created");
	set_port(std::atoi(port));
	set_password(password);
	IRC_LOG("Port = %d | password = %s", this->port, this->password.c_str());
	servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket == -1)
		throw socketFailed();
	IRC_OK("socket() OK");
	address_len = sizeof(struct sockaddr_in);
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(this->port);
	ipServ = bind(servSocket, (struct sockaddr *)&this->address, address_len);
	if (ipServ == -1)
		throw bindFailed();
	IRC_OK("bind() OK");
	if (fcntl(servSocket, F_SETFL, O_NONBLOCK) == -1)
		throw fcntlFailed();
	IRC_OK("fcntl() OK");
	if (listen(servSocket, SOMAXCONN) == -1)
		throw listenFailed();
	IRC_OK("listen() OK");
}

Server::~Server(){
	IRC_LOG("Server has been deleted");
}
