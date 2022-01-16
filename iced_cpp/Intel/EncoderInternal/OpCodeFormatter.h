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

#include "../OpCodeInfo.h"
#include "../OpCodeOperandKind.g.h"
#include <string>
#include <csharp/exceptionhelper.h>
#include <cassert>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	// GENERATOR-BEGIN: LKind
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class LKind : std::uint8_t
	{
		None,
		/// <summary>.128, .256, .512</summary>
		L128,
		/// <summary>.L0, .L1</summary>
		L0,
		/// <summary>.LZ</summary>
		LZ
	};

	DEFINE_COMP(LKind)
		DEFINE_ARITH(LKind)

		// GENERATOR-END: LKind
		/* readonly */
		class OpCodeFormatter
	{
		/* readonly */
	private:
		OpCodeInfo* opCode;
		/* readonly */
		StringBuilder* sb;
		/* readonly */
		LKind lkind = static_cast<LKind>(0);
		/* readonly */
		bool hasModrmInfo = false;
	public:
		OpCodeFormatter(OpCodeInfo* opCode, StringBuilder* sb, LKind lkind, bool hasModrmInfo);
		std::string Format();
	private:
		void AppendHexByte(std::uint8_t value);
		void AppendOpCode(std::uint32_t value, std::int32_t valueLen, bool sep);
		void AppendTable(bool sep);
		bool HasModRM();
		bool HasVsib();
		OpCodeOperandKind GetOpCodeBitsOperand();
		bool TryGetModrmInfo(bool& isRegOnly, std::int32_t& rrr, std::int32_t& bbb);
		void AppendBits(const std::string& name, std::int32_t bits, std::int32_t numBits);
		void AppendRest();
		std::string Format_Legacy();
		std::string Format_3DNow();
		std::string FormatVecEncoding(const std::string& encodingName);

		OpCodeFormatter() = default;
	};
}