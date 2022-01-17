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

#include <type_traits>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class Static final
	{
		/// <summary>
		/// Call it like so:<br/>
		/// <br/>
		/// <c>Static.Assert(SomeClass.SomeConstant == 123 ? 0 : -1);</c>
		/// </summary>
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [Conditional("E3967789CA584C48B3D02600CAB3C7B2")] public static void Assert(byte ignored)
		static constexpr void Assert(std::uint8_t ignored)
		{
			if (std::is_constant_evaluated())
			{
				if (ignored != 0)
				{
					throw std::exception("Static::Assert error.");
				}
			}
		}
	};
}
