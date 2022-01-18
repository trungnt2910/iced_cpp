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

#include "Iced.Intel.AssemblerRegister64.h"
#include "../Iced.Intel.RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegister64::AssemblerRegister64(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR64(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR64 register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegister64::AssemblerRegister64(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegister64 AssemblerRegister64::k1() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegister64 AssemblerRegister64::k2() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegister64 AssemblerRegister64::k3() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegister64 AssemblerRegister64::k4() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegister64 AssemblerRegister64::k5() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegister64 AssemblerRegister64::k6() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegister64 AssemblerRegister64::k7() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegister64 AssemblerRegister64::z() const
	{
		return AssemblerRegister64(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegister64 AssemblerRegister64::sae() const
	{
		return AssemblerRegister64(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegister64 AssemblerRegister64::rn_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegister64 AssemblerRegister64::rd_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegister64 AssemblerRegister64::ru_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegister64 AssemblerRegister64::rz_sae() const
	{
		return AssemblerRegister64(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegister64::operator Register() const
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegister64 right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterXMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterYMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator + (AssemblerRegisterZMM right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister64::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegister64::Equals(AssemblerRegister64 other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegister64::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegister64::Equals(std::any obj)
	{
		AssemblerRegister64* other = std::any_cast<AssemblerRegister64>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegister64::operator == (AssemblerRegister64 right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegister64::operator != (AssemblerRegister64 right)
	{
		return !this->Equals(right);
	}
}
