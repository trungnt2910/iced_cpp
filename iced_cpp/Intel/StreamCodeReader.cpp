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

#include "StreamCodeReader.h"

namespace Iced::Intel
{

	StreamCodeReader::StreamCodeReader(Stream* stream)
	{
		Stream = stream;
	}

	std::int32_t StreamCodeReader::ReadByte()
	{
		return Stream->ReadByte();
	}
}
