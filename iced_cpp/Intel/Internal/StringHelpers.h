#pragma once

#include <algorithm>
#include <type_traits>

namespace Iced::Intel::Internal
{
	class StringHelpers
	{
	public:
		static constexpr char ToUpper(char ch)
		{
			return (('a' <= ch) && (ch <= 'z')) ? 'A' + (ch - 'a') : ch;
		}
		static constexpr char ToLower(char ch)
		{
			return (('A' <= ch) && (ch <= 'Z')) ? 'a' + (ch - 'A') : ch;
		}
		static constexpr std::string ToUpper(const std::string& s)
		{
			std::string ss;
			ss.reserve(s.size());
			std::transform(s.begin(), s.end(), std::back_insert_iterator(ss), (char(*)(char))ToUpper);
			return ss;
		}
		// FASTEST ToHex I can loot from the internet
		// that DOESN'T use static memory.
		static constexpr std::string ToHex(std::uint8_t byte)
		{
			std::uint_fast16_t i = byte;
			i = (i | (i << 4u)) & 0x0F0Fu;
			std::uint_fast16_t mask = ((i + 0x0606u) >> 4) & 0x0101u;
			i |= 0x3030u;
			i += 0x07u * mask;

			std::string result;
			result.resize(2);
			result[0] = i >> 8u;
			result[1] = i & 0xFF;

			return result;
		}
		static constexpr std::string ToDec(std::uint32_t i)
		{
			std::string result;
			while (i)
			{
				result.push_back(i % 10 + '0');
				i /= 10;
			}
			std::reverse(result.begin(), result.end());
			return result;
		}
	};
}