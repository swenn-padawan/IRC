#pragma once

#include "macro.hpp"
#include <iostream>
#include "client.hpp"
#include <utility>
#include <vector>

class Channel{
	public:
		Channel();
		~Channel();
		GETSET(Channel, std::string, topic)
		GETTER(std::vector<std::pair<Client*COMMA bool> >, clients)
	private:

};
