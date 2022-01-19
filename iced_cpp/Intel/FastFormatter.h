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

#include "FastFormatterOptions.h"
#include "ISymbolResolver.h"
#include "FormatterInternal/FormatterString.h"
#include "FastFormatterInternal/FastFmtFlags.g.h"
#include "FastStringOutput.h"
#include "Iced.Intel.Instruction.h"
#include "Register.g.h"
#include <string>
#include <vector>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FastFormatterInternal;
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Fast formatter with less formatting options and with a masm-like syntax.
	/// Use it if formatting speed is more important than being able to re-assemble formatted instructions.
	/// <br/>
	/// <br/>
	/// This formatter is ~2.3x faster than the other formatters (the time includes decoding + formatting).
	/// </summary>
	class FastFormatter final
	{
		/* readonly */
	private:
		FastFormatterOptions* options;
		/* readonly */
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: ISymbolResolver? symbolResolver;
		ISymbolResolver* symbolResolver;
		/* readonly */
		std::vector<FormatterString> allRegisters;
		/* readonly */
		std::vector<std::string> codeMnemonics;
		/* readonly */
		std::vector<FastFmtFlags> codeFlags;
		/* readonly */
		std::vector<std::string> allMemorySizes;
		/* readonly */
		std::vector<std::string> rcStrings;
		/* readonly */
		std::vector<std::string> rcSaeStrings;
		/* readonly */
		std::vector<std::string> scaleNumbers;
		/* readonly */
		std::vector<std::string> mvexRegMemConsts32;
		/* readonly */
		std::vector<std::string> mvexRegMemConsts64;
		static constexpr bool ShowUselessPrefixes = true;
		static std::vector<std::string> s_rcStrings;
		static std::vector<std::string> s_rcSaeStrings;
		static std::vector<std::string> s_scaleNumbers;
		static std::vector<std::string> s_mvexRegMemConsts32;
		static std::vector<std::string> s_mvexRegMemConsts64;
		/// <summary>
		/// Gets the formatter options
		/// </summary>
	public:
		FastFormatterOptions* GetOptions() const;
		/// <summary>
		/// Constructor
		/// </summary>
		FastFormatter();
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="symbolResolver">Symbol resolver or null</param>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public FastFormatter(ISymbolResolver? symbolResolver)
		FastFormatter(ISymbolResolver* symbolResolver);
		/// <summary>
		/// Formats the whole instruction: prefixes, mnemonic, operands
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="output">Output</param>
		void Format(const Instruction& instruction, FastStringOutput* output);
		// Only one caller
	private:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static bool ShowSegmentPrefix(in Instruction instruction, int opCount)
		static bool ShowSegmentPrefix(const Instruction& instruction, std::int32_t opCount);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] void FormatRegister(FastStringOutput output, Register register)
		void FormatRegister(FastStringOutput* output, Register register_);
		void FormatNumber(FastStringOutput* output, std::uint64_t value);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] void WriteSymbol(FastStringOutput output, ulong address, in SymbolResult symbol)
		void WriteSymbol(FastStringOutput* output, std::uint64_t address, SymbolResult const symbol);
		void WriteSymbol(FastStringOutput* output, std::uint64_t address, SymbolResult const symbol, bool writeMinusIfSigned);
		void FormatMemory(FastStringOutput* output, const Instruction& instruction, std::int32_t operand, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize);
	};
}
