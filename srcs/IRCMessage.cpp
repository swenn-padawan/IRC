#include "IRCMessage.hpp"

// Check if character is valid in command (letter)
inline bool isCmdLetter(char c) 
{
	return std::isalpha(static_cast<unsigned char>(c)) != 0;
}
// Per ABNF: nospcrlfcl = %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF
inline bool isSeparator(char c)
{
		return c != '\0' && c != '\r' && c != '\n' && c != ' ' && c != ':';
}
// Skip whitespace characters
inline void skipWhitespace(const char* str, size_t& pos, const size_t len)
{
	while (pos < len && str[pos] == ' ') ++pos;
}
// Remove CRLF from the end of a string if present
inline void removeCRLF(std::string& str)
{
	size_t len = str.length();
	if (len >= 2 && str[len-2] == '\r' && str[len-1] == '\n')
		str.resize(len - 2);
}

IRCMessage::~IRCMessage() {}

IRCMessage::IRCMessage() : _prefix(""),
	_command(""), _trailing(""), _params(), _hasTrailing(false) {}

IRCMessage::IRCMessage(const std::string& raw_message) : _hasTrailing(false)
{
	if (!parse(raw_message))
		throw std::invalid_argument("Failed to parse IRC message");
}

bool IRCMessage::parse(const std::string& raw_message, IRCMessage& message)
{
	message.clear();
	return message.parse(raw_message);
}

// Clear message
void IRCMessage::clear()
{
	_prefix.clear();
	_command.clear();
	_params.clear();
	_trailing.clear();
	_hasTrailing = false;
}

// Parse raw message
bool IRCMessage::parse(const std::string& raw_message)
{
	clear();
	const char* str = raw_message.c_str();
	size_t pos = 0, len = raw_message.length();
	// Skip any leading whitespace
	skipWhitespace(str, pos, len);
    // Parse prefix (optional)
    // && Parse command (required)
	// && Parse parameters (optional)
	return ((pos >= len || str[pos] != ':' || parsePrefix(str, pos, len))
			&& parseCommand(str, pos, len)
			&& (pos >= len || parseParams(str, pos, len)));
}

// Parse prefix part
bool IRCMessage::parsePrefix(const char* str, size_t& pos, const size_t len)
{
	// Skip the leading colon
	size_t prefix_start = ++pos;
	// Find the end of the prefix (next space)
	while (pos < len && str[pos] != ' ')
		pos++;	
	if (pos > prefix_start)
		_prefix = std::string(str + prefix_start, pos - prefix_start);
	// Skip the space after the prefix
	skipWhitespace(str, pos, len);
	return true;
}

// Parse command part
bool IRCMessage::parseCommand(const char* str, size_t& pos, const size_t len)
{
	size_t cmd_start = pos;	
	// Command is letters
	while (pos < len && isCmdLetter(str[pos]))
		pos++;
	// no valid command found
	if (pos == cmd_start)
		return false;
	_command = std::string(str + cmd_start, pos - cmd_start);
	// Skip the space after the command
	skipWhitespace(str, pos, len);
	return true;
}

// Parse parameters part
bool IRCMessage::parseParams(const char* str, size_t& pos, const size_t len)
{
	// Parse regular parameters (up to 14) and optionally a trailing parameter
	while (pos < len)
	{
		// Check for trailing parameter (starts with ':')
		if (str[pos] == ':') {
			pos++; // Skip the colon
			_trailing = std::string(str + pos, len - pos);
			removeCRLF(_trailing);
			_hasTrailing = true;
			break;
		}
		// Regular parameter (middle)
		size_t param_start = pos;
		while (pos < len && str[pos] != ' ' && isSeparator(str[pos]))
			pos++;
		
		if (pos > param_start)
			_params.push_back(std::string(str + param_start, pos - param_start));	
		// Skip the space after the parameter
		skipWhitespace(str, pos, len);
		
		// IRC spec limits to 15 parameters (14 middle + trailing)
		if (_params.size() >= 14)
		{
			// If we've already reached 14 params, the rest is trailing
			if (pos < len) {
				pos += str[pos] == ':'; // Skip the ":" if present
				_trailing = std::string(str + pos, len - pos);
				removeCRLF(_trailing);
				_hasTrailing = true;
			}
			break;
		}
	}
	return true;
}

// Get parameter by index
std::string IRCMessage::get_param(size_t index) const 
{
	return (index < _params.size()) ? _params[index] : "";
}

// Extract nickname from prefix
std::string IRCMessage::get_nickname() const
{
	if (_prefix.empty()) return "";

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
	if (_prefix.empty()) return "";
	
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

// Format message to string
std::string IRCMessage::toString(bool include_crlf) const
{
	std::string result;
	if (!_prefix.empty())
		result += ":" + _prefix + " ";
	result += _command;
	for (size_t i = 0; i < _params.size(); ++i)
		result += " " + _params[i];
	if (_hasTrailing)
		result += " :" + _trailing;
	if (include_crlf)
		result += "\r\n";
	return result;
}
