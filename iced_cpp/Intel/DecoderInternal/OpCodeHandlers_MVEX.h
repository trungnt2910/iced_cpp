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
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../Code.g.h"
#include <stdexcept>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_EH final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerEH0;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handlerEH1;
	public:
		OpCodeHandler_EH(std::shared_ptr<OpCodeHandler> handlerEH0, std::shared_ptr<OpCodeHandler> handlerEH1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_M final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_M(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_MV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_MV(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VW(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_HWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_HWIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VWIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VHW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VHW(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VHWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VHWIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VKW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VKW(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_KHW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_KHW(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_KHWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_KHWIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VSIB final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VSIB(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_VSIB_V final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_VSIB_V(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MVEX_V_VSIB final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MVEX_V_VSIB(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
