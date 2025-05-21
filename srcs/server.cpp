#include "server.hpp"
#include "debug.hpp"
#include "irc.hpp"
#include <sys/poll.h>
#include <sys/socket.h>

Server::Server(){}

Server::Server(char *port, char *password){
	IRC_LOG("Server Created");
	long int	new_port;

	new_port = std::strtol(port, &port, 10);
	if (new_port == LONG_MIN || new_port == LONG_MAX || *port)
		throw convertionException();
	set_port(new_port);
	set_password(password);
	IRC_LOG("Port = %d | password = %s", this->port, this->password.c_str());
	servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket == -1)
		throw socketFailedException();
	IRC_OK("socket() OK");
	address_len = sizeof(struct sockaddr_in);
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(this->port);
	ipServ = bind(servSocket, (struct sockaddr *)&this->address, address_len);
	if (ipServ == -1)
		throw bindFailedException();
	IRC_OK("bind() OK");
	if (fcntl(servSocket, F_SETFL, O_NONBLOCK) == -1)
		throw fcntlFailedException();
	IRC_OK("fcntl() OK");
	if (listen(servSocket, SOMAXCONN) == -1)
		throw listenFailedException();
	IRC_OK("listen() OK");
	IRC_OK("Server initialisation OK");
}

Server::~Server(){
	IRC_LOG("Server has been deleted");
}

void	sig_handler(int sig){
	UNUSED(sig);
	//free
	throw sigException();
}

void	Server::servLoop(void){
	struct sigaction sig;
	int	nb_client = 0;

	memset(&sig, 0, sizeof(sig));
	sig.sa_handler = sig_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	pfds.resize(nb_client + 1);
	pfds[0].events = POLLIN;
	pfds[0].fd = servSocket;
	while (1){
		poll(&pfds[0], nb_client + 1, 100);
		for(int i = 0; i < nb_client + 1; i++){
			if (pfds[i].revents & POLLIN){
				if (i == 0){
					struct pollfd newClient;
					newClient.events = POLLIN;
					newClient.fd = accept(servSocket, (struct sockaddr *)0, 0);
					if (newClient.fd == -1) throw acceptFailedException();
					pfds.push_back(newClient);
					nb_client++;
					IRC_OK("client %d connected", nb_client);
				}
				else{
					char buffer[100];
					int bytes = recv(pfds[i].fd, buffer, sizeof(buffer), MSG_DONTWAIT);
					if (bytes == -1) throw recvFailedException();
					if (bytes == 0){
						pfds.erase(pfds.begin() + i);
						nb_client--;
						IRC_WARN("client %i disconnected", i);
						i--;
					}
					buffer[bytes] = '\0';
					IRC_LOG("client %i send -> %s", i, buffer);

				}
			}
		}
	}
}
