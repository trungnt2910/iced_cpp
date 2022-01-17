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

#include "DataReader.h"
#include "../../Array2.h"

namespace Iced::Intel::Internal
{

	std::int32_t DataReader::GetIndex() const
	{
		return index;
	}

	void DataReader::SetIndex(std::int32_t value)
	{
		index = value;
	}

	bool DataReader::GetCanRead() const
	{
		return static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(data.size());
	}

	DataReader::DataReader(const std::vector<std::uint8_t>& data) : DataReader(data, 0)
	{
	}

	DataReader::DataReader(const std::vector<std::uint8_t>& data, std::int32_t maxStringLength)
	{
		this->data = data;
		stringData = maxStringLength == 0 ? System::Array2::Empty<char>() : std::vector<char>(maxStringLength);
		index = 0;
	}

	std::uint8_t DataReader::ReadByte()
	{
		return data[index++];
	}

	std::uint32_t DataReader::ReadCompressedUInt32()
	{
		std::uint32_t result = 0;
		for (std::int32_t shift = 0; shift < 32; shift += 7)
		{
			std::uint32_t b = ReadByte();
			if ((b & 0x80) == 0)
			{
				return result | (b << shift);
			}
			result |= (b & 0x7F) << shift;
		}
		throw InvalidOperationException();
	}

	std::string DataReader::ReadAsciiString()
	{
		std::int32_t length = ReadByte();
		auto stringData = this->stringData;
		for (std::int32_t i = 0; i < length; i++)
		{
			stringData[i] = static_cast<char>(ReadByte());
		}
		return std::string(stringData, 0, length);
	}
}
