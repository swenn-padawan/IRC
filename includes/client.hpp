#pragma once

/*
 * @brief:
 * In this file, there will be all the classes and stuffs related to the cients management
 *
 *
*/

#include "macro.hpp"
#include <poll.h>
#include <cstdlib>
#include <string>

#define	COMMA	,

class Client
{
	GETSET(Client, std::string, msg);
	GETTER(struct pollfd, pfd);
	GETTER(size_t, size);
	GETTER(bool, isEmpty);

	public:
		Client();
		Client(struct pollfd _pfd);
		~Client();
};
