// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



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
#include <vector>
#include <cctype>
#include <stdexcept>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class HexUtils final
	{
	private:
		static constexpr std::int32_t TryParseHexChar(char c)
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
	public:
		static constexpr std::vector<std::uint8_t> ToByteArray(const std::string& hexData)
		{
			if (hexData == "")
			{
				throw std::invalid_argument("empty: hexData");
			}
			if (hexData.length() == 0)
			{
				return std::vector<std::uint8_t>();
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
					throw std::invalid_argument("out of range: hexData");
				}
				while (i < hexData.length() && std::isspace(hexData[i]))
				{
					i++;
				}
				if (i >= hexData.length())
				{
					throw std::invalid_argument("out of range: hexData");
				}
				std::int32_t lo = TryParseHexChar(hexData[i++]);
				if (lo < 0)
				{
					throw std::invalid_argument("out of range: hexData");
				}
				data[w++] = static_cast<std::uint8_t>((hi << 4) | lo);
			}
			if (w != data.size())
			{
				throw std::runtime_error("invalid operation");
			}
			return data;
		}
	};
}
