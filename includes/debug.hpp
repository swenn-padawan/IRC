#pragma once

/*
 * @brief:
 * Debugging functions/macros (Verbose)
 * 
 * @Colors:
*/

# define	BOLD(X)				"\033[1m" X "\033[22m"
# define 	ITALIC(X)			"\033[3m" X "\033[23m"
# define	RESET				"\033[0m"
# define	RED					"\033[31m"
# define	GREEN				"\033[32m"
# define	YELLOW				"\033[33m"
# define	BLUE				"\033[34m"
# define	MAGENTA				"\033[35m"
# define	CYAN				"\033[36m"
# define	GRAY				"\033[90m"
# define 	COLOR(C, X)			C X RESET

#include <stdio.h>

/*
 * @Macros:
*/

/*
 * S/o rgramati j'ai pas su faire faire mieux...(pour l'instant)
*/


/*@brief: If the program is compile with verbose mode (make re VERBOSE=1), it print all the LOG, WARN and OK macros, else it print nothing */

# define _IRC_LOG(c, t, msg, ...)	printf(BOLD(COLOR(c,"%8s")) " > " msg "\n", t, ##__VA_ARGS__)

#ifdef VERBOSE
#  define IRC_LOG(msg, ...)			_IRC_LOG(CYAN,       "log:", msg, ##__VA_ARGS__)
#  define IRC_WARN(msg, ...)		_IRC_LOG(YELLOW, "warning:", msg, ##__VA_ARGS__)
#  define IRC_OK(msg, ...)			_IRC_LOG(GREEN,	    "done:", msg, ##__VA_ARGS__)
# else
#  define IRC_LOG(msg, ...)
#  define IRC_WARN(msg, ...)
#  define IRC_OK(msg, ...)
#endif

# define IRC_ERR(msg, ...)			_IRC_LOG(RED,	   "error:", msg, ##__VA_ARGS__)

# define IRC_CATCH					catch (std::exception &e) { IRC_ERR("%s", e.what()); }
