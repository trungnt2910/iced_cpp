// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>
#include <csharp/interfaces.h>
#include <csharp/primitives.h>

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include <string>
#include <exception>

class ArgumentOutOfRangeException : public std::exception
{
private:
	std::string msg;

public:
	ArgumentOutOfRangeException(const std::string& message = "") : msg(message)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};

class InvalidOperationException : public std::exception
{
private:
	std::string msg;

public:
	InvalidOperationException(const std::string& message = "") : msg(message)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};

class NotSupportedException : public std::exception
{
private:
	std::string msg;

public:
	NotSupportedException(const std::string& message = "") : msg(message)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};
