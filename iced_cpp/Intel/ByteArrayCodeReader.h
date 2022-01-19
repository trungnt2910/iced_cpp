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

#include "CodeReader.h"
#include <string>
#include <vector>

#include <string_view>
#include <ranges>
#include "HexUtils.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	template <typename R>
	concept byte_random_access_borrowed_range =
		std::ranges::borrowed_range<R> &&
		std::ranges::random_access_range<R> &&
		std::is_convertible_v<std::ranges::range_value_t<R>, std::uint8_t> &&
		sizeof(std::ranges::range_value_t<R>) == sizeof(std::uint8_t);

	template <typename R>
	concept byte_range =
		std::ranges::range<R> &&
		std::is_convertible_v<std::ranges::range_value_t<R>, std::uint8_t> &&
		sizeof(std::ranges::range_value_t<R>) == sizeof(std::uint8_t);

	/// <summary>
	/// A <see cref="CodeReader"/> that reads data from a byte array
	/// </summary>
	template <byte_random_access_borrowed_range R = std::string_view>
	class ByteArrayCodeReader final : public CodeReader
	{
		/* readonly */
	private:
		std::vector<std::ranges::range_value_t<R>> copied_data;
		R data;
		std::ranges::borrowed_iterator_t<R> current;
		/// <summary>
		/// Current position
		/// </summary>
	public:
		constexpr std::int32_t GetPosition() const
		{
			return (std::int32_t)(current - std::ranges::begin(data));
		}
		constexpr void SetPosition(std::int32_t value)
		{
			current = std::ranges::begin(data) + value;
		}
		/// <summary>
		/// Number of bytes that can be read
		/// </summary>
		constexpr std::int32_t GetCount() const
		{
			return (std::int32_t)(std::ranges::size(data));
		}
		/// <summary>
		/// Checks if it's possible to read another byte
		/// </summary>
		constexpr bool GetCanReadByte() const
		{
			return current != std::ranges::end(data);
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="range">Byte borrowed range, such as std::string_view</param>
		constexpr ByteArrayCodeReader(const R& range) :
			data(range),
			current(std::ranges::begin(data))
		{
		}

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="range">Any range that contains bytes</param>
		template <byte_range R1>
		constexpr ByteArrayCodeReader(const R1& range) : 
			copied_data(std::ranges::begin(range), std::ranges::end(range)), 
			data(copied_data.begin(), copied_data.end()), 
			current(std::ranges::begin(data)) 
		{
		}

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="hexData">Hex bytes encoded in a string</param>
		static constexpr ByteArrayCodeReader DecodeFromString(const std::string& hexData)
		{
			return ByteArrayCodeReader(HexUtils::ToByteArray(hexData));
		}

		/// <summary>
		/// Reads the next byte or returns less than 0 if there are no more bytes
		/// </summary>
		/// <returns></returns>
		constexpr std::int32_t ReadByte() override
		{
			if (!GetCanReadByte())
			{
				return -1;
			}
			std::int32_t result = (std::uint8_t)*current;
			++current;
			return result;
		}
	};
}
