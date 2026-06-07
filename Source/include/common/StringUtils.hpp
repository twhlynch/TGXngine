#pragma once

#include <algorithm>
#include <regex>
#include <string>
#include <type_traits>
#include <vector>

std::vector<std::string> static StringSplit(const std::string &input, const std::string &_regex)
{
	std::regex re(_regex);
	std::sregex_token_iterator
		first{input.begin(), input.end(), re, -1},
		last;
	return {first, last};
}

std::string static LastStringSplit(const std::string &input, const std::string &_regex)
{
	std::regex re(_regex);
	std::sregex_token_iterator
		first{input.begin(), input.end(), re, -1},
		last;
	std::vector<std::string> reversedStrings{first, last};

	std::reverse(reversedStrings.begin(), reversedStrings.end());

	if (!reversedStrings.empty())
	{
		return reversedStrings.front();
	}

	return "";
}

inline std::string ToString(const std::string &value)
{
	return value;
}
inline std::string ToString(const char *value)
{
	return value ? std::string(value) : std::string{};
}
inline std::string ToString(char value)
{
	return std::string(1, value);
}
inline std::string ToString(bool value)
{
	return value ? "true" : "false";
}

template <typename T>
inline std::enable_if_t<std::is_arithmetic_v<T> && !std::is_same_v<T, bool>, std::string>
ToString(T value)
{
	return std::to_string(value);
}

template <typename... Args>
std::string StringConcat(Args &&...args)
{
	std::string result;
	(result.append(ToString(std::forward<Args>(args))), ...);
	return result;
}

void static StringReplaceAll(std::string &str, const std::string &from, const std::string &to)
{
	if (from.empty())
	{
		return;
	}

	size_t start_pos = 0;

	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}
