/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stetrel <stetrel@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:46:12 by stetrel           #+#    #+#             */
/*   Updated: 2025/05/28 08:48:24 by stetrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "debug.hpp"
#include "irc.hpp"
#include "macro.hpp"
#include <sys/poll.h>
#include <sys/socket.h>
#include <utility>

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
					//Server::AddClient()
					struct pollfd newClientpfd;
					newClientpfd.events = POLLIN;
					newClientpfd.fd = accept(servSocket, (struct sockaddr *)0, 0);
					if (newClientpfd.fd == -1) throw acceptFailedException();
					pfds.push_back(newClientpfd);
					Client	newClient(newClientpfd);
					clientMap.insert(std::make_pair(newClientpfd.fd, newClient));
					nb_client++;
					IRC_OK("client %d connected", nb_client);
					send(newClientpfd.fd, WELCOME, sizeof(WELCOME), MSG_DONTWAIT);
				}
				else{ //Server::ReceiveMsg
					char	recbuffer[255];
					int bytes = recv(pfds[i].fd, recbuffer, 255, MSG_DONTWAIT);
					if (bytes == -1) throw recvFailedException();
					if (bytes == 0){
						pfds.erase(pfds.begin() + i);
						clientMap.erase(pfds[i].fd);
						nb_client--;
						IRC_WARN("client %i disconnected", i);
						i--;
						continue;
					}
					recbuffer[bytes] = '\0';
					std::string tmp_msg = FIND_MSG(i, get_msg()) += std::string(recbuffer);
					FIND_MSG(i, set_msg(tmp_msg));
					if (std::string(recbuffer).find_first_of(CRLF) != std::string::npos){
						//executeCommand
						IRC_LOG("final string = %s", FIND_MSG(i, get_msg()).c_str());
					}else{
						//nothing
					}

				}
			}
		}
	}
}
