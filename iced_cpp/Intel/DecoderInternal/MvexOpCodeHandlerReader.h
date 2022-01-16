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

#pragma once

#include "TableDeserializer.h"
#include "OpCodeHandlers.h"
#include <vector>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class MvexOpCodeHandlerReader final : public OpCodeHandlerReader
	{
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
		std::int32_t ReadHandlers(TableDeserializer& deserializer, std::vector<OpCodeHandler*>& result, std::int32_t resultIndex) override;
	};
}
