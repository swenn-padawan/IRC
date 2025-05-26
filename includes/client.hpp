#pragma once

/*
 * @brief:
 * In this file, there will be all the classes and stuffs related to the cients management
 *
 *
 * TODO: ([X] = finish, [...] = in progress, [ ] Not started yet)
 * [ ] - Parsing user input
 * [ ] - Send it
 * [ ] - Handle Ctrl+D (Reconstitute packet before treat them)
*/

#include "macro.hpp"
#include <poll.h>
#include <cstdlib>

#define	COMMA	,

class Client{
	public:
		Client();
		Client(struct pollfd _pfd);
		GETTER(struct pollfd, pfd);
		GETTER(char *, buffer);
		GETTER(size_t, _size);
//		GETTER(map<int COMMA int>, _map)
		~Client();
	private:
		char			*buffer;
		struct pollfd	pfd;
		bool			isEmpty;
		size_t			_size;
};
