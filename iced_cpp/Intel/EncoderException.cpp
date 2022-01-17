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

#include "EncoderException.h"

namespace Iced::Intel
{

	Iced::Intel::Instruction EncoderException::GetInstruction() const
	{
		return Instruction;
	}

	EncoderException::EncoderException(const std::string& message, Iced::Intel::Instruction const instruction) : std::runtime_error(message)
	{
		Instruction = instruction;
	}
}
