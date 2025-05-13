#include "debug.hpp"
#include "irc.hpp"

/* @Usage:
 * /ircserv <port> <password>
*/

void	test(bool val){
	if (val) DEBUG_THROW("pas cool");
}

int main(UNUSED int argc, UNUSED char **argv){
	try{
		test(0);
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	if (argc != 3){
		std::cerr << "ARGS ERROR at: " << __LINE__ << " in: " << __FILE__ <<std::endl;
		return (1);
	}
}
