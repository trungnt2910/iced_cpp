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

#include "Iced.Intel.AssemblerRegisterZMM.h"
#include "../Iced.Intel.RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegisterZMM::AssemblerRegisterZMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsZMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a ZMM register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegisterZMM::AssemblerRegisterZMM(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK1() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK2() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK3() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK4() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK5() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK6() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetK7() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetZ() const
	{
		return AssemblerRegisterZMM(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetSae() const
	{
		return AssemblerRegisterZMM(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetRnSae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetRdSae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetRuSae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegisterZMM AssemblerRegisterZMM::GetRzSae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegisterZMM::operator Register() const
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegisterZMM::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterZMM::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterZMM::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegisterZMM::Equals(AssemblerRegisterZMM other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegisterZMM::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterZMM::Equals(std::any obj)
	{
		AssemblerRegisterZMM* other = std::any_cast<AssemblerRegisterZMM>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterZMM::operator == (AssemblerRegisterZMM right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterZMM::operator != (AssemblerRegisterZMM right)
	{
		return !this->Equals(right);
	}
}
