// C# helper headers

#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "TableDeserializer.h"
#include "SerializedDataKind.g.h"

using namespace Iced::Intel::Internal;

namespace Iced::Intel::DecoderInternal
{

	HandlerInfo::HandlerInfo(std::shared_ptr<OpCodeHandler> handler)
	{
		this->handler = handler;
		handlers = std::nullopt;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public HandlerInfo(OpCodeHandler?[] handlers)
	HandlerInfo::HandlerInfo(const std::vector<std::shared_ptr<OpCodeHandler>>& handlers)
	{
		handler = nullptr;
		this->handlers = handlers;
	}

	TableDeserializer::TableDeserializer(OpCodeHandlerReader* handlerReader, std::int32_t maxIds, const std::vector<std::uint8_t>& data) : reader(data)
	{
		this->handlerReader = handlerReader;
		idToHandler = std::vector<HandlerInfo>();
		idToHandler.reserve(maxIds);
		handlerArray = std::vector<std::shared_ptr<OpCodeHandler>>(1);
	}

	void TableDeserializer::Deserialize()
	{
		for (std::uint32_t currentIndex = 0; reader.GetCanRead(); currentIndex++)
		{
			switch (static_cast<SerializedDataKind>(reader.ReadByte()))
			{
			case SerializedDataKind::HandlerReference:
				idToHandler.push_back(HandlerInfo(ReadHandler()));
				break;
			case SerializedDataKind::ArrayReference:
				idToHandler.push_back(HandlerInfo(ReadHandlers(static_cast<std::int32_t>(reader.ReadCompressedUInt32()))));
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
		}
		if (reader.GetCanRead())
		{
			throw std::runtime_error("invalid operation");
		}
	}

	LegacyOpCodeHandlerKind TableDeserializer::ReadLegacyOpCodeHandlerKind()
	{
		return static_cast<LegacyOpCodeHandlerKind>(reader.ReadByte());
	}

	VexOpCodeHandlerKind TableDeserializer::ReadVexOpCodeHandlerKind()
	{
		return static_cast<VexOpCodeHandlerKind>(reader.ReadByte());
	}

	EvexOpCodeHandlerKind TableDeserializer::ReadEvexOpCodeHandlerKind()
	{
		return static_cast<EvexOpCodeHandlerKind>(reader.ReadByte());
	}

	MvexOpCodeHandlerKind TableDeserializer::ReadMvexOpCodeHandlerKind()
	{
		return static_cast<MvexOpCodeHandlerKind>(reader.ReadByte());
	}

	Iced::Intel::Code TableDeserializer::ReadCode()
	{
		return static_cast<Code>(reader.ReadCompressedUInt32());
	}

	Iced::Intel::Register TableDeserializer::ReadRegister()
	{
		return static_cast<Register>(reader.ReadByte());
	}

	Iced::Intel::DecoderOptions TableDeserializer::ReadDecoderOptions()
	{
		return static_cast<DecoderOptions>(reader.ReadCompressedUInt32());
	}

	HandlerFlags TableDeserializer::ReadHandlerFlags()
	{
		return static_cast<HandlerFlags>(reader.ReadCompressedUInt32());
	}

	LegacyHandlerFlags TableDeserializer::ReadLegacyHandlerFlags()
	{
		return static_cast<LegacyHandlerFlags>(reader.ReadCompressedUInt32());
	}

	Iced::Intel::TupleType TableDeserializer::ReadTupleType()
	{
		return static_cast<TupleType>(reader.ReadByte());
	}

	bool TableDeserializer::ReadBoolean()
	{
		return reader.ReadByte() != 0;
	}

	std::int32_t TableDeserializer::ReadInt32()
	{
		return static_cast<std::int32_t>(reader.ReadCompressedUInt32());
	}

	std::shared_ptr<OpCodeHandler> TableDeserializer::ReadHandler()
	{
		std::shared_ptr<OpCodeHandler> tempVar = ReadHandlerOrNull();
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return ReadHandlerOrNull() ?? throw new InvalidOperationException();
		return (tempVar != nullptr) ? tempVar : throw std::runtime_error("invalid operation");
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public OpCodeHandler? ReadHandlerOrNull()
	std::shared_ptr<OpCodeHandler> TableDeserializer::ReadHandlerOrNull()
	{
		std::int32_t count = handlerReader->ReadHandlers(*this, handlerArray, 0);
		if (count != 1)
		{
			throw std::runtime_error("invalid operation");
		}
		return handlerArray[0];
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public OpCodeHandler?[] ReadHandlers(int count)
	std::vector<std::shared_ptr<OpCodeHandler>> TableDeserializer::ReadHandlers(std::int32_t count)
	{
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: var handlers = std::make_shared<OpCodeHandler>?[count];
		auto handlers = std::vector<std::shared_ptr<OpCodeHandler>>(count);
		for (std::int32_t i = 0; i < handlers.size();)
		{
			std::int32_t num = handlerReader->ReadHandlers(*this, handlers, i);
			if (num <= 0 || static_cast<std::uint32_t>(i) + static_cast<std::uint32_t>(num) > static_cast<std::uint32_t>(handlers.size()))
			{
				throw std::runtime_error("invalid operation");
			}
			i += num;
		}
		return handlers;
	}

	std::shared_ptr<OpCodeHandler> TableDeserializer::ReadHandlerReference()
	{
		std::uint32_t index = reader.ReadByte();
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return idToHandler[(int)index].handler ?? throw new InvalidOperationException();
		return ((idToHandler[static_cast<std::int32_t>(index)].handler) != nullptr) ? idToHandler[static_cast<std::int32_t>(index)].handler : throw std::runtime_error("invalid operation");
	}

	std::vector<std::shared_ptr<OpCodeHandler>> TableDeserializer::ReadArrayReference(std::uint32_t kind)
	{
		if (reader.ReadByte() != kind)
		{
			throw std::runtime_error("invalid operation");
		}
		return GetTable(reader.ReadByte());
	}

	std::vector<std::shared_ptr<OpCodeHandler>> TableDeserializer::GetTable(std::uint32_t index)
	{
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
		//ORIGINAL LINE: return (idToHandler[(int)index].handlers ?? throw new InvalidOperationException())!;
	//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
	//ORIGINAL LINE: return (idToHandler[(int)index].handlers ?? throw new InvalidOperationException());
		return ((idToHandler[static_cast<std::int32_t>(index)].handlers) != std::nullopt) ? idToHandler[static_cast<std::int32_t>(index)].handlers.value() : throw std::runtime_error("invalid operation");
	}
}
