// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "OpCodeHandlers.h"
#include "../Internal/DataReader.h"
#include "LegacyOpCodeHandlerKind.g.h"
#include "VexOpCodeHandlerKind.g.h"
#include "EvexOpCodeHandlerKind.g.h"
#include "MvexOpCodeHandlerKind.g.h"
#include "../Code.g.h"
#include "../Register.g.h"
#include "../DecoderOptions.g.h"
#include "HandlerFlags.g.h"
#include "LegacyHandlerFlags.g.h"
#include "../TupleType.g.h"
#include "../Internal/MemoryPool.h"
#include "SerializedDataKind.g.h"
#include <optional>
#include <string_view>
#include <vector>
#include <type_traits>

namespace Iced::Intel::DecoderInternal
{
	template <typename T>
	concept IOpCodeHandler = std::is_base_of_v<OpCodeHandler, T>;

	template <IOpCodeHandler... Types>
	class TableDeserializer;

	template <IOpCodeHandler... Types>
	class OpCodeHandlerReader
	{
	protected:
		Internal::VectorPool<Types...> pool;
	public:
		constexpr const auto& GetPool() const
		{
			return pool;
		}
		constexpr virtual std::int32_t ReadHandlers(TableDeserializer<Types...>& deserializer, std::vector<const OpCodeHandler*>& result, std::int32_t resultIndex) = 0;
	};
	class HandlerInfo
	{
	public:
		const OpCodeHandler* handler = nullptr;
		std::optional<std::vector<const OpCodeHandler*>> handlers;
		constexpr HandlerInfo(const OpCodeHandler* handler)
			: handler(handler), handlers(std::nullopt)
		{
		}
		constexpr HandlerInfo(const std::vector<const OpCodeHandler*>& handlers)
			: handler(nullptr), handlers(handlers)
		{
		}
		constexpr HandlerInfo() = default;
		constexpr ~HandlerInfo() = default;
	};

	template <IOpCodeHandler... Types>
	class TableDeserializer
	{
	private:
		Iced::Intel::Internal::DataReader<std::basic_string_view<std::uint8_t>> reader;
		OpCodeHandlerReader<Types...>* handlerReader;
		std::vector<HandlerInfo> idToHandler;
		std::vector<const OpCodeHandler*> handlerArray;
	public:
		constexpr TableDeserializer(
			OpCodeHandlerReader<Types...>* handlerReader,
			std::int32_t maxIds,
			const std::vector<std::uint8_t>& data)
			: reader(data)
		{
			this->handlerReader = handlerReader;
			idToHandler = std::vector<HandlerInfo>();
			idToHandler.reserve(maxIds);
			handlerArray = std::vector<const OpCodeHandler*>(1);
		}
		constexpr void Deserialize()
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
		constexpr LegacyOpCodeHandlerKind ReadLegacyOpCodeHandlerKind()
		{
			return static_cast<LegacyOpCodeHandlerKind>(reader.ReadByte());
		}
		constexpr VexOpCodeHandlerKind ReadVexOpCodeHandlerKind()
		{
			return static_cast<VexOpCodeHandlerKind>(reader.ReadByte());
		}
		constexpr EvexOpCodeHandlerKind ReadEvexOpCodeHandlerKind()
		{
			return static_cast<EvexOpCodeHandlerKind>(reader.ReadByte());
		}
		constexpr MvexOpCodeHandlerKind ReadMvexOpCodeHandlerKind()
		{
			return static_cast<MvexOpCodeHandlerKind>(reader.ReadByte());
		}
		constexpr Iced::Intel::Code ReadCode()
		{
			return static_cast<Code>(reader.ReadCompressedUInt32());
		}
		constexpr Iced::Intel::Register ReadRegister()
		{
			return static_cast<Register>(reader.ReadByte());
		}
		constexpr Iced::Intel::DecoderOptions ReadDecoderOptions()
		{
			return static_cast<DecoderOptions>(reader.ReadCompressedUInt32());
		}
		constexpr HandlerFlags ReadHandlerFlags()
		{
			return static_cast<HandlerFlags>(reader.ReadCompressedUInt32());
		}
		constexpr LegacyHandlerFlags ReadLegacyHandlerFlags()
		{
			return static_cast<LegacyHandlerFlags>(reader.ReadCompressedUInt32());
		}
		constexpr Iced::Intel::TupleType ReadTupleType()
		{
			return static_cast<TupleType>(reader.ReadByte());
		}
		constexpr bool ReadBoolean()
		{
			return reader.ReadByte() != 0;
		}
		constexpr std::int32_t ReadInt32()
		{
			return static_cast<std::int32_t>(reader.ReadCompressedUInt32());
		}
		constexpr const OpCodeHandler* ReadHandler()
		{
			const OpCodeHandler* tempVar = ReadHandlerOrNull();
			return (tempVar != nullptr) ? tempVar : throw std::runtime_error("invalid operation");
		}
		constexpr const OpCodeHandler* ReadHandlerOrNull()
		{
			std::int32_t count = handlerReader->ReadHandlers(*this, handlerArray, 0);
			if (count != 1)
			{
				throw std::runtime_error("invalid operation");
			}
			return handlerArray[0];
		}
		constexpr std::vector<const OpCodeHandler*> ReadHandlers(std::int32_t count)
		{
			auto handlers = std::vector<const OpCodeHandler*>(count);
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
		constexpr const OpCodeHandler* ReadHandlerReference()
		{
			std::uint32_t index = reader.ReadByte();
			return ((idToHandler[static_cast<std::int32_t>(index)].handler) != nullptr) ? idToHandler[static_cast<std::int32_t>(index)].handler : throw std::runtime_error("invalid operation");
		}
		constexpr std::vector<const OpCodeHandler*> ReadArrayReference(std::uint32_t kind)
		{
			if (reader.ReadByte() != kind)
			{
				throw std::runtime_error("invalid operation");
			}
			return GetTable(reader.ReadByte());
		}
		constexpr std::vector<const OpCodeHandler*> GetTable(std::uint32_t index)
		{
			return ((idToHandler[static_cast<std::int32_t>(index)].handlers) != std::nullopt) ? idToHandler[static_cast<std::int32_t>(index)].handlers.value() : throw std::runtime_error("invalid operation");
		}

		
		constexpr const auto& GetReaderPool() const
		{
			return handlerReader->GetPool();
		}
		
		constexpr TableDeserializer() = default;
	};
}
