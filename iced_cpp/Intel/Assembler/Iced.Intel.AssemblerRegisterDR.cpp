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

#include "Iced.Intel.AssemblerRegisterDR.h"
#include "../Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterDR::AssemblerRegisterDR(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsDR(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a DR register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterDR::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterDR::Equals(AssemblerRegisterDR other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterDR::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterDR::Equals(std::any obj)
	{
		AssemblerRegisterDR* other = std::any_cast<AssemblerRegisterDR>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterDR::operator == (AssemblerRegisterDR right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterDR::operator != (AssemblerRegisterDR right)
	{
		return !this->Equals(right);
	}
}
