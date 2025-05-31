#pragma once

#define	COMMA	,

#define GETSET(cls, type, var, ...) \
	private: type _##var; \
	public: \
	const type& get_##var() const {return _##var;} \
	cls& set_##var(const type& val) {_##var = val; __VA_ARGS__ return *this;}

#define GETTER(type, var) \
	private: type _##var; \
	public: const type& get_##var() const {return _##var;}

#define SETTER(cls, type, var, ...) \
	private: type _##var; \
	public: cls& set_##var(type val) {_##var = val; __VA_ARGS__ return *this;}

# define UNUSED(x) ((void)x)

/*@brief: Generate Exception */
/*@Exemple: EXCEPTION(ServerPollFailedException, "poll() failed"); */

# define EXCEPTION(n, m)	class n:public std::exception { inline const char *what() const throw() { return (m) ; } ; }

# define FIND_MSG(i, func) clientMap.find(pfds[i].fd)->second.func

# define CRLF "\r\n"

# define BUFFER_SIZE 3000
