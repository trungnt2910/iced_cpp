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

#include "FormatterOptions.h"
#include "FormatterOutput.h"
#include "Iced.Intel.Instruction.h"
#include "OpAccess.g.h"
#include "Register.g.h"
#include "IFormatterOptionsProvider.h"
#include <string>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Formats instructions
	/// </summary>
	class Formatter
	{
		/// <summary>
		/// Gets the formatter options
		/// </summary>
	public:
		virtual FormatterOptions* GetOptions() const = 0;
		/// <summary>
		/// Formats the mnemonic and any prefixes
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		void FormatMnemonic(Instruction const instruction, FormatterOutput* output);
		/// <summary>
		/// Formats the mnemonic and/or any prefixes
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		/// <param name="options">Options</param>
		virtual void FormatMnemonic(Instruction const instruction, FormatterOutput* output, FormatMnemonicOptions options) = 0;
		/// <summary>
		/// Gets the number of operands that will be formatted. A formatter can add and remove operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		virtual std::int32_t GetOperandCount(Instruction const instruction) = 0;
		/// <summary>
		/// Returns the operand access but only if it's an operand added by the formatter. If it's an
		/// operand that is part of <see cref="Instruction"/>, you should call eg. <see cref="InstructionInfoFactory.GetInfo(in Instruction)"/>.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		/// <param name="access">Updated with operand access if successful</param>
		/// <returns></returns>
		virtual bool TryGetOpAccess(Instruction const instruction, std::int32_t operand, OpAccess& access) = 0;
		/// <summary>
		/// Converts a formatter operand index to an instruction operand index. Returns -1 if it's an operand added by the formatter
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		/// <returns></returns>
		virtual std::int32_t GetInstructionOperand(Instruction const instruction, std::int32_t operand) = 0;
		/// <summary>
		/// Converts an instruction operand index to a formatter operand index. Returns -1 if the instruction operand isn't used by the formatter
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="instructionOperand">Instruction operand</param>
		/// <returns></returns>
		virtual std::int32_t GetFormatterOperand(Instruction const instruction, std::int32_t instructionOperand) = 0;
		/// <summary>
		/// Formats an operand. This is a formatter operand and not necessarily a real instruction operand.
		/// A formatter can add and remove operands.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.
		/// See <see cref="GetOperandCount(in Instruction)"/></param>
		virtual void FormatOperand(Instruction const instruction, FormatterOutput* output, std::int32_t operand) = 0;
		/// <summary>
		/// Formats an operand separator
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		virtual void FormatOperandSeparator(Instruction const instruction, FormatterOutput* output) = 0;
		/// <summary>
		/// Formats all operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		virtual void FormatAllOperands(Instruction const instruction, FormatterOutput* output) = 0;
		/// <summary>
		/// Formats the whole instruction: prefixes, mnemonic, operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		virtual void Format(Instruction const instruction, FormatterOutput* output) = 0;
		/// <summary>
		/// Formats a register
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		virtual std::string Format(Register register_) = 0;
		/// <summary>
		/// Formats a <see cref="sbyte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatInt8(std::int8_t value);
		/// <summary>
		/// Formats a <see cref="short"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatInt16(std::int16_t value);
		/// <summary>
		/// Formats a <see cref="int"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatInt32(std::int32_t value);
		/// <summary>
		/// Formats a <see cref="long"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatInt64(std::int64_t value);
		/// <summary>
		/// Formats a <see cref="byte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatUInt8(std::uint8_t value);
		/// <summary>
		/// Formats a <see cref="ushort"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatUInt16(std::uint16_t value);
		/// <summary>
		/// Formats a <see cref="uint"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatUInt32(std::uint32_t value);
		/// <summary>
		/// Formats a <see cref="ulong"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <returns></returns>
		std::string FormatUInt64(std::uint64_t value);
		/// <summary>
		/// Formats a <see cref="sbyte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatInt8(std::int8_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="short"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatInt16(std::int16_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="int"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatInt32(std::int32_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="long"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatInt64(std::int64_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="byte"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatUInt8(std::uint8_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="ushort"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatUInt16(std::uint16_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="uint"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatUInt32(std::uint32_t value, NumberFormattingOptions const numberOptions) = 0;
		/// <summary>
		/// Formats a <see cref="ulong"/>
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="numberOptions">Options</param>
		/// <returns></returns>
		virtual std::string FormatUInt64(std::uint64_t value, NumberFormattingOptions const numberOptions) = 0;
	};
	// GENERATOR-BEGIN: FormatMnemonicOptions
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	/// <summary>Format mnemonic options</summary>
	enum class FormatMnemonicOptions : uint
	{
		/// <summary>No option is set</summary>
		None = 0x00000000,
		/// <summary>Don&apos;t add any prefixes</summary>
		NoPrefixes = 0x00000001,
		/// <summary>Don&apos;t add the mnemonic</summary>
		NoMnemonic = 0x00000002
	};
	DEFINE_FLAGS(FormatMnemonicOptions)
		DEFINE_COMP(FormatMnemonicOptions)
		DEFINE_ARITH(FormatMnemonicOptions)

		// GENERATOR-END: FormatMnemonicOptions
}