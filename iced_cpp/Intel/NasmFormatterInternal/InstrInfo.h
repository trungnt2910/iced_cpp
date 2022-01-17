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

#include "../MemorySizeExtensions.h"
#include "../Iced.Intel.IcedConstants.h"
#include "../Mnemonic.g.h"
#include "../FormatterInternal/FormatterString.h"
#include "InstrOpInfoFlags.g.h"
#include "../MemorySize.g.h"
#include "../Register.g.h"
#include "../OpAccess.g.h"
#include "../Iced.Intel.Instruction.h"
#include "../FormatterOptions.h"
#include "../CodeSize.g.h"
#include "SignExtendInfo.g.h"
#include "../OpKind.g.h"
#include "../Code.g.h"
#include <string>
#include <vector>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel::NasmFormatterInternal
{
	// GENERATOR-BEGIN: InstrOpKind
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class InstrOpKind : std::uint8_t
	{
		Register,
		NearBranch16,
		NearBranch32,
		NearBranch64,
		FarBranch16,
		FarBranch32,
		Immediate8,
		Immediate8_2nd,
		Immediate16,
		Immediate32,
		Immediate64,
		Immediate8to16,
		Immediate8to32,
		Immediate8to64,
		Immediate32to64,
		MemorySegSI,
		MemorySegESI,
		MemorySegRSI,
		MemorySegDI,
		MemorySegEDI,
		MemorySegRDI,
		MemoryESDI,
		MemoryESEDI,
		MemoryESRDI,
		Memory,
		Sae,
		RnSae,
		RdSae,
		RuSae,
		RzSae,
		Rn,
		Rd,
		Ru,
		Rz,
		DeclareByte,
		DeclareWord,
		DeclareDword,
		DeclareQword
	};

	DEFINE_COMP(InstrOpKind)
		DEFINE_ARITH(InstrOpKind)

		// GENERATOR-END: InstrOpKind
		// GENERATOR-BEGIN: MemorySizeInfo
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class MemorySizeInfo
	{
		None,
		Word,
		Dword,
		Qword
	};

	DEFINE_COMP(MemorySizeInfo)
		DEFINE_ARITH(MemorySizeInfo)

		// GENERATOR-END: MemorySizeInfo
		// GENERATOR-BEGIN: FarMemorySizeInfo
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class FarMemorySizeInfo
	{
		None,
		Word,
		Dword
	};

	DEFINE_COMP(FarMemorySizeInfo)
		DEFINE_ARITH(FarMemorySizeInfo)

		// GENERATOR-END: FarMemorySizeInfo
		class InstrOpInfo
	{
	public:
		static constexpr std::int32_t TEST_RegisterBits = IcedConstants::RegisterBits;
		FormatterString Mnemonic;
		InstrOpInfoFlags Flags = static_cast<InstrOpInfoFlags>(0);
		std::uint8_t OpCount = 0;
		InstrOpKind Op0Kind = static_cast<InstrOpKind>(0);
		InstrOpKind Op1Kind = static_cast<InstrOpKind>(0);
		InstrOpKind Op2Kind = static_cast<InstrOpKind>(0);
		InstrOpKind Op3Kind = static_cast<InstrOpKind>(0);
		InstrOpKind Op4Kind = static_cast<InstrOpKind>(0);
		std::uint8_t Op0Register = 0;
		std::uint8_t Op1Register = 0;
		std::uint8_t Op2Register = 0;
		std::uint8_t Op3Register = 0;
		std::uint8_t Op4Register = 0;
		std::int8_t Op0Index = 0;
		std::int8_t Op1Index = 0;
		std::int8_t Op2Index = 0;
		std::int8_t Op3Index = 0;
		std::int8_t Op4Index = 0;
		/* readonly */
		Iced::Intel::MemorySize GetMemorySize() const;
		void SetMemorySize(Iced::Intel::MemorySize value);
		Register GetOpRegister(std::int32_t operand) const;
		InstrOpKind GetOpKind(std::int32_t operand) const;
		std::int32_t GetInstructionIndex(std::int32_t operand) const;
		bool TryGetOpAccess(std::int32_t operand, OpAccess& access);
		std::int32_t GetOperandIndex(std::int32_t instructionOperand) const;
		InstrOpInfo(FormatterString mnemonic, Instruction const instruction, InstrOpInfoFlags flags);

		InstrOpInfo() = default;
	};
	class InstrInfo
	{
	public:
		static constexpr std::int32_t OpAccess_INVALID = -1;
		static constexpr std::int32_t OpAccess_None = -static_cast<std::int32_t>(OpAccess::None + 2);
		static constexpr std::int32_t OpAccess_Read = -static_cast<std::int32_t>(OpAccess::Read + 2);
		static constexpr std::int32_t OpAccess_CondRead = -static_cast<std::int32_t>(OpAccess::CondRead + 2);
		static constexpr std::int32_t OpAccess_Write = -static_cast<std::int32_t>(OpAccess::Write + 2);
		static constexpr std::int32_t OpAccess_CondWrite = -static_cast<std::int32_t>(OpAccess::CondWrite + 2);
		static constexpr std::int32_t OpAccess_ReadWrite = -static_cast<std::int32_t>(OpAccess::ReadWrite + 2);
		static constexpr std::int32_t OpAccess_ReadCondWrite = -static_cast<std::int32_t>(OpAccess::ReadCondWrite + 2);
		static constexpr std::int32_t OpAccess_NoMemAccess = -static_cast<std::int32_t>(OpAccess::NoMemAccess + 2);
		virtual void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) = 0;
	protected:
		static std::int32_t GetBitness(CodeSize codeSize);
	};
	class SimpleInstrInfo final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo(const std::string& mnemonic);
		SimpleInstrInfo(const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_cc final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t ccIndex = 0;
		/* readonly */
		std::vector<FormatterString> mnemonics;
	public:
		SimpleInstrInfo_cc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_push_imm8 final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		SignExtendInfo sexInfo = static_cast<SignExtendInfo>(0);
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_push_imm8(std::int32_t bitness, SignExtendInfo sexInfo, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_push_imm final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		SignExtendInfo sexInfo = static_cast<SignExtendInfo>(0);
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_push_imm(std::int32_t bitness, SignExtendInfo sexInfo, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_SignExt final : public InstrInfo
	{
		/* readonly */
	private:
		SignExtendInfo sexInfoReg = static_cast<SignExtendInfo>(0);
		/* readonly */
		SignExtendInfo sexInfoMem = static_cast<SignExtendInfo>(0);
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_SignExt(SignExtendInfo sexInfo, const std::string& mnemonic, InstrOpInfoFlags flags);
		SimpleInstrInfo_SignExt(SignExtendInfo sexInfoReg, SignExtendInfo sexInfoMem, const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_imul final : public InstrInfo
	{
		/* readonly */
	private:
		SignExtendInfo sexInfo = static_cast<SignExtendInfo>(0);
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_imul(SignExtendInfo sexInfo, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_AamAad final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_AamAad(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_String final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_String(const std::string& mnemonic);
	private:
		static InstrOpInfoFlags GetAddressSizeFlags(OpKind opKind);
	public:
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_XLAT final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_XLAT(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_nop final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		Register register_ = static_cast<Register>(0);
	public:
		SimpleInstrInfo_nop(std::int32_t bitness, const std::string& mnemonic, Register register_);
	private:
		static FormatterString str_xchg;
	public:
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_STIG1 final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		bool pseudoOp = false;
	public:
		SimpleInstrInfo_STIG1(const std::string& mnemonic, bool pseudoOp);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_STIG2 final : public InstrInfo
	{
		/* readonly */
	private:
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		bool pseudoOp = false;
	public:
		SimpleInstrInfo_STIG2(const std::string& mnemonic, bool pseudoOp);
		SimpleInstrInfo_STIG2(const std::string& mnemonic, InstrOpInfoFlags flags);
	private:
		SimpleInstrInfo_STIG2(const std::string& mnemonic, InstrOpInfoFlags flags, bool pseudoOp);
	public:
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_as final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_as(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_maskmovq final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_maskmovq(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_pblendvb final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		MemorySize memSize = static_cast<MemorySize>(0);
	public:
		SimpleInstrInfo_pblendvb(const std::string& mnemonic, MemorySize memSize);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_reverse final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_reverse(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_OpSize final : public InstrInfo
	{
		/* readonly */
	private:
		CodeSize codeSize = static_cast<CodeSize>(0);
		/* readonly */
		std::vector<FormatterString> mnemonics;
	public:
		SimpleInstrInfo_OpSize(CodeSize codeSize, const std::string& mnemonic, const std::string& mnemonic16, const std::string& mnemonic32, const std::string& mnemonic64);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_OpSize2_bnd final : public InstrInfo
	{
		/* readonly */
	private:
		std::vector<FormatterString> mnemonics;
	public:
		SimpleInstrInfo_OpSize2_bnd(const std::string& mnemonic, const std::string& mnemonic16, const std::string& mnemonic32, const std::string& mnemonic64);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_OpSize3 final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonicDefault;
		/* readonly */
		FormatterString mnemonicFull;
	public:
		SimpleInstrInfo_OpSize3(std::int32_t bitness, const std::string& mnemonicDefault, const std::string& mnemonicFull);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_os(std::int32_t bitness, const std::string& mnemonic);
		SimpleInstrInfo_os(std::int32_t bitness, const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_mem final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_os_mem(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_mem2 final : public InstrInfo
	{
		/* readonly */
	private:
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
		/* readonly */
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_os_mem2(std::int32_t bitness, const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_mem_reg16 final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_os_mem_reg16(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_jcc final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		std::int32_t ccIndex = 0;
		/* readonly */
		std::vector<FormatterString> mnemonics;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_os_jcc(std::int32_t bitness, std::int32_t ccIndex, const std::vector<std::string>& mnemonics);
		SimpleInstrInfo_os_jcc(std::int32_t bitness, std::int32_t ccIndex, const std::vector<std::string>& mnemonics, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_loop final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		std::int32_t ccIndex = 0;
		/* readonly */
		Register register_ = static_cast<Register>(0);
		/* readonly */
		std::vector<FormatterString> mnemonics;
	public:
		SimpleInstrInfo_os_loop(std::int32_t bitness, std::int32_t ccIndex, Register register_, const std::vector<std::string>& mnemonics);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_os_call final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		bool canHaveBndPrefix = false;
	public:
		SimpleInstrInfo_os_call(std::int32_t bitness, const std::string& mnemonic, bool canHaveBndPrefix);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_far final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_far(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_far_mem final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_far_mem(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_movabs final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_movabs(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_er final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t erIndex = 0;
		/* readonly */
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic);
		SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
		static void MoveOperands(InstrOpInfo& info, std::int32_t index, InstrOpKind newOpKind);
	};
	class SimpleInstrInfo_sae final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t saeIndex = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_sae(std::int32_t saeIndex, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_bcst final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flagsNoBroadcast = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_bcst(const std::string& mnemonic, InstrOpInfoFlags flagsNoBroadcast);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_bnd final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		InstrOpInfoFlags flags = static_cast<InstrOpInfoFlags>(0);
	public:
		SimpleInstrInfo_bnd(const std::string& mnemonic, InstrOpInfoFlags flags);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_pops final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		std::vector<FormatterString> pseudo_ops;
	public:
		SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
		static void RemoveLastOp(InstrOpInfo& info);
	};
	class SimpleInstrInfo_pclmulqdq final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		std::vector<FormatterString> pseudo_ops;
	public:
		SimpleInstrInfo_pclmulqdq(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_Reg16 final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_Reg16(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_Reg32 final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_Reg32(const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_invlpga final : public InstrInfo
	{
		/* readonly */
	private:
		std::int32_t bitness = 0;
		/* readonly */
		FormatterString mnemonic;
	public:
		SimpleInstrInfo_invlpga(std::int32_t bitness, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
	class SimpleInstrInfo_DeclareData final : public InstrInfo
	{
		/* readonly */
	private:
		FormatterString mnemonic;
		/* readonly */
		InstrOpKind opKind = static_cast<InstrOpKind>(0);
	public:
		SimpleInstrInfo_DeclareData(Code code, const std::string& mnemonic);
		void GetOpInfo(FormatterOptions* options, Instruction const instruction, InstrOpInfo& info) override;
	};
}
