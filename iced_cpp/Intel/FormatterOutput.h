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

#include "FormatterTextKind.g.h"
#include "Iced.Intel.Instruction.h"
#include "Register.g.h"
#include "ISymbolResolver.h"
#include "FormatterOptions.h"
#include "IFormatterOptionsProvider.h"
#include "NumberFormatter.h"
#include <string>
#include <limits>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Used by a <see cref="Formatter"/> to write all text
	/// </summary>
	class FormatterOutput
	{
		/// <summary>
		/// Writes text and text kind
		/// </summary>
		/// <param name="text">Text</param>
		/// <param name="kind">Text kind</param>
	public:
		virtual void Write(const std::string& text, FormatterTextKind kind) = 0;
		/// <summary>
		/// Writes a prefix
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="text">Prefix text</param>
		/// <param name="prefix">Prefix</param>
		virtual void WritePrefix(Instruction const instruction, const std::string& text, PrefixKind prefix);
		/// <summary>
		/// Writes a mnemonic (see <see cref="Instruction.Mnemonic"/>)
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="text">Mnemonic text</param>
		virtual void WriteMnemonic(Instruction const instruction, const std::string& text);
		/// <summary>
		/// Writes a number
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="text">Number text</param>
		/// <param name="value">Value</param>
		/// <param name="numberKind">Number kind</param>
		/// <param name="kind">Text kind</param>
		virtual void WriteNumber(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, std::uint64_t value, NumberKind numberKind, FormatterTextKind kind);
		/// <summary>
		/// Writes a decorator
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="text">Decorator text</param>
		/// <param name="decorator">Decorator</param>
		virtual void WriteDecorator(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, DecoratorKind decorator);
		/// <summary>
		/// Writes a register
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="text">Register text</param>
		/// <param name="register">Register</param>
		virtual void WriteRegister(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, Register register_);
		/// <summary>
		/// Writes a symbol
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="address">Address</param>
		/// <param name="symbol">Symbol</param>
		virtual void WriteSymbol(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, std::uint64_t address, SymbolResult const symbol);
		void Write(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOptions* options, NumberFormatter const numberFormatter, NumberFormattingOptions const numberOptions, std::uint64_t address, SymbolResult const symbol, bool showSymbolAddress);
		void Write(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOptions* options, NumberFormatter const numberFormatter, NumberFormattingOptions const numberOptions, std::uint64_t address, SymbolResult const symbol, bool showSymbolAddress, bool writeMinusIfSigned, bool spacesBetweenOp);
	};
	// GENERATOR-BEGIN: PrefixKind
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	/// <summary>Prefix</summary>
	enum class PrefixKind
	{
		ES = 0,
		CS = 1,
		SS = 2,
		DS = 3,
		FS = 4,
		GS = 5,
		Lock = 6,
		Rep = 7,
		Repe = 8,
		Repne = 9,
		OperandSize = 10,
		AddressSize = 11,
		HintNotTaken = 12,
		HintTaken = 13,
		Bnd = 14,
		Notrack = 15,
		Xacquire = 16,
		Xrelease = 17
	};

	DEFINE_COMP(PrefixKind)
		DEFINE_ARITH(PrefixKind)

		// GENERATOR-END: PrefixKind
		// GENERATOR-BEGIN: DecoratorKind
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Decorator</summary>
		enum class DecoratorKind
	{
		/// <summary>Broadcast decorator, eg. <c>{1to4}</c></summary>
		Broadcast = 0,
		/// <summary>Rounding control, eg. <c>{rd-sae}</c></summary>
		RoundingControl = 1,
		/// <summary>Suppress all exceptions: <c>{sae}</c></summary>
		SuppressAllExceptions = 2,
		/// <summary>Zeroing masking: <c>{z}</c></summary>
		ZeroingMasking = 3,
		/// <summary>MVEX swizzle or memory up/down conversion: <c>{dacb}</c> or <c>{sint16}</c></summary>
		SwizzleMemConv = 4,
		/// <summary>MVEX eviction hint: <c>{eh}</c></summary>
		EvictionHint = 5
	};

	DEFINE_COMP(DecoratorKind)
		DEFINE_ARITH(DecoratorKind)

		// GENERATOR-END: DecoratorKind
		// GENERATOR-BEGIN: NumberKind
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Number kind</summary>
		enum class NumberKind
	{
		Int8 = 0,
		UInt8 = 1,
		Int16 = 2,
		UInt16 = 3,
		Int32 = 4,
		UInt32 = 5,
		Int64 = 6,
		UInt64 = 7
	};

	DEFINE_COMP(NumberKind)
		DEFINE_ARITH(NumberKind)

		// GENERATOR-END: NumberKind
}