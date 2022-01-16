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

#include "MemorySizeExtensions.h"
#include "ThrowHelper.h"
#include "Static.h"
#include "Iced.Intel.IcedConstants.h"

namespace Iced::Intel
{

	Iced::Intel::MemorySize MemorySizeInfo::GetMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>(memorySize);
	}

	std::int32_t MemorySizeInfo::GetSize() const
	{
		return size;
	}

	std::int32_t MemorySizeInfo::GetElementSize() const
	{
		return elementSize;
	}

	Iced::Intel::MemorySize MemorySizeInfo::GetElementType() const
	{
		return static_cast<Iced::Intel::MemorySize>(elementType);
	}

	bool MemorySizeInfo::IsSigned() const
	{
		return isSigned;
	}

	bool MemorySizeInfo::IsBroadcast() const
	{
		return isBroadcast;
	}

	bool MemorySizeInfo::IsPacked() const
	{
		return elementSize < size;
	}

	std::int32_t MemorySizeInfo::GetElementCount() const
	{
		return elementSize == size ? 1 : size / elementSize;
	}

	MemorySizeInfo::MemorySizeInfo(Iced::Intel::MemorySize memorySize, std::int32_t size, std::int32_t elementSize, Iced::Intel::MemorySize elementType, bool isSigned, bool isBroadcast)
	{
		if (size < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_size();
		}
		if (elementSize < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_elementSize();
		}
		if (elementSize > size)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_elementSize();
		}
		Static::Assert(IcedConstants::MemorySizeEnumCount <= std::numeric_limits<std::uint8_t>::max() + 1 ? 0 : -1);
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(size <= std::numeric_limits<std::uint16_t>::max());
		this->size = static_cast<std::uint16_t>(size);
		assert(elementSize <= std::numeric_limits<std::uint16_t>::max());
		this->elementSize = static_cast<std::uint16_t>(elementSize);
		Static::Assert(IcedConstants::MemorySizeEnumCount <= std::numeric_limits<std::uint8_t>::max() + 1 ? 0 : -1);
		this->elementType = static_cast<std::uint8_t>(elementType);
		this->isSigned = isSigned;
		this->isBroadcast = isBroadcast;
	}
}
