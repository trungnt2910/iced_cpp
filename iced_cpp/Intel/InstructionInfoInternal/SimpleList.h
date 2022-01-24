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

#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::InstructionInfoInternal
{
	template<typename T>
	class SimpleList
	{
	public:
		static SimpleList<T> Empty;
		std::vector<T> Array;
		std::int32_t ValidLength = 0;
		SimpleList(const std::vector<T>& array)
		{
			Array = array;
			ValidLength = 0;
		}

		SimpleList() = default;
	};
}
