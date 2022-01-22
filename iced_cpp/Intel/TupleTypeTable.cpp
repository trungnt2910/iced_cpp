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

#include "TupleTypeTable.h"

namespace Iced::Intel
{

	std::vector<std::uint8_t> TupleTypeTable::tupleTypeData = { 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x08, 0x04, 0x10, 0x04, 0x20, 0x04, 0x40, 0x04, 0x10, 0x08, 0x20, 0x08, 0x40, 0x08, 0x04, 0x02, 0x08, 0x02, 0x10, 0x02, 0x20, 0x02, 0x40, 0x02 };

	std::uint32_t TupleTypeTable::GetDisp8N(TupleType tupleType, bool bcst)
	{
		std::int32_t index = (static_cast<std::int32_t>(tupleType) << 1) | (bcst ? 1 : 0);
		assert(static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(tupleTypeData.size()));
		return tupleTypeData[index];
	}
}
