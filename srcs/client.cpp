#include "client.hpp"

Client::Client(){
}

Client::~Client(){}

Client::Client(struct pollfd pfd){
	_pfd = pfd;
	_isEmpty = true;
}
