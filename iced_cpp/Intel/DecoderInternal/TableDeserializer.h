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
#include <vector>
#include <csharp/exceptionhelper.h>

#include <string_view>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel::DecoderInternal { class TableDeserializer; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandlerReader
	{
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public abstract int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex);
		virtual std::int32_t ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex) = 0;
	};
	/* readonly */
	class HandlerInfo
	{
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public OpCodeHandler? handler;
		std::shared_ptr<OpCodeHandler> handler;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public OpCodeHandler?[]? handlers;
		std::optional<std::vector<std::shared_ptr<OpCodeHandler>>> handlers;
		HandlerInfo(std::shared_ptr<OpCodeHandler> handler);
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public HandlerInfo(OpCodeHandler?[] handlers)
		HandlerInfo(const std::vector<std::shared_ptr<OpCodeHandler>>& handlers);

		HandlerInfo() = default;
	};
	class TableDeserializer
	{
	private:
		Iced::Intel::Internal::DataReader<std::basic_string_view<std::uint8_t>> reader;
		/* readonly */
		OpCodeHandlerReader* handlerReader;
		/* readonly */
		std::vector<HandlerInfo> idToHandler;
		/* readonly */
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: OpCodeHandler?[] handlerArray;
		std::vector<std::shared_ptr<OpCodeHandler>> handlerArray;
	public:
		TableDeserializer(OpCodeHandlerReader* handlerReader, std::int32_t maxIds, const std::vector<std::uint8_t>& data);
		void Deserialize();
		LegacyOpCodeHandlerKind ReadLegacyOpCodeHandlerKind();
		VexOpCodeHandlerKind ReadVexOpCodeHandlerKind();
		EvexOpCodeHandlerKind ReadEvexOpCodeHandlerKind();
		MvexOpCodeHandlerKind ReadMvexOpCodeHandlerKind();
		Code ReadCode();
		Register ReadRegister();
		DecoderOptions ReadDecoderOptions();
		HandlerFlags ReadHandlerFlags();
		LegacyHandlerFlags ReadLegacyHandlerFlags();
		TupleType ReadTupleType();
		bool ReadBoolean();
		std::int32_t ReadInt32();
		std::shared_ptr<OpCodeHandler> ReadHandler();
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public OpCodeHandler? ReadHandlerOrNull()
		std::shared_ptr<OpCodeHandler> ReadHandlerOrNull();
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public OpCodeHandler?[] ReadHandlers(int count)
		std::vector<std::shared_ptr<OpCodeHandler>> ReadHandlers(std::int32_t count);
		std::shared_ptr<OpCodeHandler> ReadHandlerReference();
		std::vector<std::shared_ptr<OpCodeHandler>> ReadArrayReference(std::uint32_t kind);
		std::vector<std::shared_ptr<OpCodeHandler>> GetTable(std::uint32_t index);

		TableDeserializer() = default;
	};
}
