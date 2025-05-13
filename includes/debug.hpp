#pragma once

/*
 * @brief:
 * Debugging functions/macros
 *
 * Can be delete before final push
*/

/*
 * @Colors:
*/

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define GRAY    "\033[90m"

/*
 * @Macros:
*/

#include <stdio.h>
#include <exception>

class	DebugException: public std::exception{
	public:
		virtual const char* what() const throw();
};

#ifdef DEBUG_BUILD
#	define DEBUG_THROW(msg) throw DebugException()
#else
#	define DEBUG_THROW(msg) ((void)0)
#endif
