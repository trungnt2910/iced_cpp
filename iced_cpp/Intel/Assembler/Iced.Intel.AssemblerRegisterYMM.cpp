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
#include "../RegisterExtensions.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegisterYMM::AssemblerRegisterYMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsYMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a YMM register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegisterYMM::AssemblerRegisterYMM(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k1() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k2() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k3() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k4() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k5() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k6() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::k7() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::z() const
	{
		return AssemblerRegisterYMM(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::sae() const
	{
		return AssemblerRegisterYMM(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::rn_sae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::rd_sae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::ru_sae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	AssemblerRegisterYMM AssemblerRegisterYMM::rz_sae() const
	{
		return AssemblerRegisterYMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	AssemblerRegisterYMM::operator Register() const
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
		AssemblerRegisterYMM* other = std::any_cast<AssemblerRegisterYMM>(&obj);
		return other != nullptr && Equals(*other);
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
