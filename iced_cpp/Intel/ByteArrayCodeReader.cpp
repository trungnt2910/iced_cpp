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

#include "ByteArrayCodeReader.h"
#include "ThrowHelper.h"

namespace Iced::Intel
{

	std::int32_t ByteArrayCodeReader::GetPosition() const
	{
		return currentPosition - startPosition;
	}

	void ByteArrayCodeReader::SetPosition(std::int32_t value)
	{
		if (static_cast<std::uint32_t>(value) > static_cast<std::uint32_t>(GetCount()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		currentPosition = startPosition + value;
	}

	std::int32_t ByteArrayCodeReader::GetCount() const
	{
		return endPosition - startPosition;
	}

	bool ByteArrayCodeReader::GetCanReadByte() const
	{
		return currentPosition < endPosition;
	}

	ByteArrayCodeReader::ByteArrayCodeReader(const std::string& hexData) : ByteArrayCodeReader(HexUtils::ToByteArray(hexData))
	{
	}

	ByteArrayCodeReader::ByteArrayCodeReader(std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		this->data = data;
		currentPosition = 0;
		startPosition = 0;
		endPosition = data.size();
	}

	ByteArrayCodeReader::ByteArrayCodeReader(std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t count)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		this->data = data;
		if (index < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (count < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		if (static_cast<std::uint32_t>(index) + static_cast<std::uint32_t>(count) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		currentPosition = index;
		startPosition = index;
		endPosition = index + count;
	}

	ByteArrayCodeReader::ByteArrayCodeReader(ArraySegment<std::uint8_t> data)
	{
		if (data.Array.empty())
		{
			ThrowHelper::ThrowArgumentException();
		}
		this->data = data.Array;
		std::int32_t offset = data.Offset;
		currentPosition = offset;
		startPosition = offset;
		endPosition = offset + data.Count;
	}

	std::int32_t ByteArrayCodeReader::ReadByte()
	{
		if (currentPosition >= endPosition)
		{
			return -1;
		}
		return data[currentPosition++];
	}
}
