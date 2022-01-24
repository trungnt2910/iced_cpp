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

#include "../FormatterInternal/FormatterString.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel::MasmFormatterInternal
{
	class MemorySizes final
	{
	public:
		static std::vector<FormatterString> dword_ptr;
		static std::vector<FormatterString> qword_ptr;
		static std::vector<FormatterString> mmword_ptr;
		static std::vector<FormatterString> xmmword_ptr;
		static std::vector<FormatterString> oword_ptr;
	public:
		class Info
		{
		public:
			bool isBroadcast = false;
			std::int32_t size = 0;
			std::vector<FormatterString> keywords;
			Info(bool isBroadcast, std::int32_t size, const std::vector<FormatterString>& keywords);

			Info() = default;
		};
	public:
		static std::vector<Info> AllMemorySizes;
	private:
		static std::vector<Info> GetMemorySizes();
	};
}
