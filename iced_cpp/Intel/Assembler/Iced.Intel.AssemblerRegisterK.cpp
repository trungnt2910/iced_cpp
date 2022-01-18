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

#include "Iced.Intel.AssemblerRegisterK.h"
#include "../RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterK::AssemblerRegisterK(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsK(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a K register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerRegisterK::AssemblerRegisterK(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	AssemblerRegisterK AssemblerRegisterK::k1() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerRegisterK AssemblerRegisterK::k2() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerRegisterK AssemblerRegisterK::k3() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerRegisterK AssemblerRegisterK::k4() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerRegisterK AssemblerRegisterK::k5() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerRegisterK AssemblerRegisterK::k6() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerRegisterK AssemblerRegisterK::k7() const
	{
		return AssemblerRegisterK(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerRegisterK AssemblerRegisterK::z() const
	{
		return AssemblerRegisterK(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	AssemblerRegisterK::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterK::Equals(AssemblerRegisterK other)
	{
		return Value == other.Value && Flags == other.Flags;
	}

	std::int32_t AssemblerRegisterK::GetHashCode()
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterK::Equals(std::any obj)
	{
		AssemblerRegisterK* other = std::any_cast<AssemblerRegisterK>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterK::operator == (AssemblerRegisterK right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterK::operator != (AssemblerRegisterK right)
	{
		return !this->Equals(right);
	}
}
