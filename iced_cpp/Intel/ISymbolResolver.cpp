// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ISymbolResolver.h"

namespace Iced::Intel
{

	bool SymbolResult::GetHasSymbolSize() const
	{
		return (Flags & SymbolFlags::HasSymbolSize) != 0;
	}

	SymbolResult::SymbolResult(std::uint64_t address, const std::string& text)
	{
		Address = address;
		Text = TextInfo(text, DefaultKind);
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, MemorySize size)
	{
		Address = address;
		Text = TextInfo(text, DefaultKind);
		Flags = SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}

	SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color)
	{
		Address = address;
		Text = TextInfo(text, color);
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	SymbolResult::SymbolResult(std::uint64_t address, const std::string& text, FormatterTextKind color, SymbolFlags flags)
	{
		Address = address;
		Text = TextInfo(text, color);
		Flags = flags & ~SymbolFlags::HasSymbolSize;
		SymbolSize = MemorySize::Unknown;
	}

	SymbolResult::SymbolResult(std::uint64_t address, TextInfo text)
	{
		Address = address;
		Text = text;
		Flags = SymbolFlags::None;
		SymbolSize = MemorySize::Unknown;
	}

	SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, MemorySize size)
	{
		Address = address;
		Text = text;
		Flags = SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}

	SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags)
	{
		Address = address;
		Text = text;
		Flags = flags & ~SymbolFlags::HasSymbolSize;
		SymbolSize = MemorySize::Unknown;
	}

	SymbolResult::SymbolResult(std::uint64_t address, TextInfo text, SymbolFlags flags, MemorySize size)
	{
		Address = address;
		Text = text;
		Flags = flags | SymbolFlags::HasSymbolSize;
		SymbolSize = size;
	}

	bool TextInfo::IsDefault() const
	{
		return TextArray == nullptr && Text.Text == std::string();
	}

	TextInfo::TextInfo(const std::string& text, FormatterTextKind color)
	{
		Text = TextPart(text, color);
		TextArray = nullptr;
	}

	TextInfo::TextInfo(TextPart text)
	{
		Text = text;
		TextArray = nullptr;
	}

	TextInfo::TextInfo(std::vector<TextPart>* text)
	{
		Text = Iced::Intel::TextPart();
		TextArray = text;
	}

	TextPart::TextPart(const std::string& text, FormatterTextKind color)
	{
		Text = text;
		Color = color;
	}
}
