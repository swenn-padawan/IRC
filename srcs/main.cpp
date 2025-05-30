#include "debug.hpp"
#include "irc.hpp"
#include "IRCMessage.hpp"

/* @Usage:
 * /ircserv <port> <password>
*/

int main(int argc, char **argv){
	if (argc != 3){
		std::cerr << "Error: IRC: Not enought argument\n";
		return (1);
	}
	try{
		Server server(argv[1], argv[2]);
		server.servLoop();
	}IRC_CATCH;
}
