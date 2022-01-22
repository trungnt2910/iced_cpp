// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Iced.Intel.AssemblerRegisterTR.h"
#include "../RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterTR::AssemblerRegisterTR(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsTR(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a TR register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterTR::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterTR::Equals(AssemblerRegisterTR other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterTR::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterTR::Equals(std::any obj)
	{
		AssemblerRegisterTR* other = std::any_cast<AssemblerRegisterTR>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterTR::operator == (AssemblerRegisterTR right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterTR::operator != (AssemblerRegisterTR right)
	{
		return !this->Equals(right);
	}
}
