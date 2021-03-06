// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "MemorySizes.h"
#include "../IcedConstants.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::GasFormatterInternal
{

	std::vector<FormatterString> MemorySizes::AllMemorySizes = GetMemorySizes();

	std::vector<FormatterString> MemorySizes::GetMemorySizes()
	{
		// GENERATOR-BEGIN: ConstData
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		auto empty = FormatterString("");
		auto b1to2 = FormatterString("1to2");
		auto b1to4 = FormatterString("1to4");
		auto b1to8 = FormatterString("1to8");
		auto b1to16 = FormatterString("1to16");
		auto b1to32 = FormatterString("1to32");
		// GENERATOR-END: ConstData
		std::vector<std::uint8_t> bcstToData = { 0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x03, 0x02, 0x01, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x04, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x03, 0x05, 0x04, 0x03, 0x04, 0x04, 0x03, 0x03, 0x04 };
		auto infos = std::vector<FormatterString>(IcedConstants::MemorySizeEnumCount);
		for (std::size_t i = 0; i < infos.size(); i++)
		{
			FormatterString bcstTo;
			if (i < static_cast<std::int32_t>(IcedConstants::FirstBroadcastMemorySize))
			{
				bcstTo = empty;
			}
			else
			{
				auto switchTempVar_0 = bcstToData[i - static_cast<std::int32_t>(IcedConstants::FirstBroadcastMemorySize)];
				// GENERATOR-BEGIN: BroadcastToKindSwitch
				// ⚠️This was generated by GENERATOR!🦹‍♂️
				// GENERATOR-END: BroadcastToKindSwitch

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: bcstTo = (switchTempVar_0 == 0x00) ? empty : (switchTempVar_0 == 0x01) ? b1to2 : (switchTempVar_0 == 0x02) ? b1to4 : (switchTempVar_0 == 0x03) ? b1to8 : (switchTempVar_0 == 0x04) ? b1to16 : (switchTempVar_0 == 0x05) ? b1to32 : throw new InvalidOperationException();
				bcstTo = (switchTempVar_0 == 0x00) ? empty : (switchTempVar_0 == 0x01) ? b1to2 : (switchTempVar_0 == 0x02) ? b1to4 : (switchTempVar_0 == 0x03) ? b1to8 : (switchTempVar_0 == 0x04) ? b1to16 : (switchTempVar_0 == 0x05) ? b1to32 : throw std::runtime_error("unexpected");
			}
			infos[i] = bcstTo;
		}
		return infos;
	}
}
