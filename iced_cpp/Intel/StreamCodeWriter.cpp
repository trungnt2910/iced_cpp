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

#include "StreamCodeWriter.h"

namespace Iced::Intel
{

	StreamCodeWriter::StreamCodeWriter(class Stream* stream)
	{
		Stream = stream;
	}

	void StreamCodeWriter::WriteByte(std::uint8_t value)
	{
		Stream->WriteByte(value);
	}
}
