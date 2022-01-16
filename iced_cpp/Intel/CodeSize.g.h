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

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	/// <summary>The code size (16/32/64) that was used when an instruction was decoded</summary>
	enum class CodeSize
	{
		/// <summary>Unknown size</summary>
		Unknown = 0,
		/// <summary>16-bit code</summary>
		Code16 = 1,
		/// <summary>32-bit code</summary>
		Code32 = 2,
		/// <summary>64-bit code</summary>
		Code64 = 3
	};

	DEFINE_COMP(CodeSize)
		DEFINE_ARITH(CodeSize)

}
