// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "TableDeserializer.h"
#include "OpCodeHandlers.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class VexOpCodeHandlerReader final : public OpCodeHandlerReader
	{
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
		std::int32_t ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex) override;
	};
}
