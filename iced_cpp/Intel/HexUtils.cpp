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

#include "HexUtils.h"
#include "../Array2.h"

namespace Iced::Intel
{

	std::vector<std::uint8_t> HexUtils::ToByteArray(const std::string& hexData)
	{
		if (hexData == "")
		{
			throw std::invalid_argument("hexData");
		}
		if (hexData.length() == 0)
		{
			return Array2::Empty<std::uint8_t>();
		}
		std::int32_t len = 0;
		for (std::int32_t i = 0; i < hexData.length(); i++)
		{
			if (hexData[i] != ' ')
			{
				len++;
			}
		}
		auto data = std::vector<std::uint8_t>(len / 2);
		std::int32_t w = 0;
		for (std::int32_t i = 0; ;)
		{
			while (i < hexData.length() && std::isspace(hexData[i]))
			{
				i++;
			}
			if (i >= hexData.length())
			{
				break;
			}
			std::int32_t hi = TryParseHexChar(hexData[i++]);
			if (hi < 0)
			{
				throw ArgumentOutOfRangeException("hexData");
			}
			while (i < hexData.length() && std::isspace(hexData[i]))
			{
				i++;
			}
			if (i >= hexData.length())
			{
				throw ArgumentOutOfRangeException("hexData");
			}
			std::int32_t lo = TryParseHexChar(hexData[i++]);
			if (lo < 0)
			{
				throw ArgumentOutOfRangeException("hexData");
			}
			data[w++] = static_cast<std::uint8_t>((hi << 4) | lo);
		}
		if (w != data.size())
		{
			throw InvalidOperationException();
		}
		return data;
	}

	std::int32_t HexUtils::TryParseHexChar(char c)
	{
		if ('0' <= c && c <= '9')
		{
			return c - '0';
		}
		if ('A' <= c && c <= 'F')
		{
			return c - 'A' + 10;
		}
		if ('a' <= c && c <= 'f')
		{
			return c - 'a' + 10;
		}
		return -1;
	}
}
