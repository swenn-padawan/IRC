#include "IRCMessage.hpp"

IRCMessage::~IRCMessage() {}

IRCMessage::IRCMessage() : _prefix(""),
	_command(""), _params(), _hasTrailing(false) {}

IRCMessage::IRCMessage(const std::string &raw_message) : _hasTrailing(false)
{
	if (!parse(raw_message))
		throw std::invalid_argument("Failed to parse IRC message");
}

bool IRCMessage::parse(const std::string &raw_message, IRCMessage &message)
{
	message.clear();
	return message.parse(raw_message);
}

void IRCMessage::clear()
{
	_prefix.clear();
	_command.clear();
	_params.clear();
	_raw_message.clear();
	_hasTrailing = false;
}

bool IRCMessage::parse(const std::string &raw_message)
{
	this->clear();
	_raw_message = raw_message;
	if (raw_message.empty())
		return false;
	size_t pos = 0;
	//skipWhitespace(str, pos, len);
	return (parsePrefix(raw_message, pos)
			&& parseCommand(raw_message, pos)
			&& parseParams(raw_message, pos));
}

bool IRCMessage::parsePrefix(const std::string &str, size_t &pos)
{
	if (str[pos] != CHAR_PREFIX)
		return true;
	// Find the end of the prefix (next space)
	size_t prefix_end = str.find(CHAR_SPACE, ++pos);
	if (prefix_end == pos)
		return false;
	_prefix = str.substr(pos, prefix_end - pos);
	pos = prefix_end;
	return pos != std::string::npos;
}

bool IRCMessage::parseCommand(const std::string &str, size_t& pos)
{
	// Skip skipWhitespace
	pos = str.find_first_not_of(CHAR_SPACE, pos);
	if (pos == std::string::npos)
		return false;
	size_t cmd_end = str.find_first_not_of(CHARSET_LETTERS, pos);
	// no valid command found
	if (pos == cmd_end)
		return false;
	_command = str.substr(pos, cmd_end - pos);
	pos = str.find_first_not_of(CHARSET_SEPARATOR, cmd_end);
	return (pos != cmd_end || pos == std::string::npos);
}

bool IRCMessage::parseParams(const std::string &str, size_t& pos)
{
	// Parse regular parameters (up to 14) and optionally a trailing parameter
	while (pos != std::string::npos && _params.size() < 14)
	{
		size_t param_end = str.find_first_of(CHARSET_SEPARATOR, pos);
		if (param_end > pos)
			_params.push_back(str.substr(pos, param_end - pos));
		pos = str.find_first_not_of("\r\n \0", param_end);
		if (str[pos] == CHAR_TRAILING)
		{
			_params.push_back(str.substr(++pos));
			return (_hasTrailing=true);
		}
	}
	return pos == std::string::npos;
}

// Get parameter by index
std::string IRCMessage::get_param(size_t index) const 
{
	return (index < _params.size()) ? _params[index] : "";
}

// Extract nickname from prefix
std::string IRCMessage::get_nickname() const
{
	if (_prefix.empty())
		return "";
	size_t pos = _prefix.find('!');
	// If no '!', look for '@'
	if (pos == std::string::npos)
	{
		pos = _prefix.find('@');
		if (pos == std::string::npos)
			return _prefix; // No @, just a nickname
	}
	return _prefix.substr(0, pos);
}

// Extract username from prefix
std::string IRCMessage::get_username() const
{
	if (_prefix.empty())
		return "";	
	size_t excl_pos = _prefix.find('!');
	// If no '!', no username
	if (excl_pos == std::string::npos)
		return "";
	size_t at_pos = _prefix.find('@', excl_pos);
	// If no '@', return everything after '!'
	return (at_pos == std::string::npos) ? _prefix.substr(excl_pos + 1)
		: _prefix.substr(excl_pos + 1, at_pos - excl_pos - 1);
}

// Extract hostname from prefix
std::string IRCMessage::get_hostname() const
{
	if (_prefix.empty())
		return "";	
	size_t at_pos = _prefix.find('@');
	return (at_pos == std::string::npos) ? "" : _prefix.substr(at_pos + 1);
}
