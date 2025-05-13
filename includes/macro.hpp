#pragma once

/*
 * @brief:
 * This are MACROS to generate GET's and SET class functions
*/


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

#define GETTER(field_type, field_name) \
	field_type get_##field_name() const {return field_name;}

#define SETTER(field_type, field_name) \
    void set_##field_name(field_type value) { field_name = value; }
