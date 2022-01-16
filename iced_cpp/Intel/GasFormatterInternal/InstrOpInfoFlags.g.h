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
namespace Iced::Intel::GasFormatterInternal
{
	enum class InstrOpInfoFlags : ushort
	{
		None = 0x00000000,
		MnemonicSuffixIfMem = 0x00000001,
		SizeOverrideMask = 0x00000003,
		OpSizeShift = 0x00000001,
		OpSize16 = 0x00000002,
		OpSize32 = 0x00000004,
		OpSize64 = 0x00000006,
		AddrSizeShift = 0x00000003,
		AddrSize16 = 0x00000008,
		AddrSize32 = 0x00000010,
		AddrSize64 = 0x00000018,
		IndirectOperand = 0x00000020,
		OpSizeIsByteDirective = 0x00000040,
		KeepOperandOrder = 0x00000080,
		JccNotTaken = 0x00000100,
		JccTaken = 0x00000200,
		BndPrefix = 0x00000400,
		IgnoreIndexReg = 0x00000800,
		MnemonicIsDirective = 0x00001000
	};
	DEFINE_FLAGS(InstrOpInfoFlags)
		DEFINE_COMP(InstrOpInfoFlags)
		DEFINE_ARITH(InstrOpInfoFlags)

}