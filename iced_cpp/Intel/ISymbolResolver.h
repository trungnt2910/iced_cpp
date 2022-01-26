// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once
#if defined(GAS) || defined(INTEL) || defined(MASM) || defined(NASM) || defined(FAST_FMT)

#include "Iced.Intel.Instruction.h"
#include "FormatterTextKind.g.h"
#include "MemorySize.g.h"
#include <string>
#include <vector>

namespace Iced::Intel { class SymbolResult; }
namespace Iced::Intel { class TextInfo; }
namespace Iced::Intel { class TextPart; }

namespace Iced::Intel
{
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
		constexpr TextPart(const std::string& text, FormatterTextKind color)
			: Text(text), Color(color)
		{
		}

		constexpr TextPart() = default;
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
		constexpr bool IsDefault() const
		{
			return TextArray == nullptr && Text.Text == std::string();
		}
		/// <summary>
		/// The text and color unless <see cref="TextArray"/> is non-null
		/// </summary>
		TextPart Text = TextPart();
		/// <summary>
		/// Text and color or null if <see cref="Text"/> should be used
		/// </summary>
		std::vector<TextPart>* TextArray = nullptr;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">Text</param>
		/// <param name="color">Color</param>
		constexpr TextInfo(const std::string& text, FormatterTextKind color)
			: Text(TextPart(text, color)), TextArray(nullptr)
		{
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">Text</param>
		constexpr TextInfo(TextPart text)
			: Text(text), TextArray(nullptr)
		{
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="text">All text parts</param>
		constexpr TextInfo(std::vector<TextPart>* text)
			: TextArray(text)
		{
		}

		constexpr TextInfo() = default;
	};

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
		constexpr virtual bool TryGetSymbol(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, std::uint64_t address, std::int32_t addressSize, SymbolResult& symbol) const = 0;
	};
	// GENERATOR-BEGIN: SymbolFlags
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class SymbolFlags : std::uint32_t {
		/// <summary>No bit is set</summary>
		None  = 0x00000000,
		/// <summary>It&apos;s a symbol relative to a register, eg. a struct offset <c>[ebx+some_struct.field1]</c>. If this is cleared, it&apos;s the address of a symbol.</summary>
		Relative  = 0x00000001,
		/// <summary>It&apos;s a signed symbol and it should be displayed as <c>-symbol</c> or <c>reg-symbol</c> instead of <c>symbol</c> or <c>reg+symbol</c></summary>
		Signed  = 0x00000002,
		/// <summary>Set if <see cref="SymbolResult.SymbolSize"/> is valid</summary>
		HasSymbolSize  = 0x00000004,
	};
	constexpr SymbolFlags& operator^=(SymbolFlags& a, const SymbolFlags& b) { return a = (SymbolFlags)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr SymbolFlags operator^(const SymbolFlags& a, const SymbolFlags& b) { return (SymbolFlags)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr SymbolFlags& operator|=(SymbolFlags& a, const SymbolFlags& b) { return a = (SymbolFlags)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr SymbolFlags operator|(const SymbolFlags& a, const SymbolFlags& b) { return (SymbolFlags)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr SymbolFlags& operator&=(SymbolFlags& a, const SymbolFlags& b) { return a = (SymbolFlags)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr SymbolFlags operator&(const SymbolFlags& a, const SymbolFlags& b) { return (SymbolFlags)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr SymbolFlags operator~(const SymbolFlags& a) { return (SymbolFlags)(~((std::uint32_t)a)); }
	constexpr std::uint32_t operator+(const SymbolFlags& a, const SymbolFlags& b) { return ((std::uint32_t)a + (std::uint32_t)b); }
	constexpr std::uint32_t operator+(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a + b); }
	constexpr std::uint32_t operator+(const std::uint32_t& a, const SymbolFlags& b) { return (a + (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const SymbolFlags& a, const SymbolFlags& b) { return ((std::uint32_t)a - (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a - b); }
	constexpr std::uint32_t operator-(const std::uint32_t& a, const SymbolFlags& b) { return (a - (std::uint32_t)b); }
	constexpr SymbolFlags operator++(SymbolFlags& a, int) { auto temp = a; a = SymbolFlags(a + 1); return temp; }
	constexpr SymbolFlags& operator++(SymbolFlags& a) { return a = SymbolFlags(a + 1); }
	constexpr SymbolFlags operator--(SymbolFlags& a, int) { auto temp = a; a = SymbolFlags(a - 1); return temp; }
	constexpr SymbolFlags& operator--(SymbolFlags& a) { return a = SymbolFlags(a - 1); }
	constexpr bool operator==(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a == b); }
	constexpr bool operator==(const std::uint32_t& a, const SymbolFlags& b) { return (a == (std::uint32_t)b); }
	constexpr bool operator>=(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a >= b); }
	constexpr bool operator>=(const std::uint32_t& a, const SymbolFlags& b) { return (a >= (std::uint32_t)b); }
	constexpr bool operator<=(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a <= b); }
	constexpr bool operator<=(const std::uint32_t& a, const SymbolFlags& b) { return (a <= (std::uint32_t)b); }
	constexpr bool operator>(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a > b); }
	constexpr bool operator>(const std::uint32_t& a, const SymbolFlags& b) { return (a > (std::uint32_t)b); }
	constexpr bool operator<(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a < b); }
	constexpr bool operator<(const std::uint32_t& a, const SymbolFlags& b) { return (a < (std::uint32_t)b); }
	constexpr bool operator!=(const SymbolFlags& a, const std::uint32_t& b) { return ((std::uint32_t)a != b); }
	constexpr bool operator!=(const std::uint32_t& a, const SymbolFlags& b) { return (a != (std::uint32_t)b); }
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
		constexpr bool GetHasSymbolSize() const;
		/// <summary>
		/// Symbol size if <see cref="HasSymbolSize"/> is <see langword="true"/>
		/// </summary>
		MemorySize SymbolSize = static_cast<MemorySize>(0);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		constexpr SymbolResult(std::uint64_t address, const std::string& text);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="size">Symbol size</param>
		constexpr SymbolResult(std::uint64_t address, const std::string& text, MemorySize size);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="color">Color</param>
		constexpr SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="color">Color</param>
		/// <param name="flags">Symbol flags</param>
		constexpr SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color, SymbolFlags flags);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		constexpr SymbolResult(std::uint64_t address, TextInfo text);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="size">Symbol size</param>
		constexpr SymbolResult(std::uint64_t address, TextInfo text, MemorySize size);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="flags">Symbol flags</param>
		constexpr SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="address">The address of the symbol</param>
		/// <param name="text">Symbol</param>
		/// <param name="flags">Symbol flags</param>
		/// <param name="size">Symbol size</param>
		constexpr SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags, MemorySize size);

		constexpr SymbolResult() = default;
	};

	constexpr bool SymbolResult::GetHasSymbolSize() const
	{
		return (Flags & SymbolFlags::HasSymbolSize) != 0;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, const std::string& text)
	{
		Address = address;
		Text = TextInfo(text, DefaultKind);
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, MemorySize size)
	{
		Address = address;
		Text = TextInfo(text, DefaultKind);
		Flags = SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color)
	{
		Address = address;
		Text = TextInfo(text, color);
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color, SymbolFlags flags)
	{
		Address = address;
		Text = TextInfo(text, color);
		Flags = flags & ~SymbolFlags::HasSymbolSize;
		SymbolSize = MemorySize::Unknown;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, TextInfo text)
	{
		Address = address;
		Text = text;
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, MemorySize size)
	{
		Address = address;
		Text = text;
		Flags = SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags)
	{
		Address = address;
		Text = text;
		Flags = flags & ~SymbolFlags::HasSymbolSize;
		SymbolSize = MemorySize::Unknown;
	}

	constexpr SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags, MemorySize size)
	{
		Address = address;
		Text = text;
		Flags = flags | SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}
}
#endif
