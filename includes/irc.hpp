#pragma once

/*
 * @Sources:
 * https://modern.ircdocs.horse/
 *
 *
*/


# include <iostream>

#define UNUSED __attribute__((unused))

/*
 * @brief:
 * This are MACROS to generate GET and SET functions
 *
*/

#define GETTER(field_type, field_name) \
	field_type get_##field_name() const {return field_name;}

#define SETTER(field_type, field_name) \
    void set_##field_name(field_type value) { field_name = value; }

/*
 * @exemple:
 *
class test{
	private:
		std::string name;

	public:
		test();
		~test();
		GETTER(std::string, name);
		SETTER(std::string, name);
};
*/

