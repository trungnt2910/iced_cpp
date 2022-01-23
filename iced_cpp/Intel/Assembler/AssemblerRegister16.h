#pragma once

#include <csharp/classes.h>
#include <csharp/exceptionhelper.h>

#include "AssemblerRegister16.defs.h"
#include "../RegisterExtensions.h"

#include "AssemblerMemoryOperand.h"

namespace Iced::Intel
{
	constexpr AssemblerRegister16::AssemblerRegister16(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR16(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR16 register", nameof(value)));
		}
		Value = value;
	}

	constexpr AssemblerRegister16::operator Register() const
	{
		return this->Value;
	}

	constexpr AssemblerMemoryOperand AssemblerRegister16::operator + (AssemblerRegister16 right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister16::operator + (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister16::operator - (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister16::operator *(std::int32_t scale) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	constexpr std::int32_t AssemblerRegister16::GetHashCode() const
	{
		return static_cast<std::int32_t>(Value);
	}

	constexpr bool AssemblerRegister16::operator == (AssemblerRegister16 right) const
	{
		return Value == right.Value;
	}

	constexpr bool AssemblerRegister16::operator != (AssemblerRegister16 right) const
	{
		return Value != right.Value;
	}

	constexpr bool AssemblerRegister16::operator == (Register right) const
	{
		return Value == right;
	}

	inline std::string AssemblerRegister16::ToString() const
	{
		return Iced::Intel::ToString(Value);
	}

	constexpr AssemblerMemoryOperand operator + (AssemblerRegister16 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}
}
