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

#include "Iced.Intel.AssemblerRegister16.h"
#include "../RegisterExtensions.h"
#include "AssemblerOperandFlags.h"
#include "MemoryOperandSize.g.h"

namespace Iced::Intel
{

	AssemblerRegister16::AssemblerRegister16(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR16(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR16 register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegister16::operator Register() const
	{
		return this->Value;
	}

	AssemblerMemoryOperand AssemblerRegister16::operator + (AssemblerRegister16 right)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, right, 1, 0, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister16::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister16::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	AssemblerMemoryOperand AssemblerRegister16::operator *(std::int32_t scale)
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	bool AssemblerRegister16::Equals(AssemblerRegister16 other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegister16::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegister16::Equals(std::any obj)
	{
		AssemblerRegister16* other = std::any_cast<AssemblerRegister16>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegister16::operator == (AssemblerRegister16 right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegister16::operator != (AssemblerRegister16 right)
	{
		return !this->Equals(right);
	}
}
