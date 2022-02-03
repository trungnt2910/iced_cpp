// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once
#if defined(ENCODER) && defined(OPCODE_INFO)

#include "OpCodeInfosEnums.h"
#include "../MemorySize.g.h"
#include "../Code.g.h"
#include <string>
#include <vector>
#include <cassert>

namespace Iced::Intel
{
	class OpCodeInfo;
}

namespace Iced::Intel::EncoderInternal
{
	class InstructionFormatter
	{
	private:
		const bool isConstexprEval = false;
		bool ownsSb = false;
		const OpCodeInfo* opCode = nullptr;
		std::string* sb = nullptr;
		std::int32_t r32_count = 0;
		std::int32_t r64_count = 0;
		std::int32_t bnd_count = 0;
		std::int32_t startOpIndex = 0;
		std::int32_t r32_index = 0, r64_index = 0, bnd_index = 0;
		std::int32_t k_index = 0;
		std::int32_t vec_index = 0;
		std::int32_t tmm_index = 0;
		std::int32_t opCount = 0;
		// true: k2 {k1}, false: k1 {k2}
		bool opMaskIsK1 = false;
		bool noVecIndex = false;
		bool swapVecIndex12 = false;
		bool noGprSuffix = false;
		bool vecIndexSameAsOpIndex = false;
		static constexpr std::array ConvFnNames = std::to_array<std::string_view> ({ "Sf32", "Sf64", "Si32", "Si64", "Uf32", "Uf64", "Ui32", "Ui64", "Df32", "Df64", "Di32", "Di64" });
		constexpr std::int32_t GetKIndex();
		constexpr std::int32_t GetBndIndex();
		constexpr std::int32_t GetVecIndex(std::int32_t opIndex);
		constexpr std::int32_t GetTmmIndex();
	public:
		inline InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption, std::string& sb);
		constexpr InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption);
		constexpr ~InstructionFormatter();
	private:
		constexpr InstructionFormatter(const OpCodeInfo& opCode, InstrStrFmtOption fmtOption, bool constructString);
		constexpr MemorySize GetMemorySize(bool isBroadcast);
	public:
		constexpr std::string Format();
	private:
		constexpr void WriteMemorySize(MemorySize memorySize);
		constexpr bool IsSgdtOrSidt();
		constexpr void WriteRegister(const std::string& register_);
		constexpr void WriteRegOp(const std::string& register_);
		constexpr void WriteRegOp(const std::string& register_, std::int32_t index);
		constexpr void WriteDecorator(const std::string& decorator);
		constexpr void WriteRegDecorator(const std::string& register_, std::int32_t index);
		constexpr void AppendGprSuffix(std::int32_t count, std::int32_t& index);
		constexpr void WriteOpSeparator();
		constexpr void Write(const std::string& s, bool upper);
		constexpr void WriteGprMem(std::int32_t regSize);
		constexpr void WriteRegMem(const std::string& register_, std::int32_t index);
		constexpr void WriteMemory();
		constexpr void WriteMemory(bool isBroadcast);
		constexpr static bool IsFpuInstruction(Code code);

		constexpr InstructionFormatter() = default;
	};
}
#endif