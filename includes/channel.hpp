#pragma once

#include "macro.hpp"
#include <iostream>
#include "client.hpp"
#include <utility>
#include <vector>

enum ChannelMode {
	MODE_INVITE_ONLY = 1 << 0,
	MODE_TOPIC_OP_ONLY = 1 << 1,
	MODE_KEY_REQUIRED = 1 << 2,
	MODE_MODERATED = 1 << 3,
	MODE_LIMIT_SET = 1 << 4,
};

#define IS_MODE_SET(c, m)	((c).modes & (m))
#define SET_MODE(c, m)      ((c).modes |= (m))
#define UNSET_MODE(c, m)    ((c).modes &= ~(m))

class Channel{
	public:
		Channel();
		~Channel();
		GETSET(Channel, std::string, topic)
		GETSET(Channel, std::string, name)
		GETTER(std::vector<std::pair<Client*COMMA bool> >, clients) //bool is for the operator
		GETSET(Channel, int, user_limit);
		GETSET(Channel, std::string, key);
		char	modes;	// 0x00000000
						//   itkol000 activate the bit corresponding to the modes (overkill mais drole, desole mika)
	private:

};
