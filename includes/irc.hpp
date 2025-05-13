#pragma once

/*
 * @Sources:
 * https://modern.ircdocs.horse/
 *
*/

/*
 * @Forbidden Stuff:
 * - if fcntl() is used, it only can be use like this: fcntl(fd, F_SETFL, O_NONBLOCK)
 * - poll() or equivalent is mandatory ("Ainsi, si vous essayez d’utiliser read/recv ou write/send avec
		n’importe quel FD sans utiliser poll() (ou équivalent), votre note
		sera de 0.") Voir Sujet: page 6
 * etc...
*/

# include <iostream>
# include "server.hpp"
# include "client.hpp"

#if __has_attribute(unused)
#	define UNUSED __attribute__((unused))
#else
#	define UNUSED
#endif
