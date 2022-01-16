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

#include "Iced.Intel.AssemblerRegisterYMM.h"
#include "../Iced.Intel.RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegisterYMM::AssemblerRegisterYMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsYMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a YMM register", value), "value");
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegisterYMM::AssemblerRegisterYMM(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK1() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK2() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK3() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK4() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK5() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK6() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetK7() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetZ() const
	{
		return AssemblerRegisterYMM(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetSae() const
	{
		return AssemblerRegisterYMM(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetRnSae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetRdSae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetRuSae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::GetRzSae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegisterYMM::operator Register()
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegisterYMM::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterYMM::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterYMM::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegisterYMM::Equals(AssemblerRegisterYMM other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegisterYMM::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterYMM::Equals(std::any obj)
	{
		AssemblerRegisterYMM other = dynamic_cast<AssemblerRegisterYMM>(obj);
		return other != nullptr && Equals(other);
	}

	bool AssemblerRegisterYMM::operator == (AssemblerRegisterYMM right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterYMM::operator != (AssemblerRegisterYMM right)
	{
		return !this->Equals(right);
	}
}
