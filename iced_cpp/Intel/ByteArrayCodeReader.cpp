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

#include "HexUtils.h"

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

	ByteArrayCodeReader::ByteArrayCodeReader(const std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		this->data = data;
		currentPosition = 0;
		startPosition = 0;
		endPosition = (std::int32_t)data.size();
	}

	ByteArrayCodeReader::ByteArrayCodeReader(const std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t count)
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

	// The author used an ArraySegment, std::basic_string_view is basically the same.
	ByteArrayCodeReader::ByteArrayCodeReader(const std::basic_string_view<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentException();
		}
		this->data = std::vector<std::uint8_t>(data.begin(), data.end());
		currentPosition = 0;
		startPosition = 0;
		endPosition = (std::int32_t)data.length();
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
