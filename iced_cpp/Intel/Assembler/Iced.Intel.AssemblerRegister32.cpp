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

#include "Iced.Intel.AssemblerRegister32.h"
#include "../Iced.Intel.RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegister32::AssemblerRegister32(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR32(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR32 register", value), "value");
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegister32::AssemblerRegister32(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegister32 AssemblerRegister32::GetK1() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegister32 AssemblerRegister32::GetK2() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegister32 AssemblerRegister32::GetK3() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegister32 AssemblerRegister32::GetK4() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegister32 AssemblerRegister32::GetK5() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegister32 AssemblerRegister32::GetK6() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegister32 AssemblerRegister32::GetK7() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegister32 AssemblerRegister32::GetZ() const
	{
		return AssemblerRegister32(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegister32 AssemblerRegister32::GetSae() const
	{
		return AssemblerRegister32(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegister32 AssemblerRegister32::GetRnSae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegister32 AssemblerRegister32::GetRdSae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegister32 AssemblerRegister32::GetRuSae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegister32 AssemblerRegister32::GetRzSae() const
	{
		return AssemblerRegister32(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegister32::operator Register()
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegister32 right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterXMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterYMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator + (AssemblerRegisterZMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister32::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegister32::Equals(AssemblerRegister32 other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegister32::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegister32::Equals(std::any obj)
	{
		AssemblerRegister32 other = dynamic_cast<AssemblerRegister32>(obj);
		return other != nullptr && Equals(other);
	}

	bool AssemblerRegister32::operator == (AssemblerRegister32 right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegister32::operator != (AssemblerRegister32 right)
	{
		return !this->Equals(right);
	}
}
