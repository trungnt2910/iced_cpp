#pragma once

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::FormatterInternal
{
	/* readonly */
	class FormatterString
	{
	private:
		std::string lower;
		std::string upper;
		// std::toupper is not constexpr
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
				if (ch != ToLower(ch))
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
