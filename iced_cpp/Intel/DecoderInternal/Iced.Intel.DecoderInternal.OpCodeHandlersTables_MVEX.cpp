// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Iced.Intel.DecoderInternal.OpCodeHandlersTables_MVEX.h"
#include "MvexOpCodeHandlerReader.h"
#include "TableDeserializer.h"

namespace Iced::Intel::DecoderInternal
{

	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_MVEX::Handlers_0F;
	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_MVEX::Handlers_0F38;
	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlersTables_MVEX::Handlers_0F3A;

	OpCodeHandlersTables_MVEX::StaticConstructor::StaticConstructor()
	{
		auto handlerReader = new MvexOpCodeHandlerReader();
		auto deserializer = TableDeserializer(handlerReader, MaxIdNames, GetSerializedTables());
		deserializer.Deserialize();
		Handlers_0F = deserializer.GetTable(Handlers_0FIndex);
		Handlers_0F38 = deserializer.GetTable(Handlers_0F38Index);
		Handlers_0F3A = deserializer.GetTable(Handlers_0F3AIndex);
	}

	OpCodeHandlersTables_MVEX::StaticConstructor OpCodeHandlersTables_MVEX::staticConstructor;

	std::vector<std::uint8_t> OpCodeHandlersTables_MVEX::GetSerializedTables()
	{
		return std::vector<std::uint8_t> {0x01, 0x08, 0x08, 0x0A, 0x83, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x84, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x85, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x86, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x87, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x88, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x89, 0x24, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x8A, 0x24, 0x00, 0x00, 0x00, 0x01, 0x08, 0x02, 0x02, 0x00, 0x08, 0x00, 0x07, 0x0D, 0x9F, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0D, 0xA0, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0D, 0xA1, 0x24, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x02, 0x07, 0x00, 0x08, 0x00, 0x00, 0x0A, 0xA6, 0x24, 0x0A, 0xA7, 0x24, 0x01, 0x08, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0x9B, 0x25, 0x05, 0x00, 0x14, 0x9C, 0x25, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0x9D, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0x9E, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0x9F, 0x25, 0x05, 0x00, 0x14, 0xA0, 0x25, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0xA1, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x14, 0xA2, 0x25, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x02, 0x18, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x0C, 0xB5, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x05, 0x00, 0x0C, 0xB6, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x0C, 0xB7, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x05, 0x00, 0x0C, 0xB8, 0x24, 0x00, 0x00, 0x02, 0x0B, 0x00, 0x08, 0x00, 0x07, 0x12, 0xB9, 0x24, 0x00, 0x00, 0x00, 0x02, 0x0E, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBA, 0x24, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBB, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBC, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBD, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBE, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xBF, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xC0, 0x24, 0x0C, 0xC1, 0x24, 0x00, 0x00, 0x02, 0x02, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xC2, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xC3, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xC4, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xC5, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xC6, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xC7, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xC8, 0x24, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xC9, 0x24, 0x0F, 0xCA, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xCB, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xCC, 0x24, 0x0F, 0xCD, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xCE, 0x24, 0x0F, 0xCF, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xD0, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xD1, 0x24, 0x0F, 0xD2, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xD3, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xD4, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x0C, 0xD5, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x05, 0x00, 0x0C, 0xD6, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x05, 0x00, 0x0C, 0xD7, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x05, 0x00, 0x0C, 0xD8, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xD9, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xDA, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xDB, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xDC, 0x24, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xDD, 0x24, 0x0F, 0xDE, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xDF, 0x24, 0x0F, 0xE0, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xE1, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xE2, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xE3, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xE4, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xE5, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xE6, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xE7, 0x24, 0x0F, 0xE8, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xE9, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x11, 0xEA, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xEB, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xEC, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xED, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xEE, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x12, 0xEF, 0x24, 0x00, 0x00, 0x00, 0x02, 0x0F, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xF0, 0x24, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xF1, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xF2, 0x24, 0x00, 0x00, 0x00, 0x02, 0x08, 0x00, 0x08, 0x00, 0x07, 0x16, 0xF3, 0x24, 0x16, 0xF4, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x16, 0xF5, 0x24, 0x16, 0xF6, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xF7, 0x24, 0x0F, 0xF8, 0x24, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xF9, 0x24, 0x0F, 0xFA, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xFB, 0x24, 0x0F, 0xFC, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xFD, 0x24, 0x0F, 0xFE, 0x24, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xFF, 0x24, 0x0F, 0x80, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x15, 0x81, 0x25, 0x15, 0x82, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x15, 0x83, 0x25, 0x15, 0x84, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x85, 0x25, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x86, 0x25, 0x0F, 0x87, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x88, 0x25, 0x0F, 0x89, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x8A, 0x25, 0x0F, 0x8B, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x8C, 0x25, 0x0F, 0x8D, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x16, 0x8E, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x16, 0x8F, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x90, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x91, 0x25, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x92, 0x25, 0x0F, 0x93, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x94, 0x25, 0x0F, 0x95, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x96, 0x25, 0x0F, 0x97, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0x98, 0x25, 0x0F, 0x99, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x16, 0x9A, 0x25, 0x00, 0x00, 0x00, 0x02, 0x05, 0x00, 0x06, 0x04, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xA3, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xA4, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xA5, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0C, 0xA6, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xA7, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xA8, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xA9, 0x25, 0x0F, 0xAA, 0x25, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xAB, 0x25, 0x00, 0x00, 0x00, 0x08, 0x07, 0x05, 0x00, 0x0C, 0xAC, 0x25, 0x05, 0x00, 0x0C, 0xAD, 0x25, 0x07, 0x0B, 0xAE, 0x25, 0x0B, 0xAF, 0x25, 0x00, 0x00, 0x08, 0x07, 0x05, 0x00, 0x0C, 0xB0, 0x25, 0x05, 0x00, 0x0C, 0xB1, 0x25, 0x07, 0x0B, 0xB2, 0x25, 0x0B, 0xB3, 0x25, 0x00, 0x00, 0x08, 0x07, 0x0C, 0xB4, 0x25, 0x00, 0x07, 0x0C, 0xB5, 0x25, 0x00, 0x00, 0x00, 0x08, 0x07, 0x0C, 0xB6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08, 0x07, 0x05, 0x00, 0x0C, 0xB7, 0x25, 0x05, 0x00, 0x0C, 0xB8, 0x25, 0x07, 0x0B, 0xB9, 0x25, 0x0B, 0xBA, 0x25, 0x00, 0x00, 0x08, 0x07, 0x05, 0x00, 0x0C, 0xBB, 0x25, 0x05, 0x00, 0x0C, 0xBC, 0x25, 0x07, 0x0B, 0xBD, 0x25, 0x0B, 0xBE, 0x25, 0x00, 0x00, 0x08, 0x07, 0x0C, 0xBF, 0x25, 0x00, 0x07, 0x0C, 0xC0, 0x25, 0x00, 0x00, 0x00, 0x08, 0x07, 0x0C, 0xC1, 0x25, 0x00, 0x00, 0x00, 0x00, 0x02, 0x28, 0x00, 0x01, 0x80, 0x02, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x10, 0xC2, 0x25, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0E, 0xC3, 0x25, 0x00, 0x00, 0x00, 0x02, 0x16, 0x00, 0x08, 0x00, 0x07, 0x13, 0xC4, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x13, 0xC5, 0x25, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x08, 0x00, 0x07, 0x0E, 0xC6, 0x25, 0x0E, 0xC7, 0x25, 0x00, 0x00, 0x02, 0x2B, 0x00, 0x08, 0x00, 0x07, 0x0E, 0xC8, 0x25, 0x0E, 0xC9, 0x25, 0x00, 0x00, 0x02, 0x77, 0x00, 0x08, 0x07, 0x0E, 0xCA, 0x25, 0x00, 0x07, 0x0E, 0xCB, 0x25, 0x00, 0x00, 0x07, 0x00, 0x0E, 0xCC, 0x25, 0x08, 0x07, 0x0E, 0xCD, 0x25, 0x00, 0x07, 0x0E, 0xCE, 0x25, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x08, 0x00, 0x07, 0x0E, 0xCF, 0x25, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0E, 0xD0, 0x25, 0x00, 0x00, 0x00, 0x02, 0x14, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x0E, 0xD1, 0x25, 0x02, 0x19, 0x00, 0x01, 0x80, 0x02, 0x02, 0x18, 0x00, 0x06, 0x04, 0x00, 0x02, 0x0F, 0x00, 0x08, 0x07, 0x0C, 0x8B, 0x24, 0x00, 0x07, 0x00, 0x0C, 0x8C, 0x24, 0x00, 0x00, 0x08, 0x07, 0x0B, 0x8D, 0x24, 0x00, 0x07, 0x00, 0x0B, 0x8E, 0x24, 0x07, 0x00, 0x09, 0x0B, 0x8F, 0x24, 0x0B, 0x90, 0x24, 0x07, 0x09, 0x0B, 0x91, 0x24, 0x0B, 0x92, 0x24, 0x00, 0x02, 0x2E, 0x00, 0x08, 0x07, 0x0F, 0x93, 0x24, 0x00, 0x07, 0x00, 0x0F, 0x94, 0x24, 0x00, 0x00, 0x08, 0x07, 0x0F, 0x95, 0x24, 0x00, 0x07, 0x00, 0x0F, 0x96, 0x24, 0x00, 0x00, 0x08, 0x07, 0x0C, 0x97, 0x24, 0x00, 0x07, 0x00, 0x0C, 0x98, 0x24, 0x00, 0x00, 0x00, 0x08, 0x07, 0x0F, 0x99, 0x24, 0x00, 0x07, 0x00, 0x0F, 0x9A, 0x24, 0x00, 0x00, 0x02, 0x09, 0x00, 0x08, 0x00, 0x07, 0x12, 0x9B, 0x24, 0x00, 0x00, 0x00, 0x02, 0x08, 0x00, 0x08, 0x00, 0x07, 0x0C, 0x9C, 0x24, 0x0C, 0x9D, 0x24, 0x00, 0x00, 0x08, 0x00, 0x07, 0x0E, 0x9E, 0x24, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x01, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x12, 0xA2, 0x24, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x00, 0x07, 0x0C, 0xA3, 0x24, 0x00, 0x00, 0x02, 0x04, 0x00, 0x08, 0x00, 0x07, 0x0B, 0xA4, 0x24, 0x0B, 0xA5, 0x24, 0x00, 0x00, 0x02, 0x2E, 0x00, 0x06, 0x04, 0x02, 0x02, 0x13, 0x00, 0x08, 0x07, 0x13, 0xA8, 0x24, 0x00, 0x07, 0x00, 0x13, 0xA9, 0x24, 0x00, 0x00, 0x02, 0x18, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xAA, 0x24, 0x0F, 0xAB, 0x24, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xAC, 0x24, 0x0F, 0xAD, 0x24, 0x00, 0x00, 0x02, 0x06, 0x00, 0x08, 0x00, 0x00, 0x07, 0x0C, 0xAE, 0x24, 0x00, 0x00, 0x02, 0x04, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xAF, 0x24, 0x0F, 0xB0, 0x24, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xB1, 0x24, 0x0F, 0xB2, 0x24, 0x00, 0x00, 0x02, 0x0A, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xB3, 0x24, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x08, 0x00, 0x07, 0x0F, 0xB4, 0x24, 0x00, 0x00, 0x00, 0x00};
	}
}
