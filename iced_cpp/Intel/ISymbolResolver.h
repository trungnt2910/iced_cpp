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
#include "FormatterTextKind.g.h"
#include "MemorySize.g.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel { class SymbolResult; }
namespace Iced::Intel { class TextInfo; }
namespace Iced::Intel { class TextPart; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Used by a formatter to resolve symbols
	/// </summary>
	class ISymbolResolver
	{
		/// <summary>
		/// Tries to resolve a symbol. It returns <see langword="true"/> if <paramref name="symbol"/> was updated.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="operand">Operand number, 0-based. This is a formatter operand and isn't necessarily the same as an instruction operand.</param>
		/// <param name="instructionOperand">Instruction operand number, 0-based, or -1 if it's an operand created by the formatter.</param>
		/// <param name="address">Address</param>
		/// <param name="addressSize">Size of <paramref name="address"/> in bytes (eg. 1, 2, 4 or 8)</param>
		/// <param name="symbol">Updated with symbol information if this method returns <see langword="true"/></param>
		/// <returns></returns>
	public:
		virtual bool TryGetSymbol(Instruction const instruction, std::int32_t operand, std::int32_t instructionOperand, std::uint64_t address, std::int32_t addressSize, SymbolResult& symbol) = 0;
	};
	// GENERATOR-BEGIN: SymbolFlags
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	/// <summary>Symbol flags</summary>
	enum class SymbolFlags : uint
	{
		/// <summary>No bit is set</summary>
		None = 0x00000000,
		/// <summary>It&apos;s a symbol relative to a register, eg. a struct offset <c>[ebx+some_struct.field1]</c>. If this is cleared, it&apos;s the address of a symbol.</summary>
		Relative = 0x00000001,
		/// <summary>It&apos;s a signed symbol and it should be displayed as <c>-symbol</c> or <c>reg-symbol</c> instead of <c>symbol</c> or <c>reg+symbol</c></summary>
		Signed = 0x00000002,
		/// <summary>Set if <see cref="SymbolResult.SymbolSize"/> is valid</summary>
		HasSymbolSize = 0x00000004
	};
	DEFINE_FLAGS(SymbolFlags)
		DEFINE_COMP(SymbolFlags)
		DEFINE_ARITH(SymbolFlags)

		// GENERATOR-END: SymbolFlags
		/// <summary>
		/// Created by a <see cref="ISymbolResolver"/>
		/// </summary>
		class SymbolResult
	{
	private:
		static constexpr FormatterTextKind DefaultKind = FormatterTextKind::Label;
		/// <summary>
		/// The address of the symbol
		/// </summary>
	public:
		std::uint64_t Address = 0;
		/// <summary>
		/// Contains the symbol
		/// </summary>
		TextInfo Text;
		/// <summary>
		/// Symbol flags
		/// </summary>
		SymbolFlags Flags = static_cast<SymbolFlags>(0);
		/// <summary>
		/// Checks whether <see cref="SymbolSize"/> is valid
		/// </summary>
		bool GetHasSymbolSize() const;
		/// <summary>
		/// Symbol size if <see cref="HasSymbolSize"/> is <see langword="true"/>
		/// </summary>
		MemorySize SymbolSize = static_cast<MemorySize>(0);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		SymbolResult(std::uint64_t address, const std::string& text);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="size">Symbol size</param>
		SymbolResult(std::uint64_t address, const std::string& text, MemorySize size);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="color">Color</param>
		SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="color">Color</param>
		/// <param name="flags">Symbol flags</param>
		SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color, SymbolFlags flags);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		SymbolResult(std::uint64_t address, TextInfo text);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="size">Symbol size</param>
		SymbolResult(std::uint64_t address, TextInfo text, MemorySize size);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="flags">Symbol flags</param>
		SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="flags">Symbol flags</param>
		/// <param name="size">Symbol size</param>
		SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags, MemorySize size);

		SymbolResult() = default;
	};
	/// <summary>
	/// Contains one or more <see cref="TextPart"/>s (text and color)
	/// </summary>
	class TextInfo
	{
		/// <summary>
		/// <see langword="true"/> if this is the default instance
		/// </summary>
	public:
		bool IsDefault() const;
		/// <summary>
		/// The text and color unless <see cref="TextArray"/> is non-null
		/// </summary>
		TextPart Text;
		/// <summary>
		/// Text and color or null if <see cref="Text"/> should be used
		/// </summary>
		TextPart[] ? TextArray;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">Text</param>
		/// <param name="color">Color</param>
		TextInfo(const std::string& text, FormatterTextKind color);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">Text</param>
		TextInfo(TextPart text);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">All text parts</param>
		TextInfo(std::vector<TextPart>& text);

		TextInfo() = default;
	};
	/// <summary>
	/// Contains text and colors
	/// </summary>
	class TextPart
	{
		/// <summary>
		/// Text
		/// </summary>
	public:
		std::string Text;
		/// <summary>
		/// Color
		/// </summary>
		FormatterTextKind Color = static_cast<FormatterTextKind>(0);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">Text</param>
		/// <param name="color">Color</param>
		TextPart(const std::string& text, FormatterTextKind color);

		TextPart() = default;
	};
}