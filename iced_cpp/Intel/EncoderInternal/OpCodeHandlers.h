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

#pragma once

#include "EncoderOpCodeHandler.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	class OpCodeHandlers final
	{
	public:
		static std::vector<std::shared_ptr<OpCodeHandler>> Handlers;
	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static OpCodeHandlers::StaticConstructor staticConstructor;

	};
}
