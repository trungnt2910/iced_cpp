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

#include "FormatterOutput.h"

namespace Iced::Intel
{

	void FormatterOutput::WritePrefix(const Instruction& instruction, const std::string& text, PrefixKind prefix)
	{
		Write(text, FormatterTextKind::Prefix);
	}

	void FormatterOutput::WriteMnemonic(const Instruction& instruction, const std::string& text)
	{
		Write(text, FormatterTextKind::Mnemonic);
	}

	void FormatterOutput::WriteNumber(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, std::uint64_t value, NumberKind numberKind, FormatterTextKind kind)
	{
		Write(text, kind);
	}

	void FormatterOutput::WriteDecorator(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, DecoratorKind decorator)
	{
		Write(text, FormatterTextKind::Decorator);
	}

	void FormatterOutput::WriteRegister(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, const std::string& text, Register register_)
	{
		Write(text, FormatterTextKind::Register);
	}

	void FormatterOutput::WriteSymbol(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, std::uint64_t address, SymbolResult const symbol)
	{
		const auto& text = symbol.Text;
		auto array = text.TextArray;
		if (array != nullptr)
		{
			for (const auto& part : *array)
			{
				Write(part.Text, part.Color);
			}
		}
		else
		{
			const std::string& s = text.Text.Text;
			if (s != "")
			{
				Write(s, text.Text.Color);
			}
		}
	}

	void FormatterOutput::Write(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOptions* options, NumberFormatter const numberFormatter, NumberFormattingOptions const numberOptions, std::uint64_t address, SymbolResult const symbol, bool showSymbolAddress)
	{
		Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, address, symbol, showSymbolAddress, true, false);
	}

	void FormatterOutput::Write(const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterOptions* options, NumberFormatter const numberFormatter, NumberFormattingOptions const numberOptions, std::uint64_t address, SymbolResult const symbol, bool showSymbolAddress, bool writeMinusIfSigned, bool spacesBetweenOp)
	{
		std::int64_t displ = static_cast<std::int64_t>(address - symbol.Address);
		if ((symbol.Flags & SymbolFlags::Signed) != 0)
		{
			if (writeMinusIfSigned)
			{
				Write("-", FormatterTextKind::Operator);
			}
			displ = -displ;
		}
		WriteSymbol(instruction, operand, instructionOperand, address, symbol);
		NumberKind numberKind;
		if (displ != 0)
		{
			if (spacesBetweenOp)
			{
				Write(" ", FormatterTextKind::Text);
			}
			std::uint64_t origDispl = static_cast<std::uint64_t>(displ);
			if (displ < 0)
			{
				Write("-", FormatterTextKind::Operator);
				displ = -displ;
				if (displ <= std::numeric_limits<std::int8_t>::max() + 1)
				{
					numberKind = NumberKind::Int8;
				}
				else if (displ <= std::numeric_limits<std::int16_t>::max() + 1)
				{
					numberKind = NumberKind::Int16;
				}
				else if (displ <= static_cast<std::int64_t>(std::numeric_limits<std::int32_t>::max()) + 1)
				{
					numberKind = NumberKind::Int32;
				}
				else
				{
					numberKind = NumberKind::Int64;
				}
			}
			else
			{
				Write("+", FormatterTextKind::Operator);
				if (displ <= std::numeric_limits<std::int8_t>::max())
				{
					numberKind = NumberKind::Int8;
				}
				else if (displ <= std::numeric_limits<std::int16_t>::max())
				{
					numberKind = NumberKind::Int16;
				}
				else if (displ <= std::numeric_limits<std::int32_t>::max())
				{
					numberKind = NumberKind::Int32;
				}
				else
				{
					numberKind = NumberKind::Int64;
				}
			}
			if (spacesBetweenOp)
			{
				Write(" ", FormatterTextKind::Text);
			}
			auto s = numberFormatter.FormatUInt64(options, numberOptions, static_cast<std::uint64_t>(displ), false);
			WriteNumber(instruction, operand, instructionOperand, s, origDispl, numberKind, FormatterTextKind::Number);
		}
		if (showSymbolAddress)
		{
			Write(" ", FormatterTextKind::Text);
			Write("(", FormatterTextKind::Punctuation);
			std::string s;
			if (address <= std::numeric_limits<std::uint16_t>::max())
			{
				s = numberFormatter.FormatUInt16(options, numberOptions, static_cast<std::uint16_t>(address), true);
				numberKind = NumberKind::UInt16;
			}
			else if (address <= std::numeric_limits<std::uint32_t>::max())
			{
				s = numberFormatter.FormatUInt32(options, numberOptions, static_cast<std::uint32_t>(address), true);
				numberKind = NumberKind::UInt32;
			}
			else
			{
				s = numberFormatter.FormatUInt64(options, numberOptions, address, true);
				numberKind = NumberKind::UInt64;
			}
			WriteNumber(instruction, operand, instructionOperand, s, address, numberKind, FormatterTextKind::Number);
			Write(")", FormatterTextKind::Punctuation);
		}
	}
}
