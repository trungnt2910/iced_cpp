// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <vector>

#include "../CharHelpers.h"

namespace Iced::Intel::FormatterInternal
{
	/* readonly */
	class FormatterString
	{
	private:
		std::string lower;
		std::string upper;
		// std::toupper is not constexpr
		static constexpr std::string ToUpper(const std::string& s)
		{
			std::string ss;
			ss.reserve(s.size());
			std::transform(s.begin(), s.end(), std::back_insert_iterator(ss), (char(*)(char))CharHelpers::ToUpper);
			return ss;
		}
	public:
		constexpr std::int32_t GetLength() const
		{
			return (std::int32_t)lower.length();
		}
		constexpr FormatterString(const std::string& lower) : lower(lower), upper(ToUpper(lower))
		{
#if !defined(NDEBUG)
			for (auto ch : lower)
			{
				if (ch != CharHelpers::ToLower(ch))
				{
					throw std::invalid_argument("Not a lowercase string: " + lower);
				}
			}
#endif
		}
		constexpr const std::string& Get(bool getUpper) const
		{
			return (getUpper) ? upper : lower;
		}
		constexpr const std::string& GetLower() const
		{
			return lower;
		}
		static constexpr std::vector<FormatterString> Create(const std::vector<std::string>& strings)
		{
			auto res = std::vector<FormatterString>(strings.size());
			for (std::int32_t i = 0; i < strings.size(); i++)
			{
				res[i] = FormatterString(strings[i]);
			}
			return res;
		}
		constexpr FormatterString() = default;
	};
}
