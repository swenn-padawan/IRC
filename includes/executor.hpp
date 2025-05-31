
#pragma once

#include "IRCMessage.hpp"

#define MAX_COMMAND 12

class Server;

class Executor
{
	private:
		typedef void (*CommandCallback)(const Server&, const IRCMessage&);
		static const std::string _names[MAX_COMMAND];
		static const Executor::CommandCallback _commands[MAX_COMMAND];

		static void executePass(const Server& server, const IRCMessage& message);
		static void executeNick(const Server& server, const IRCMessage& message);
		static void executeUser(const Server& server, const IRCMessage& message);
		static void executeJoin(const Server& server, const IRCMessage& message);
		static void executePart(const Server& server, const IRCMessage& message);
		static void executeMode(const Server& server, const IRCMessage& message);
		static void executeQuit(const Server& server, const IRCMessage& message);
		static void executeKick(const Server& server, const IRCMessage& message);
		static void executeTopic(const Server& server, const IRCMessage& message);
		static void executeNotice(const Server& server, const IRCMessage& message);
		static void executeInvite(const Server& server, const IRCMessage& message);
		static void executePrivmsg(const Server& server, const IRCMessage& message);

	public:
		static void executeCommand(const Server& server, const IRCMessage& message);
};

const std::string Executor::_names[MAX_COMMAND] = {
		"PASS",
		"NICK",
		"USER",
		"JOIN",
		"PART",
		"PRIVMSG",
		"NOTICE",
		"MODE",
		"TOPIC",
		"QUIT",
		"KICK",
		"INVITE",
};
const Executor::CommandCallback Executor::_commands[MAX_COMMAND] = {
		&Executor::executePass,
		&Executor::executeNick,
		&Executor::executeUser,
		&Executor::executeJoin,
		&Executor::executePart,
		&Executor::executePrivmsg,
		&Executor::executeNotice,
		&Executor::executeMode,
		&Executor::executeTopic,
		&Executor::executeQuit,
		&Executor::executeKick,
		&Executor::executeInvite,
};
