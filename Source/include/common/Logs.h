#pragma once

#include <fmt/format.h>
#include <source_location>
#include <string>
#include <string_view>

namespace WoS
{
struct Log
{
private:
	static void WriteToConsole(const std::string &msg)
	{
		fmt::print("{}", msg);
	}

public:
	void static Print(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;34m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	void static Print(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;34m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Print(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;34m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Info(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;90m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	static void Info(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;90m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Info(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;90m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Debug(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;36m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	static void Debug(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;36m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Debug(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;36m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Success(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;32m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	static void Success(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;32m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static void Success(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;32m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Warning(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;33m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	void static Warning(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;33m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Warning(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;33m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Error(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;31m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	void static Error(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;31m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Error(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;31m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Crash(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[0;35m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	void static Crash(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[0;35m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Crash(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[0;35m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Clean(std::string_view fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;35m{}\033[0m\n", FormatPath(fullMessage, loc));
			WriteToConsole(message);
		}
	}

	void static Clean(int fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;35m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	void static Clean(float fullMessage, bool log = true, const std::source_location &loc = std::source_location::current())
	{
		if (log)
		{
			std::string message = fmt::format("\033[1;35m{}\033[0m\n", FormatPath(std::to_string(fullMessage), loc));
			WriteToConsole(message);
		}
	}

	static std::string FormatPath(const std::string_view &item, const std::source_location &loc)
	{
		return FormatPath(item, loc.file_name(), loc.function_name(), static_cast<int>(loc.line()));
	}

	static std::string FormatPath(std::string_view item, std::string_view path, std::string_view function, int lineNumber)
	{
		size_t lastSlash = path.find_last_of("\\/");
		std::string_view filename = (lastSlash != std::string_view::npos) ? path.substr(lastSlash + 1) : path;

		size_t lastDot = filename.find_last_of('.');
		std::string_view filenameNoExt = (lastDot != std::string_view::npos) ? filename.substr(0, lastDot) : filename;

		std::string functionName = ExtractFunctionName(function);

		if (functionName.empty())
		{
			return std::string(item) + " - " + std::string(filenameNoExt) + " (" + std::to_string(lineNumber) + ")";
		}

		return std::string(item) + " - " + std::string(filenameNoExt) + "/" + functionName + " (" + std::to_string(lineNumber) + ")";
	}

	static std::string ExtractFunctionName(std::string_view functionSignature)
	{
		size_t lastColonPos = functionSignature.rfind("::");
		if (lastColonPos == std::string_view::npos)
		{
			return "";
		}

		size_t openParenPos = functionSignature.find('(', lastColonPos);
		if (openParenPos == std::string_view::npos)
		{
			return "";
		}

		std::string_view name = functionSignature.substr(lastColonPos + 2, openParenPos - (lastColonPos + 2));
		return std::string{name};
	}
};
} // namespace WoS
