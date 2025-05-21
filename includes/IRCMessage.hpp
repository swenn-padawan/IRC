#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>

#include "macro.hpp"

#define CHAR_TRAILING ':'
#define CHAR_PREFIX ':'
#define CHAR_SPACE ' '
#define CHARSET_CRLF "\r\n\0"
#define CHARSET_SEPARATOR "\r\n: \0"
#define CHARSET_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
/**
 * @class IRCMessage
 * @brief Represents a parsed IRC protocol message
 *
 * This class provides functionality to parse, manipulate, and format IRC messages
 * according to the RFC 1459/2812 specifications.
 */
class IRCMessage
{
	GETSET(IRCMessage, std::string, prefix);
	GETSET(IRCMessage, std::string, command);
	GETTER(std::vector<std::string>, params);
	GETTER(std::string, raw_message);
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

	void clear();
	std::string get_nickname() const;
	std::string get_username() const;
	std::string get_hostname() const;
	std::string get_param(size_t index) const;

private:
	// Helper parsing methods
	bool parsePrefix(const std::string &str, size_t& pos);
	bool parseCommand(const std::string &str, size_t& pos);
	bool parseParams(const std::string &str, size_t& pos);
};
