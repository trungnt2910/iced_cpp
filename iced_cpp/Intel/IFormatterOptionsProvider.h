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

#include "Iced.Intel.Instruction.h"
#include "MemorySizeOptions.g.h"
#include "FormatterOptions.h"
#include <string>
#include <limits>
#include <csharp/exceptionhelper.h>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel { class FormatterOperandOptions; }
namespace Iced::Intel { class NumberFormattingOptions; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Can override options used by a <see cref="Formatter"/>
	/// </summary>
	class IFormatterOptionsProvider
	{
		/// <summary>
		/// Called by the formatter. The method can override any options before the formatter uses them.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="options">Options. Only those options that will be used by the formatter are initialized.</param>
		/// <param name="numberOptions">Number formatting options</param>
	public:
		virtual void GetOperandOptions(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOperandOptions& options, NumberFormattingOptions& numberOptions) = 0;
	};
	/// <summary>
	/// Operand options
	/// </summary>
	class FormatterOperandOptions
	{
	private:
		std::uint32_t flags = 0;
	public:
		enum class Flags : int
		{
			None = 0,
			NoBranchSize = 0x00000001,
			RipRelativeAddresses = 0x00000002,
			MemorySizeShift = 30,
			MemorySizeMask = 3U << static_cast<std::int32_t>(MemorySizeShift)
		};
		DEFINE_FLAGS(Flags)
			DEFINE_COMP(Flags)
			DEFINE_ARITH(Flags)

			/// <summary>
			/// Show branch size (eg. <c>SHORT</c>, <c>NEAR PTR</c>)
			/// </summary>
	public:
		/* readonly */
		bool GetBranchSize() const;
		void SetBranchSize(bool value);
		/// <summary>
		/// If <see langword="true"/>, show <c>RIP</c> relative addresses as <c>[rip+12345678h]</c>, else show the linear address eg. <c>[1029384756AFBECDh]</c>
		/// </summary>
		 /* readonly */
		bool GetRipRelativeAddresses() const;
		void SetRipRelativeAddresses(bool value);
		/// <summary>
		/// Memory size options
		/// </summary>
		 /* readonly */
		Iced::Intel::MemorySizeOptions GetMemorySizeOptions() const;
		void SetMemorySizeOptions(Iced::Intel::MemorySizeOptions value);
		FormatterOperandOptions(Flags flags);
		FormatterOperandOptions(Iced::Intel::MemorySizeOptions options);

		FormatterOperandOptions() = default;
	};
	/// <summary>
	/// Gets initialized with the default options and can be overridden by a <see cref="IFormatterOptionsProvider"/>
	/// </summary>
	class NumberFormattingOptions
	{
		/// <summary>
		/// Digit separator or <see langword="null"/>/empty string to not use a digit separator
		/// </summary>
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public string? DigitSeparator;
		std::string DigitSeparator;
		/// <summary>
		/// Number prefix or <see langword="null"/>/empty string
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? Prefix;
		std::string Prefix;
		/// <summary>
		/// Number suffix or <see langword="null"/>/empty string
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? Suffix;
		std::string Suffix;
		/// <summary>
		/// Size of a digit group or 0 to not use a digit separator
		/// </summary>
		std::uint8_t DigitGroupSize = 0;
		/// <summary>
		/// Number base
		/// </summary>
		 /* readonly */
		Iced::Intel::NumberBase GetNumberBase() const;
		void SetNumberBase(Iced::Intel::NumberBase value);
	private:
		std::uint8_t numberBaseByteValue = 0;
		/// <summary>
		/// Use uppercase hex digits
		/// </summary>
	public:
		bool UppercaseHex = false;
		/// <summary>
		/// Small hex numbers (-9 .. 9) are shown in decimal
		/// </summary>
		bool SmallHexNumbersInDecimal = false;
		/// <summary>
		/// Add a leading zero to hex numbers if there's no prefix and the number starts with hex digits <c>A-F</c>
		/// </summary>
		bool AddLeadingZeroToHexNumbers = false;
		/// <summary>
		/// If <see langword="true"/>, add leading zeros to numbers, eg. '1h' vs '00000001h'
		/// </summary>
		bool LeadingZeros = false;
		/// <summary>
		/// If <see langword="true"/>, the number is signed, and if <see langword="false"/> it's an unsigned number
		/// </summary>
		bool SignedNumber = false;
		/// <summary>
		/// Add leading zeros to displacements
		/// </summary>
		bool DisplacementLeadingZeros = false;
		/// <summary>
		/// Creates options used when formatting immediate values
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static NumberFormattingOptions CreateImmediate(FormatterOptions options)
		static NumberFormattingOptions CreateImmediate(FormatterOptions* options);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] internal static NumberFormattingOptions CreateImmediateInternal(FormatterOptions options)
		static NumberFormattingOptions CreateImmediateInternal(FormatterOptions* options);
		/// <summary>
		/// Creates options used when formatting displacements
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static NumberFormattingOptions CreateDisplacement(FormatterOptions options)
		static NumberFormattingOptions CreateDisplacement(FormatterOptions* options);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] internal static NumberFormattingOptions CreateDisplacementInternal(FormatterOptions options)
		static NumberFormattingOptions CreateDisplacementInternal(FormatterOptions* options);
		/// <summary>
		/// Creates options used when formatting branch operands
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static NumberFormattingOptions CreateBranch(FormatterOptions options)
		static NumberFormattingOptions CreateBranch(FormatterOptions* options);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] internal static NumberFormattingOptions CreateBranchInternal(FormatterOptions options)
		static NumberFormattingOptions CreateBranchInternal(FormatterOptions* options);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="options">Formatter options to use</param>
		/// <param name="leadingZeros">Add leading zeros to numbers, eg. <c>1h</c> vs <c>00000001h</c></param>
		/// <param name="signedNumber">Signed numbers if <see langword="true"/>, and unsigned numbers if <see langword="false"/></param>
		/// <param name="displacementLeadingZeros">Add leading zeros to displacements</param>
		NumberFormattingOptions(FormatterOptions* options, bool leadingZeros, bool signedNumber, bool displacementLeadingZeros);

		NumberFormattingOptions() = default;
	};
}
