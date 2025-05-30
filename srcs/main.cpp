#include "irc.hpp"
#include "IRCMessage.hpp"

/* @Usage:
 * /ircserv <port> <password>
*/

#define IRC_DEBUG(msg, str) IRC_LOG(msg, str.c_str());

int main(int argc, char **argv){
	UNUSED(argc);
	UNUSED(argv);

	try{
		IRCMessage msg(argv[1]);
		IRC_LOG("-- Checking Parsed message --");
		IRC_DEBUG("Raw message: %s", msg.get_raw_message());
		IRC_DEBUG("Command: %s", msg.get_command());
		IRC_DEBUG("Prefix: %s", msg.get_prefix());
		IRC_DEBUG("Nickname: %s", msg.get_nickname());
		IRC_DEBUG("Username: %s", msg.get_username());
		IRC_DEBUG("Hostname: %s", msg.get_hostname());
		for (size_t i = 0; i < msg.get_params().size(); ++i)
			IRC_LOG("Param[%lu]: %s", i, msg.get_param(i).c_str());
		if(!msg.get_hasTrailing())
			IRC_WARN("Message does not have trailing text");
	} IRC_CATCH
}
