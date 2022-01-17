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

#include "Iced.Intel.AssemblerRegisterXMM.h"
#include "../Iced.Intel.RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegisterXMM::AssemblerRegisterXMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsXMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a XMM register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegisterXMM::AssemblerRegisterXMM(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK1() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK2() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK3() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK4() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK5() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK6() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetK7() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetZ() const
	{
		return AssemblerRegisterXMM(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetSae() const
	{
		return AssemblerRegisterXMM(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetRnSae() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetRdSae() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetRuSae() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegisterXMM AssemblerRegisterXMM::GetRzSae() const
	{
		return AssemblerRegisterXMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegisterXMM::operator Register() const
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegisterXMM::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterXMM::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegisterXMM::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegisterXMM::Equals(AssemblerRegisterXMM other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegisterXMM::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterXMM::Equals(std::any obj)
	{
		AssemblerRegisterXMM* other = std::any_cast<AssemblerRegisterXMM>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterXMM::operator == (AssemblerRegisterXMM right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterXMM::operator != (AssemblerRegisterXMM right)
	{
		return !this->Equals(right);
	}
}
