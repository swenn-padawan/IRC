#pragma once

/*@brief: Generate automatically a getter/setter funcs*/
#define GETTER(field_type, field_name) \
	field_type get_##field_name() const {return field_name;}

#define SETTER(field_type, field_name) \
    void set_##field_name(field_type value) { field_name = value; }

# define UNUSED(x) ((void)x)

/*@brief: Generate Exception */
/*@Exemple: EXCEPTION(ServerPollFailedException, "poll() failed"); */

# define EXCEPTION(n, m)	class n:public std::exception { inline const char *what() const throw() { return (m) ; } ; }

