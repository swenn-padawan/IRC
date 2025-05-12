#include "irc.hpp"

/* @Usage:
 * /ircserv <port> <password>
*/

/*
 * @Forbidden Stuff:
 * - if fcntl() is used, it only can be use like this: fcntl(fd, F_SETFL, O_NONBLOCK)
 * etc...
*/

int main(UNUSED int argc, UNUSED char **argv){
	if (argc != 3){
		std::cerr << "ARGS ERROR" << std::endl;
		return (1);
	}
}
