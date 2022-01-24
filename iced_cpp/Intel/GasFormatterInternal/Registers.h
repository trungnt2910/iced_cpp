// C# helper headers

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

#include "../Register.g.h"
#include "../FormatterInternal/FormatterString.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel::GasFormatterInternal
{
	class Registers final
	{
	public:
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4996)
		static constexpr Register Register_ST = Register::DontUse0;
#pragma warning (pop)
#endif
		static std::vector<FormatterString> AllRegistersNaked;
		static std::vector<FormatterString> AllRegisters;
	private:
		static std::vector<FormatterString> GetRegistersWithPrefix();
	};
}
