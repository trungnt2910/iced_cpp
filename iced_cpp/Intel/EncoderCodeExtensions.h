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

#include "Code.g.h"
#include "OpCodeInfo.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::EncoderInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Extensions
	/// </summary>
	class EncoderCodeExtensions final
	{
		/// <summary>
		/// Gets a <see cref="OpCodeInfo"/>
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static OpCodeInfo ToOpCode(this Code code)
		static OpCodeInfo* ToOpCode(Code code);
	};
}