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

#include "Iced.Intel.AssemblerRegisterTMM.h"
#include "../RegisterExtensions.h"

namespace Iced::Intel
{

	AssemblerRegisterTMM::AssemblerRegisterTMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsTMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a TMM register", nameof(value)));
		}
		Value = value;
	}

	AssemblerRegisterTMM::operator Register() const
	{
		return this->Value;
	}

	bool AssemblerRegisterTMM::Equals(AssemblerRegisterTMM other)
	{
		return Value == other.Value;
	}

	std::int32_t AssemblerRegisterTMM::GetHashCode()
	{
		return static_cast<std::int32_t>(Value);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerRegisterTMM::Equals(std::any obj)
	{
		AssemblerRegisterTMM* other = std::any_cast<AssemblerRegisterTMM>(&obj);
		return other != nullptr && Equals(*other);
	}

	bool AssemblerRegisterTMM::operator == (AssemblerRegisterTMM right)
	{
		return this->Equals(right);
	}

	bool AssemblerRegisterTMM::operator != (AssemblerRegisterTMM right)
	{
		return !this->Equals(right);
	}
}
