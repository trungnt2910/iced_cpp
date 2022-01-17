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

#include "Iced.Intel.MemorySizeExtensions.h"
#include "Iced.Intel.IcedConstants.h"
#include "ThrowHelper.h"

namespace Iced::Intel
{

	bool MemorySizeExtensions::IsBroadcast(MemorySize memorySize)
	{
		return memorySize >= IcedConstants::FirstBroadcastMemorySize;
	}

	MemorySizeInfo MemorySizeExtensions::GetInfo(MemorySize memorySize)
	{
		const auto& infos = MemorySizeInfos;
		if (static_cast<std::uint32_t>(memorySize) >= static_cast<std::uint32_t>(infos.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_memorySize();
		}
		return infos[static_cast<std::int32_t>(memorySize)];
	}

	std::int32_t MemorySizeExtensions::GetSize(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetSize();
	}

	std::int32_t MemorySizeExtensions::GetElementSize(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementSize();
	}

	MemorySize MemorySizeExtensions::GetElementType(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementType();
	}

	MemorySizeInfo MemorySizeExtensions::GetElementTypeInfo(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementType());
	}

	bool MemorySizeExtensions::IsSigned(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).IsSigned();
	}

	bool MemorySizeExtensions::IsPacked(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).IsPacked();
	}

	std::int32_t MemorySizeExtensions::GetElementCount(MemorySize memorySize)
	{
		return Iced::Intel::MemorySizeExtensions::GetInfo(memorySize).GetElementCount();
	}
}
