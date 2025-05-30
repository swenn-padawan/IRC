#include "client.hpp"

Client::Client(){
}

Client::~Client(){}

Client::Client(struct pollfd _pfd){
	this->pfd = _pfd;
	isEmpty = true;
}
