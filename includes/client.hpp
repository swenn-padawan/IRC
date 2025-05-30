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

class Client{
	public:
		Client();
		Client(struct pollfd _pfd);
		GETTER(struct pollfd, pfd);
		GETTER(std::string, msg);
		GETTER(size_t, _size);
		GETTER(bool, isEmpty);
		SETTER(std::string, msg);
//		GETTER(map<int COMMA int>, _map)
		~Client();
	private:

		std::string		msg;
		struct pollfd	pfd;
		bool			isEmpty;
		size_t			_size;
};
