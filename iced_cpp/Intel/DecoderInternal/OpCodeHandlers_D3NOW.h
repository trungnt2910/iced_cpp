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
#include "../Code.g.h"
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include <vector>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_D3NOW final : public OpCodeHandlerModRM
	{
	public:
		static std::vector<Code> CodeValues;
	private:
		static std::vector<Code> CreateCodeValues();
		/* readonly */
		std::vector<Code> codeValues = CodeValues;
	public:
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
