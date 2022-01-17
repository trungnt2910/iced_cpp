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
#include <string_view>
#include <vector>

#pragma once

#include "../OpCodeInfo.h"
#include "OpCodeInfosEnums.h"
#include "../MemorySize.g.h"
#include "../Code.g.h"
#include <string>
#include <vector>
#include <csharp/exceptionhelper.h>
#include <cassert>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	class InstructionFormatter
	{
		/* readonly */
	private:
		OpCodeInfo* opCode;
		/* readonly */
		StringBuilder* sb;
		/* readonly */
		std::int32_t r32_count = 0;
		/* readonly */
		std::int32_t r64_count = 0;
		/* readonly */
		std::int32_t bnd_count = 0;
		/* readonly */
		std::int32_t startOpIndex = 0;
		std::int32_t r32_index = 0, r64_index = 0, bnd_index = 0;
		std::int32_t k_index = 0;
		std::int32_t vec_index = 0;
		std::int32_t tmm_index = 0;
		/* readonly */
		std::int32_t opCount = 0;
		// true: k2 {k1}, false: k1 {k2}
		/* readonly */
		bool opMaskIsK1 = false;
		/* readonly */
		bool noVecIndex = false;
		/* readonly */
		bool swapVecIndex12 = false;
		/* readonly */
		bool noGprSuffix = false;
		/* readonly */
		bool vecIndexSameAsOpIndex = false;
		static constexpr std::array ConvFnNames = std::to_array<std::string_view> ({ "Sf32", "Sf64", "Si32", "Si64", "Uf32", "Uf64", "Ui32", "Ui64", "Df32", "Df64", "Di32", "Di64" });
		std::int32_t GetKIndex();
		std::int32_t GetBndIndex();
		std::int32_t GetVecIndex(std::int32_t opIndex);
		std::int32_t GetTmmIndex();
	public:
		InstructionFormatter(OpCodeInfo* opCode, InstrStrFmtOption fmtOption, StringBuilder* sb);
	private:
		MemorySize GetMemorySize(bool isBroadcast);
	public:
		std::string Format();
	private:
		void WriteMemorySize(MemorySize memorySize);
		bool IsSgdtOrSidt();
		void WriteRegister(const std::string& register_);
		void WriteRegOp(const std::string& register_);
		void WriteRegOp(const std::string& register_, std::int32_t index);
		void WriteDecorator(const std::string& decorator);
		void WriteRegDecorator(const std::string& register_, std::int32_t index);
		void AppendGprSuffix(std::int32_t count, std::int32_t& index);
		void WriteOpSeparator();
		void Write(const std::string& s, bool upper);
		void WriteGprMem(std::int32_t regSize);
		void WriteRegMem(const std::string& register_, std::int32_t index);
		void WriteMemory();
		void WriteMemory(bool isBroadcast);
		static bool IsFpuInstruction(Code code);

		InstructionFormatter() = default;
	};
}
