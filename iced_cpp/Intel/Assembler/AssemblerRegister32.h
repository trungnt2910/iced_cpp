#pragma once

#include "AssemblerRegister32.defs.h"

#include <csharp/classes.h>

#include "../RegisterExtensions.h"
#include "AssemblerOperandFlags.h"
#include "AssemblerMemoryOperand.h"

#include "AssemblerRegisterXMM.h"
#include "AssemblerRegisterYMM.h"
#include "AssemblerRegisterZMM.h"

namespace Iced::Intel
{

	constexpr AssemblerRegister32::AssemblerRegister32(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR32(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR32 register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	constexpr AssemblerRegister32::AssemblerRegister32(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k1() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k2() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k3() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k4() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k5() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k6() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::k7() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::z() const
	{
		return AssemblerRegister32(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::sae() const
	{
		return AssemblerRegister32(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::rn_sae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::rd_sae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::ru_sae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	constexpr AssemblerRegister32 AssemblerRegister32::rz_sae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	constexpr AssemblerRegister32::operator Register() const
	{
		return this->Value;
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegister32 right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterXMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterYMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterZMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator + (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator - (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister32::operator *(std::int32_t scale) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	constexpr std::int32_t AssemblerRegister32::GetHashCode() const
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	constexpr bool AssemblerRegister32::operator == (AssemblerRegister32 right) const
	{
		return Value == right.Value;
	}

	constexpr bool AssemblerRegister32::operator != (AssemblerRegister32 right) const
	{
		return Value != right.Value;
	}

	constexpr bool AssemblerRegister32::operator == (Register right) const
	{
		return Value == right;
	}

	inline std::string AssemblerRegister32::ToString() const
	{
		return Iced::Intel::ToString(Value);
	}

	constexpr AssemblerMemoryOperand operator + (AssemblerRegister32 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}
}
