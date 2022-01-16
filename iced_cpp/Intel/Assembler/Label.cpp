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

	std::string Label::ToString()
	{
		return std::format("{0:s}@{1:s}", Name, Id);
	}

	bool Label::Equals(Label* other)
	{
		return Name == other.Name && Id == other.Id;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool Label::Equals(std::any obj)
	{
		Label* other = dynamic_cast<Label*>(obj);
		return other != nullptr && Equals(other);
	}

	std::int32_t Label::GetHashCode()
	{
		//	 unchecked
		return (Name.GetHashCode() * 397) ^ Id.GetHashCode();
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
