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

#include "Iced.Intel.DecoderInternal.OpCodeHandlersTables_XOP.h"
#include "VexOpCodeHandlerReader.h"
#include "TableDeserializer.h"

namespace Iced::Intel::DecoderInternal
{

	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_XOP::Handlers_MAP8;
	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_XOP::Handlers_MAP9;
	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_XOP::Handlers_MAP10;

	OpCodeHandlersTables_XOP::StaticConstructor::StaticConstructor()
	{
		auto handlerReader = new VexOpCodeHandlerReader();
		auto deserializer = TableDeserializer(handlerReader, MaxIdNames, GetSerializedTables());
		deserializer.Deserialize();
		Handlers_MAP8 = deserializer.GetTable(Handlers_MAP8Index);
		Handlers_MAP9 = deserializer.GetTable(Handlers_MAP9Index);
		Handlers_MAP10 = deserializer.GetTable(Handlers_MAP10Index);
	}

	OpCodeHandlersTables_XOP::StaticConstructor OpCodeHandlersTables_XOP::staticConstructor;

	std::vector<std::uint8_t> OpCodeHandlersTables_XOP::GetSerializedTables()
	{
		return std::vector<std::uint8_t> {0x01, 0x08, 0x00, 0x0A, 0x0E, 0x1C, 0x88, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x8A, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x8C, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x8E, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x90, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x92, 0x20, 0x00, 0x0A, 0x0E, 0x1C, 0x94, 0x20, 0x00, 0x01, 0x08, 0x00, 0x0A, 0x0E, 0x1C, 0x96, 0x20, 0x00, 0x02, 0x04, 0x00, 0x0A, 0x0E, 0x1C, 0x98, 0x20, 0x00, 0x00, 0x01, 0x08, 0x0A, 0x0E, 0x22, 0x9A, 0x20, 0x00, 0x0A, 0x0E, 0x22, 0x9C, 0x20, 0x00, 0x02, 0x06, 0x00, 0x01, 0x08, 0x0A, 0x0E, 0x1B, 0xCD, 0x20, 0x00, 0x0A, 0x0E, 0x1B, 0xCF, 0x20, 0x00, 0x02, 0x06, 0x00, 0x01, 0x80, 0x02, 0x02, 0x85, 0x01, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xEA, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xEB, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xEC, 0x1F, 0x00, 0x00, 0x02, 0x06, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xED, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xEE, 0x1F, 0x00, 0x00, 0x02, 0x05, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xEF, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xF0, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xF1, 0x1F, 0x00, 0x00, 0x02, 0x06, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xF2, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xF3, 0x1F, 0x00, 0x00, 0x01, 0x0A, 0x09, 0x0E, 0x2E, 0x4D, 0xF4, 0x1F, 0x2E, 0x6D, 0xF5, 0x1F, 0x0E, 0x26, 0x4D, 0xF6, 0x1F, 0x26, 0x6D, 0xF7, 0x1F, 0x0A, 0x09, 0x0E, 0x2E, 0x4D, 0xF8, 0x1F, 0x00, 0x0E, 0x26, 0x4D, 0xF9, 0x1F, 0x00, 0x01, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xFA, 0x1F, 0x00, 0x00, 0x02, 0x0F, 0x00, 0x0A, 0x0E, 0x09, 0x2E, 0x4D, 0xFB, 0x1F, 0x00, 0x00, 0x02, 0x09, 0x00, 0x0A, 0x0E, 0x09, 0x39, 0x4D, 0xFC, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x39, 0x4D, 0xFD, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x39, 0x4D, 0xFE, 0x1F, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x39, 0x4D, 0xFF, 0x1F, 0x00, 0x00, 0x02, 0x08, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x80, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x81, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x82, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x83, 0x20, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x84, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x85, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x86, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x2C, 0x4D, 0x87, 0x20, 0x00, 0x00, 0x02, 0x10, 0x00, 0x01, 0x80, 0x02, 0x00, 0x08, 0x06, 0x00, 0x08, 0x06, 0x01, 0x02, 0x0F, 0x00, 0x08, 0x06, 0x02, 0x02, 0x6D, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0x9E, 0x20, 0x00, 0x09, 0x36, 0x6D, 0x9F, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xA0, 0x20, 0x00, 0x09, 0x36, 0x6D, 0xA1, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xA2, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xA3, 0x20, 0x00, 0x00, 0x02, 0x0C, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xA4, 0x20, 0x29, 0x4D, 0xA5, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xA6, 0x20, 0x29, 0x4D, 0xA7, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xA8, 0x20, 0x29, 0x4D, 0xA9, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xAA, 0x20, 0x29, 0x4D, 0xAB, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xAC, 0x20, 0x29, 0x4D, 0xAD, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xAE, 0x20, 0x29, 0x4D, 0xAF, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xB0, 0x20, 0x29, 0x4D, 0xB1, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xB2, 0x20, 0x29, 0x4D, 0xB3, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xB4, 0x20, 0x29, 0x4D, 0xB5, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xB6, 0x20, 0x29, 0x4D, 0xB7, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xB8, 0x20, 0x29, 0x4D, 0xB9, 0x20, 0x00, 0x0A, 0x0E, 0x09, 0x38, 0x4D, 0xBA, 0x20, 0x29, 0x4D, 0xBB, 0x20, 0x00, 0x02, 0x25, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xBC, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xBD, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xBE, 0x20, 0x00, 0x00, 0x01, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xBF, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC0, 0x20, 0x00, 0x00, 0x02, 0x03, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC1, 0x20, 0x00, 0x00, 0x02, 0x05, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC2, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC3, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC4, 0x20, 0x00, 0x00, 0x01, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC5, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC6, 0x20, 0x00, 0x00, 0x02, 0x03, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC7, 0x20, 0x00, 0x00, 0x02, 0x05, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC8, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xC9, 0x20, 0x00, 0x00, 0x0A, 0x0E, 0x09, 0x36, 0x4D, 0xCA, 0x20, 0x00, 0x00, 0x02, 0x1C, 0x00, 0x01, 0x80, 0x02, 0x02, 0x10, 0x00, 0x0A, 0x0E, 0x14, 0xCB, 0x20, 0x00, 0x00, 0x08, 0x06, 0x03, 0x02, 0xED, 0x01, 0x00};
	}
}
