// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include <ranges>
#include <string>
#include <vector>

namespace Iced::Intel::Internal
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

	template <byte_random_access_borrowed_range R = std::string_view>
	class DataReader
	{
	private:
		const std::vector<std::ranges::range_value_t<R>> copied_data;
		R data;
		std::ranges::borrowed_iterator_t<R> current;
	public:
		constexpr std::int32_t GetIndex() const
		{
			return (std::int32_t)(current - std::ranges::begin(data));
		}
		constexpr void SetIndex(std::int32_t value)
		{
			current = std::ranges::begin(data) + value;
		}
		constexpr bool GetCanRead() const
		{
			return current != std::ranges::end(data);
		}
		// Second parameter maintained for signature compatibility with C#'s version.
		constexpr DataReader(const R& range, std::int32_t maxStringLength = 0) : data(range), current(std::ranges::begin(data)) {}
		template <byte_range R1>
		constexpr DataReader(const R1& range, std::int32_t maxStringLength = 0) :
			copied_data(std::ranges::begin(range), std::ranges::end(range)),
			data(copied_data.begin(), copied_data.end()),
			current(std::ranges::begin(data))
		{
		}
		constexpr std::uint8_t ReadByte()
		{
			std::uint8_t result = *current;
			++current;
			return result;
		}
		constexpr std::uint32_t ReadCompressedUInt32()
		{
			std::uint32_t result = 0;
			for (std::int32_t shift = 0; shift < 32; shift += 7)
			{
				std::uint32_t b = ReadByte();
				if ((b & 0x80) == 0)
				{
					return result | (b << shift);
				}
				result |= (b & 0x7F) << shift;
			}
			throw std::runtime_error("Unexpected error when reading UInt32");
		}
		constexpr std::string ReadAsciiString()
		{
			std::int32_t length = ReadByte();
			
			std::string result;
			result.reserve(length);
			
			for (std::int32_t i = 0; i < length; i++)
			{
				result.push_back(static_cast<char>(ReadByte()));
			}

			return result;
		}

		constexpr DataReader() = default;
	};

	template<byte_random_access_borrowed_range R>
	DataReader(const R&) -> DataReader<R>;

	template<byte_range R>
	// I know, there's an std::span, but the constructor that takes two iterators
	// is currently buggy on MSVC.
	DataReader(const R&) -> DataReader<std::basic_string_view<std::ranges::range_value_t<R>>>;
}
