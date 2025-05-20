#include "irc.hpp"
#include "IRCMessage.hpp"

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

	IRCMessage msg(":nick!user@host PRIVMSG #channel");
	IRC_LOG("Parsed message: %s", msg.toString(false).c_str());
	IRC_LOG("Command: %s", msg.get_command().c_str());
	IRC_LOG("Prefix: %s", msg.get_prefix().c_str());
	IRC_LOG("Nickname: %s", msg.get_nickname().c_str());
	IRC_LOG("Username: %s", msg.get_username().c_str());
	IRC_LOG("Hostname: %s", msg.get_hostname().c_str());
	for (size_t i = 0; i < msg.get_params().size(); ++i)
		IRC_LOG("Param[%lu]: %s", i, msg.get_param(i).c_str());
	IRC_LOG("Trailing: %s", msg.get_trailing().c_str());
	msg.set_trailing("New trailing text");
	IRC_LOG("Updated trailing: %s", msg.get_trailing().c_str());
	if(!msg.get_hasTrailing())
		IRC_WARN("Message does not have trailing text");
}
