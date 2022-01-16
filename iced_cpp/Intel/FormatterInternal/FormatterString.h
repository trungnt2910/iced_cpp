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
#include <vector>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::FormatterInternal
{
	/* readonly */
	class FormatterString
	{
		/* readonly */
	private:
		std::string lower;
		/* readonly */
		std::string upper;
	public:
		std::int32_t GetLength() const;
		FormatterString(const std::string& lower);
		static std::vector<FormatterString> Create(std::vector<std::string>& strings);
		std::string Get(bool upper);
		std::string GetLower() const;

		FormatterString() = default;
	};
}
