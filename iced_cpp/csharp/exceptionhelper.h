#pragma once

#include <stdexcept>
#include <string>

class ArgumentOutOfRangeException : public std::exception
{
private:
	std::string msg;

public:
	ArgumentOutOfRangeException(const std::string& message = "") : msg(message)
	{
	}

	ArgumentOutOfRangeException(const std::string& arg, const std::string& message) : msg("Argument " + arg + " is out of range: " + message)
	{
	}

	const char* what() const noexcept
	{
		return msg.c_str();
	}
};

class ArgumentNullException : public std::exception
{
private:
	std::string msg;
public:
	ArgumentNullException(const std::string& message = "") : msg(message)
	{
	}

	ArgumentNullException(const std::string& arg, const std::string& message) : msg("Argument " + arg + " is null: " + message)
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
