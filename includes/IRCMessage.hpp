#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>

#include "macro.hpp"

/**
 * @class IRCMessage
 * @brief Represents a parsed IRC protocol message
 *
 * This class provides functionality to parse, manipulate, and format IRC messages
 * according to the RFC 1459/2812 specifications.
 */
class IRCMessage
{
GETTER_SETTER(IRCMessage, std::string, prefix);
GETTER_SETTER(IRCMessage, std::string, command);
GETTER_SETTER(IRCMessage, std::string, trailing, _hasTrailing = true;);
GETTER(std::vector<std::string>, params);
GETTER(bool, hasTrailing);

public:
	IRCMessage();
	~IRCMessage();

	/**
	 * @brief Construct and parse from raw message
	 * @param raw_message The raw IRC message to parse
	 * @throws std::invalid_argument If the message cannot be parsed
	 */
	explicit IRCMessage(const std::string& raw_message);

	/**
	 * @brief Parse a raw IRC message
	 * @param raw_message The raw message to parse
	 * @return true if parsing was successful, false otherwise
	 */
	bool parse(const std::string& raw_message);

	/**
	 * @brief Static parsing method that doesn't modify the object
	 * @param raw_message The raw message to parse
	 * @param message The message object to populate
	 * @return true if parsing was successful, false otherwise
	 */
	static bool parse(const std::string& raw_message, IRCMessage& message);

	/**
	 * @brief Format message back to string representation
	 * @param include_crlf Whether to append CRLF at the end
	 * @return Formatted IRC message string
	 */
	std::string toString(bool include_crlf = true) const;

	void clear();
	std::string get_nickname() const;
	std::string get_username() const;
	std::string get_hostname() const;
	std::string get_param(size_t index) const;

private:
	// Helper parsing methods
	bool parsePrefix(const char* str, size_t& pos, const size_t len);
	bool parseCommand(const char* str, size_t& pos, const size_t len);
	bool parseParams(const char* str, size_t& pos, const size_t len);
};
