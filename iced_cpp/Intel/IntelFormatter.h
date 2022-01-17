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

#include "Formatter.h"
#include "FormatterOptions.h"
#include "ISymbolResolver.h"
#include "IFormatterOptionsProvider.h"
#include "FormatterInternal/FormatterString.h"
#include "IntelFormatterInternal/InstrInfo.h"
#include "IntelFormatterInternal/MemorySizes.h"
#include "MasmFormatterInternal/MemorySizes.h"
#include "NasmFormatterInternal/MemorySizes.h"
#include "NumberFormatter.h"
#include "FormatterOutput.h"
#include "Iced.Intel.Instruction.h"
#include "OpAccess.g.h"
#include "IntelFormatterInternal/InstrOpInfoFlags.g.h"
#include "Register.g.h"
#include "MemorySize.g.h"
#include <string>
#include <vector>
#include <limits>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
using namespace Iced::Intel::IntelFormatterInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Intel (XED) formatter
	/// </summary>
	class IntelFormatter final : public Formatter
	{
		/// <summary>
		/// Gets the formatter options
		/// </summary>
	public:
		FormatterOptions* GetOptions() const override;
		/* readonly */
	private:
		FormatterOptions* options;
		/* readonly */
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: ISymbolResolver? symbolResolver;
		ISymbolResolver* symbolResolver;
		/* readonly */
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: IFormatterOptionsProvider? optionsProvider;
		IFormatterOptionsProvider* optionsProvider;
		/* readonly */
		std::vector<FormatterString> allRegisters;
		/* readonly */
		std::vector<InstrInfo*> instrInfos;
		/* readonly */
		std::vector<MemorySizes::Info> allMemorySizes;
		/* readonly */
		NumberFormatter numberFormatter;
		/* readonly */
		std::vector<FormatterString> opSizeStrings;
		/* readonly */
		std::vector<FormatterString> addrSizeStrings;
		/* readonly */
		std::vector<FormatterString> rcStrings;
		/* readonly */
		std::vector<FormatterString> rcSaeStrings;
		/* readonly */
		std::vector<std::vector<FormatterString>> branchInfos;
		/* readonly */
		std::vector<std::string> scaleNumbers;
		/* readonly */
		std::vector<FormatterString> mvexRegMemConsts32;
		/* readonly */
		std::vector<FormatterString> mvexRegMemConsts64;
		/// <summary>
		/// Constructor
		/// </summary>
	public:
		IntelFormatter();
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="symbolResolver">Symbol resolver or null</param>
		/// <param name="optionsProvider">Operand options provider or null</param>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public IntelFormatter(ISymbolResolver? symbolResolver, System.Nullable<IFormatterOptionsProvider> optionsProvider = null) : this(null, symbolResolver, optionsProvider)
		IntelFormatter(ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider = nullptr);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="options">Formatter options or null</param>
		/// <param name="symbolResolver">Symbol resolver or null</param>
		/// <param name="optionsProvider">Operand options provider or null</param>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public IntelFormatter(FormatterOptions? options, System.Nullable<ISymbolResolver> symbolResolver = null, System.Nullable<IFormatterOptionsProvider> optionsProvider = null)
		IntelFormatter(FormatterOptions* options, ISymbolResolver* symbolResolver = nullptr, IFormatterOptionsProvider* optionsProvider = nullptr);
	private:
		static FormatterString str_bnd;
		static FormatterString str_far;
		static FormatterString str_hint_not_taken;
		static FormatterString str_hint_taken;
		static FormatterString str_lock;
		static FormatterString str_notrack;
		static FormatterString str_rep;
		static std::vector<FormatterString> str_repe;
		static std::vector<FormatterString> str_repne;
		static FormatterString str_sae;
		static FormatterString str_xacquire;
		static FormatterString str_xrelease;
		static FormatterString str_z;
		static std::vector<FormatterString> s_opSizeStrings;
		static std::vector<FormatterString> s_addrSizeStrings;
		static std::vector<FormatterString> s_rcStrings;
		static std::vector<FormatterString> s_rcSaeStrings;
		static std::vector<std::vector<FormatterString>> s_branchInfos;
		static std::vector<std::string> s_scaleNumbers;
		static std::vector<FormatterString> s_mvexRegMemConsts32;
		static std::vector<FormatterString> s_mvexRegMemConsts64;
		static FormatterString str_eh;
		/// <summary>
		/// Formats the mnemonic and/or any prefixes
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		/// <param name="options">Options</param>
	public:
		void FormatMnemonic(Instruction const instruction, FormatterOutput* output, FormatMnemonicOptions options) override;
		/// <summary>
		/// Gets the number of operands that will be formatted. A formatter can add and remove operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		std::int32_t GetOperandCount(Instruction const instruction) override;
		/// <summary>
		/// Returns the operand access but only if it's an operand added by the formatter. If it's an
		/// operand that is part of <see cref="Instruction"/>, you should call eg. <see cref="InstructionInfoFactory.GetInfo(in Instruction)"/>.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		/// <param name="access">Updated with operand access if successful</param>
		/// <returns></returns>
		bool TryGetOpAccess(Instruction const instruction, std::int32_t operand, OpAccess& access) override;
		/// <summary>
		/// Converts a formatter operand index to an instruction operand index. Returns -1 if it's an operand added by the formatter
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		/// <returns></returns>
		std::int32_t GetInstructionOperand(Instruction const instruction, std::int32_t operand) override;
		/// <summary>
		/// Converts an instruction operand index to a formatter operand index. Returns -1 if the instruction operand isn't used by the formatter
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="instructionOperand">Instruction operand</param>
		/// <returns></returns>
		std::int32_t GetFormatterOperand(Instruction const instruction, std::int32_t instructionOperand) override;
		/// <summary>
		/// Formats an operand. This is a formatter operand and not necessarily a real instruction operand.
		/// A formatter can add and remove operands.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		void FormatOperand(Instruction const instruction, FormatterOutput* output, std::int32_t operand) override;
		/// <summary>
		/// Formats an operand separator
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		void FormatOperandSeparator(Instruction const instruction, FormatterOutput* output) override;
		/// <summary>
		/// Formats all operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		void FormatAllOperands(Instruction const instruction, FormatterOutput* output) override;
		/// <summary>
		/// Formats the whole instruction: prefixes, mnemonic, operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		void Format(Instruction const instruction, FormatterOutput* output) override;
	private:
		void FormatMnemonic(Instruction const instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t& column, FormatMnemonicOptions mnemonicOptions);
		bool ShowSegmentPrefix(Instruction const instruction, InstrOpInfo const opInfo);
		void FormatPrefix(FormatterOutput* output, Instruction const instruction, std::int32_t& column, FormatterString prefix, PrefixKind prefixKind, bool& needSpace);
		void FormatOperands(Instruction const instruction, FormatterOutput* output, InstrOpInfo const opInfo);
		void FormatOperand(Instruction const instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t operand);
		void FormatFlowControl(FormatterOutput* output, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions);
		void FormatDecorator(FormatterOutput* output, Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterString text, DecoratorKind decorator);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] string ToRegisterString(Register reg)
		std::string ToRegisterString(Register reg);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.NoInlining)] void FormatRegister(FormatterOutput output, in Instruction instruction, int operand, int instructionOperand, Register reg)
		void FormatRegister(FormatterOutput* output, Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, Register reg);
		void FormatMemory(FormatterOutput* output, Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize, InstrOpInfoFlags flags);
		void FormatMemorySize(FormatterOutput* output, SymbolResult& symbol, MemorySize memSize, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions, bool useSymbol);
		bool IsSameMemSize(const std::vector<FormatterString>& memSizeStrings, SymbolResult& symbol);
		static bool IsSameMemSize(const std::vector<FormatterString>& a, const std::vector<FormatterString>& b);
		void FormatKeyword(FormatterOutput* output, FormatterString keyword);
		/// <summary>
		/// Formats a register
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
	public:
		std::string Format(Register register_) override;
		/// <summary>
		/// Formats a <see cref="sbyte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatInt8(std::int8_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="short"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatInt16(std::int16_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="int"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatInt32(std::int32_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="long"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatInt64(std::int64_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="byte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatUInt8(std::uint8_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="ushort"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatUInt16(std::uint16_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="uint"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatUInt32(std::uint32_t value, NumberFormattingOptions const numberOptions) override;
		/// <summary>
		/// Formats a <see cref="ulong"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		std::string FormatUInt64(std::uint64_t value, NumberFormattingOptions const numberOptions) override;
	};
}
