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

#include "Label.h"

namespace Iced::Intel
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: internal Label(string? name, ulong id)
	Label::Label(const std::string& name, std::uint64_t id)
	{
		Name = (name != "") ? name : "___label";
		Id = id;
		SetInstructionIndex(-1);
	}

	std::int32_t Label::GetInstructionIndex() const
	{
		return InstructionIndex;
	}

	void Label::SetInstructionIndex(std::int32_t value)
	{
		InstructionIndex = value;
	}

	bool Label::IsEmpty() const
	{
		return Id == 0;
	}

	std::string Label::ToString() const
	{
		return std::format("{0:s}@{1:s}", to_string(Name), to_string(Id));
	}

	bool Label::Equals(const Label& other)
	{
		return Name == other.Name && Id == other.Id;
	}

	std::int32_t Label::GetHashCode()
	{
		//	 unchecked
		return (::GetHashCode(Name) * 397) ^ ::GetHashCode(Id);
		//C# TO C++ CONVERTER TODO TASK: End of the original C# 'unchecked' block.
	}

	bool Label::operator == (const Label& right)
	{
		return this->Equals(right);
	}

	bool Label::operator != (const Label& right)
	{
		return !this->Equals(right);
	}
}
