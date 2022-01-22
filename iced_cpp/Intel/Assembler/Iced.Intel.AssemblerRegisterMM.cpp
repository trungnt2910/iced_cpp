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

#include "Iced.Intel.AssemblerRegisterMM.h"
#include "../RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterMM::AssemblerRegisterMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a MM register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterMM::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterMM::Equals(AssemblerRegisterMM other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterMM::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterMM::Equals(std::any obj)
	{
		AssemblerRegisterMM* other = std::any_cast<AssemblerRegisterMM>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterMM::operator == (AssemblerRegisterMM right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterMM::operator != (AssemblerRegisterMM right)
	{
		return !this->Equals(right);
	}
}
