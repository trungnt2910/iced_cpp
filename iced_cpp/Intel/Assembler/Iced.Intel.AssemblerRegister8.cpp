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

#include "Iced.Intel.AssemblerRegister8.h"
#include "../Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegister8::AssemblerRegister8(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsGPR8(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a GPR8 register", "value"));
		}
		Value = value;
	}

	AssemblerRegister8::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegister8::Equals(AssemblerRegister8 other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegister8::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegister8::Equals(std::any obj)
	{
		AssemblerRegister8* other = std::any_cast<AssemblerRegister8>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegister8::operator == (AssemblerRegister8 right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegister8::operator != (AssemblerRegister8 right)
	{
		return !this->Equals(right);
	}
}
