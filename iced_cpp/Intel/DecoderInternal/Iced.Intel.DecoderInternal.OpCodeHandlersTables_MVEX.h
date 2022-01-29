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

#include "OpCodeHandlers.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandlersTables_MVEX final
	{
	public:
		static std::vector<std::shared_ptr<OpCodeHandler>> Handlers_0F;
		static std::vector<std::shared_ptr<OpCodeHandler>> Handlers_0F38;
		static std::vector<std::shared_ptr<OpCodeHandler>> Handlers_0F3A;
	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static OpCodeHandlersTables_MVEX::StaticConstructor staticConstructor;



		static std::vector<std::uint8_t> GetSerializedTables();
		static constexpr std::int32_t MaxIdNames = 7;
		static constexpr std::uint32_t Handlers_0FIndex = 6;
		static constexpr std::uint32_t Handlers_0F38Index = 4;
		static constexpr std::uint32_t Handlers_0F3AIndex = 5;
	};
}
