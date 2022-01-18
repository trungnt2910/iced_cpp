#pragma once

#include <csharp/classes.h>

#include <string>

#include "AssemblerRegister64.defs.h"

#include "AssemblerMemoryOperand.h"
#include "AssemblerOperandFlags.h"
#include "AssemblerRegisterXMM.h"
#include "AssemblerRegisterYMM.h"
#include "AssemblerRegisterZMM.h"
#include "../Register.g.h"
#include "../RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	constexpr AssemblerRegister64::AssemblerRegister64(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR64(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR64 register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	constexpr AssemblerRegister64::AssemblerRegister64(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k1() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k2() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k3() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k4() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k5() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k6() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::k7() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::z() const
	{
		return AssemblerRegister64(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::sae() const
	{
		return AssemblerRegister64(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::rn_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::rd_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::ru_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	constexpr AssemblerRegister64 AssemblerRegister64::rz_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	constexpr AssemblerRegister64::operator Register() const
	{
		return this->Value;
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegister64 right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterXMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterYMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterZMM right) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator + (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator - (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegister64::operator *(std::int32_t scale) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	inline std::int32_t AssemblerRegister64::GetHashCode() const
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	constexpr bool AssemblerRegister64::operator == (AssemblerRegister64 right) const
	{
		return Value == right.Value;
	}

	constexpr bool AssemblerRegister64::operator != (AssemblerRegister64 right) const
	{
		return Value != right.Value;
	}

	constexpr bool AssemblerRegister64::operator == (Register right) const
	{
		return Value == right;
	}

	inline std::string AssemblerRegister64::ToString() const
	{
		return to_string(Value);
	}

	constexpr AssemblerMemoryOperand operator + (AssemblerRegister64 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}
}
