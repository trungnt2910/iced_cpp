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
namespace Iced::Intel::MasmFormatterInternal
{
	enum class InstrOpInfoFlags : ushort
	{
		None = 0x00000000,
		MemSize_Mask = 0x00000007,
		MemSize_Sse = 0x00000000,
		MemSize_Mmx = 0x00000001,
		MemSize_Normal = 0x00000002,
		MemSize_Nothing = 0x00000003,
		MemSize_XmmwordPtr = 0x00000004,
		MemSize_DwordOrQword = 0x00000005,
		ShowNoMemSize_ForceSize = 0x00000008,
		ShowMinMemSize_ForceSize = 0x00000010,
		JccNotTaken = 0x00000020,
		JccTaken = 0x00000040,
		BndPrefix = 0x00000080,
		IgnoreIndexReg = 0x00000100,
		MnemonicIsDirective = 0x00000200
	};
	DEFINE_FLAGS(InstrOpInfoFlags)
		DEFINE_COMP(InstrOpInfoFlags)
		DEFINE_ARITH(InstrOpInfoFlags)

}