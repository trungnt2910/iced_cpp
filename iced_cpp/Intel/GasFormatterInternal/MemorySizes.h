// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "../FormatterInternal/FormatterString.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel::GasFormatterInternal
{
	class MemorySizes final
	{
	public:
		static std::vector<FormatterString> AllMemorySizes;
	private:
		static std::vector<FormatterString> GetMemorySizes();
	};
}
