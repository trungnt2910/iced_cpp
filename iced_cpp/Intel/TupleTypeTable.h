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

#include "TupleType.g.h"
#include <vector>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class TupleTypeTable final
	{
	public:
		static std::vector<std::uint8_t> tupleTypeData;
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static uint GetDisp8N(TupleType tupleType, bool bcst)
		static std::uint32_t GetDisp8N(TupleType tupleType, bool bcst);
	};
}
