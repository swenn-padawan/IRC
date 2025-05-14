#include "irc.hpp"

/* @Usage:
 * /ircserv <port> <password>
*/

void	test(bool val){
	UNUSED(val);
	IRC_LOG("test poll");
	IRC_WARN("oulala");
}

int main(int argc, char **argv){
	UNUSED(argc);
	UNUSED(argv);
	test(1);
}
