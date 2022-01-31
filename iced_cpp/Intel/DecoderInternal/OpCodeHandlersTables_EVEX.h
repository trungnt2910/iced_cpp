// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "OpCodeHandlers.h"
#include "EvexOpCodeHandlerReader.h"
#include "TableDeserializer.h"

#include <algorithm>
#include <array>
#include <tuple>

namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandlersTables_EVEX_Constructor final
	{
	private:
		friend class OpCodeHandlersTables_EVEX;
		static constexpr auto GetInfo(
			const std::vector<std::uint8_t> & data, 
			std::int32_t MaxIdNames, 
			std::uint32_t Handlers_0FIndex,
			std::uint32_t Handlers_0F38Index,
			std::uint32_t Handlers_0F3AIndex,
			std::uint32_t Handlers_MAP5Index,
			std::uint32_t Handlers_MAP6Index)
		{
			auto handlerReader = EvexOpCodeHandlerReader();
			auto deserializer = EvexTableDeserializer(&handlerReader, MaxIdNames, data);
			deserializer.Deserialize();
			return std::make_tuple(
				std::to_array<std::size_t>({
					deserializer.GetTable(Handlers_0FIndex).size(),
					deserializer.GetTable(Handlers_0F38Index).size(),
					deserializer.GetTable(Handlers_0F3AIndex).size(),
					deserializer.GetTable(Handlers_MAP5Index).size(),
					deserializer.GetTable(Handlers_MAP6Index).size(),
				}),
				deserializer.GetReaderPool().GetSizes()
			);
		}
		template <std::size_t N, std::array<std::size_t, N> Sizes>
		static constexpr auto GetPool(
			const std::vector<std::uint8_t>& data,
			std::int32_t MaxIdNames)
		{
			auto handlerReader = EvexOpCodeHandlerReader();
			auto deserializer = EvexTableDeserializer(&handlerReader, MaxIdNames, data);
			deserializer.Deserialize();
			return EvexArrayPool<N, Sizes>(deserializer.GetReaderPool());
		}
		template <std::size_t N, std::array<std::size_t, N> PoolSizes, std::array<std::size_t, 5> PointerSizes>
		static constexpr auto GetPointers(
			const EvexArrayPool<N, PoolSizes>& Apool,
			const std::vector<std::uint8_t>& data,
			std::int32_t MaxIdNames,
			std::uint32_t Handlers_0FIndex,
			std::uint32_t Handlers_0F38Index,
			std::uint32_t Handlers_0F3AIndex,
			std::uint32_t Handlers_MAP5Index,
			std::uint32_t Handlers_MAP6Index)
		{
			auto handlerReader = EvexOpCodeHandlerReader();
			auto deserializer = EvexTableDeserializer(&handlerReader, MaxIdNames, data);
			deserializer.Deserialize();
			auto relocInfo = Apool.GetRelocInfo(deserializer.GetReaderPool());

			const auto reloc = [&](const OpCodeHandler* ptr)
			{
				for (const auto& [oldPtr, newPtr] : relocInfo)
				{
					if (ptr == oldPtr)
					{
						return dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
				return ptr;
			};

			auto Handlers_0F = std::array<const OpCodeHandler*, PointerSizes.at(0)>();
			auto Handlers_0FVec = deserializer.GetTable(Handlers_0FIndex);
			std::transform(Handlers_0FVec.begin(), Handlers_0FVec.end(), Handlers_0F.begin(), reloc);
			auto Handlers_0F38 = std::array<const OpCodeHandler*, PointerSizes.at(1)>();
			auto Handlers_0F38Vec = deserializer.GetTable(Handlers_0F38Index);
			std::transform(Handlers_0F38Vec.begin(), Handlers_0F38Vec.end(), Handlers_0F38.begin(), reloc);
			auto Handlers_0F3A = std::array<const OpCodeHandler*, PointerSizes.at(2)>();
			auto Handlers_0F3AVec = deserializer.GetTable(Handlers_0F3AIndex);
			std::transform(Handlers_0F3AVec.begin(), Handlers_0F3AVec.end(), Handlers_0F3A.begin(), reloc);
			auto Handlers_MAP5 = std::array<const OpCodeHandler*, PointerSizes.at(3)>();
			auto Handlers_MAP5Vec = deserializer.GetTable(Handlers_MAP5Index);
			std::transform(Handlers_MAP5Vec.begin(), Handlers_MAP5Vec.end(), Handlers_MAP5.begin(), reloc);
			auto Handlers_MAP6 = std::array<const OpCodeHandler*, PointerSizes.at(4)>();
			auto Handlers_MAP6Vec = deserializer.GetTable(Handlers_MAP6Index);
			std::transform(Handlers_MAP6Vec.begin(), Handlers_MAP6Vec.end(), Handlers_MAP6.begin(), reloc);

			return std::make_tuple(Handlers_0F, Handlers_0F38, Handlers_0F3A, Handlers_MAP5, Handlers_MAP6);
		}
		constexpr OpCodeHandlersTables_EVEX_Constructor() = delete;
	};

	class OpCodeHandlersTables_EVEX final
	{
	private:
#include "OpCodeHandlersTables_EVEX.g.h"
	private:
		inline static constexpr auto SizeInfo = 
			OpCodeHandlersTables_EVEX_Constructor::GetInfo(
				std::vector<std::uint8_t>(SerializedTables.begin(), SerializedTables.end()),
				MaxIdNames, 
				Handlers_0FIndex, 
				Handlers_0F38Index, 
				Handlers_0F3AIndex, 
				Handlers_MAP5Index, 
				Handlers_MAP6Index);
		inline static constexpr auto ArraySizes = std::get<0>(SizeInfo);
		inline static constexpr auto PoolSizes = std::get<1>(SizeInfo);
		
		inline static constexpr auto PoolElements = PoolSizes.size();
		inline static constexpr auto Pool = OpCodeHandlersTables_EVEX_Constructor::GetPool
			<PoolElements, PoolSizes>(
				std::vector<std::uint8_t>(SerializedTables.begin(), SerializedTables.end()),
				MaxIdNames);

		inline static constexpr auto Pointers = OpCodeHandlersTables_EVEX_Constructor::GetPointers
			<PoolElements, PoolSizes, ArraySizes>(
				Pool,
				std::vector<std::uint8_t>(SerializedTables.begin(), SerializedTables.end()),
				MaxIdNames,
				Handlers_0FIndex,
				Handlers_0F38Index,
				Handlers_0F3AIndex,
				Handlers_MAP5Index,
				Handlers_MAP6Index);
	public:
		inline static constexpr auto Handlers_0F = std::get<0>(Pointers);
		inline static constexpr auto Handlers_0F38 = std::get<1>(Pointers);
		inline static constexpr auto Handlers_0F3A = std::get<2>(Pointers);
		inline static constexpr auto Handlers_MAP5 = std::get<3>(Pointers);
		inline static constexpr auto Handlers_MAP6 = std::get<4>(Pointers);
	};
}
