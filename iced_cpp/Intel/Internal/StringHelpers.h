#pragma once

#include <algorithm>
#include <concepts>
#include <string>
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
		static constexpr std::string ToLower(const std::string& s)
		{
			std::string ss;
			ss.reserve(s.size());
			std::transform(s.begin(), s.end(), std::back_insert_iterator(ss), (char(*)(char))ToLower);
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
		template <std::unsigned_integral U>
		static constexpr std::string ToDec(U i)
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
		template <std::signed_integral I>
		static constexpr std::string ToDec(I i)
		{
			return (i < 0) ? "-" + ToDec((std::make_unsigned_t<I>)-i) : ToDec((std::make_unsigned_t<I>)i);
		}
		/// <summary>
		/// constexpr version of strlen
		/// </summary>
		/// <param name="i">pointer to c-style string</param>
		/// <returns></returns>
		static constexpr std::size_t Length(const char* ch)
		{
			return std::char_traits<char>::length(ch);
		}
		/// <summary>
		/// constexpr version of strcpy
		/// </summary>
		/// <param name="src">Source</param>
		/// <param name="dst">Destination</param>
		/// <returns>Number of chars copied, excluding the null terminator.</returns>
		static constexpr std::size_t Copy(const char* src, char* dst)
		{
			std::size_t len = Length(src);
			std::char_traits<char>::copy(dst, src, len);
			return len;
		}
	};
}