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
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../Register.g.h"
#include "../Code.g.h"
#include "LegacyHandlerFlags.g.h"
#include "HandlerFlags.g.h"
#include <array>
#include <vector>
#include <limits>
#include <stdexcept>
#include <cassert>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel::DecoderInternal { class Info; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_VEX2 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerMem;
	public:
		OpCodeHandler_VEX2(std::shared_ptr<OpCodeHandler> handlerMem);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX3 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerMem;
	public:
		OpCodeHandler_VEX3(std::shared_ptr<OpCodeHandler> handlerMem);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_XOP final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handler_reg0;
	public:
		OpCodeHandler_XOP(std::shared_ptr<OpCodeHandler> handler_reg0);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerMem;
	public:
		OpCodeHandler_EVEX(std::shared_ptr<OpCodeHandler> handlerMem);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixEsCsSsDs final : public OpCodeHandler
	{
		/* readonly */
	private:
		Register seg = static_cast<Register>(0);
	public:
		OpCodeHandler_PrefixEsCsSsDs(Register seg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixFsGs final : public OpCodeHandler
	{
		/* readonly */
	private:
		Register seg = static_cast<Register>(0);
	public:
		OpCodeHandler_PrefixFsGs(Register seg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Prefix66 final : public OpCodeHandler
	{
	public:
		OpCodeHandler_Prefix66();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Prefix67 final : public OpCodeHandler
	{
	public:
		OpCodeHandler_Prefix67();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixF0 final : public OpCodeHandler
	{
	public:
		OpCodeHandler_PrefixF0();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixF2 final : public OpCodeHandler
	{
	public:
		OpCodeHandler_PrefixF2();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixF3 final : public OpCodeHandler
	{
	public:
		OpCodeHandler_PrefixF3();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PrefixREX final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handler;
		/* readonly */
		std::uint32_t rex = 0;
	public:
		OpCodeHandler_PrefixREX(std::shared_ptr<OpCodeHandler> handler, std::uint32_t rex);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Reg(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RegIb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_RegIb(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_IbReg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_IbReg(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_AL_DX final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_AL_DX(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_DX_AL final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_DX_AL(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ib final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Ib(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ib3 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Ib3(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_MandatoryPrefix(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix3 final : public OpCodeHandlerModRM
	{
	private:
		class Info
		{
		public:
			std::shared_ptr<OpCodeHandler> handler;
			bool mandatoryPrefix = false;
			Info(std::shared_ptr<OpCodeHandler> handler, bool mandatoryPrefix);

			Info() = default;
		};
		/* readonly */
	private:
		std::vector<Info> handlers_reg;
		/* readonly */
		std::vector<Info> handlers_mem;
		/* readonly */
	public:
		OpCodeHandler_MandatoryPrefix3(std::shared_ptr<OpCodeHandler> handler_reg, std::shared_ptr<OpCodeHandler> handler_mem, std::shared_ptr<OpCodeHandler> handler66_reg, std::shared_ptr<OpCodeHandler> handler66_mem, std::shared_ptr<OpCodeHandler> handlerF3_reg, std::shared_ptr<OpCodeHandler> handlerF3_mem, std::shared_ptr<OpCodeHandler> handlerF2_reg, std::shared_ptr<OpCodeHandler> handlerF2_mem, LegacyHandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix4 final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerNP;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handler66;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handlerF3;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handlerF2;
		/* readonly */
		std::uint32_t flags = 0;
	public:
		OpCodeHandler_MandatoryPrefix4(std::shared_ptr<OpCodeHandler> handlerNP, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2, std::uint32_t flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix_NoModRM final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_MandatoryPrefix_NoModRM(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_NIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_NIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reservednop final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> reservedNopHandler;
		/* readonly */
		std::shared_ptr<OpCodeHandler> otherHandler;
	public:
		OpCodeHandler_Reservednop(std::shared_ptr<OpCodeHandler> reservedNopHandler, std::shared_ptr<OpCodeHandler> otherHandler);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Iz final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Ev_Iz(Code code16, Code code32, Code code64);
		OpCodeHandler_Ev_Iz(Code code16, Code code32, Code code64, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Ev_Ib(Code code16, Code code32, Code code64);
		OpCodeHandler_Ev_Ib(Code code16, Code code32, Code code64, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Ib2 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Ev_Ib2(Code code16, Code code32, Code code64);
		OpCodeHandler_Ev_Ib2(Code code16, Code code32, Code code64, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_1 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_1(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_CL final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_CL(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Ev(Code code16, Code code32, Code code64);
		OpCodeHandler_Ev(Code code16, Code code32, Code code64, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Rv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Rv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Rv_32_64 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Rv_32_64(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Rq final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Rq(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_REXW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		std::uint32_t flags = 0;
		/* readonly */
		std::uint32_t disallowReg = 0;
		/* readonly */
		std::uint32_t disallowMem = 0;
	public:
		OpCodeHandler_Ev_REXW(Code code32, Code code64, std::uint32_t flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Evj final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Evj(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ep final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ep(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Evw final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Evw(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ew final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ew(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ms final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ms(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gd_Rd final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Gd_Rd(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_M_as final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_M_as(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gdq_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gdq_Ev(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev3 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev3(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev2 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev2(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_R_C final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		Register baseReg = static_cast<Register>(0);
	public:
		OpCodeHandler_R_C(Code code32, Code code64, Register baseReg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_C_R final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		Register baseReg = static_cast<Register>(0);
	public:
		OpCodeHandler_C_R(Code code32, Code code64, Register baseReg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Jb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Jb(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Jx final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Jx(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Jz final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Jz(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Jb2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16_16 = static_cast<Code>(0);
		/* readonly */
		Code code16_32 = static_cast<Code>(0);
		/* readonly */
		Code code16_64 = static_cast<Code>(0);
		/* readonly */
		Code code32_16 = static_cast<Code>(0);
		/* readonly */
		Code code32_32 = static_cast<Code>(0);
		/* readonly */
		Code code64_32 = static_cast<Code>(0);
		/* readonly */
		Code code64_64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Jb2(Code code16_16, Code code16_32, Code code16_64, Code code32_16, Code code32_32, Code code64_32, Code code64_64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Jdisp final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Jdisp(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushOpSizeReg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_PushOpSizeReg(Code code16, Code code32, Code code64, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushEv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_PushEv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Gv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Ev_Gv(Code code16, Code code32, Code code64);
		OpCodeHandler_Ev_Gv(Code code16, Code code32, Code code64, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Gv_32_64 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_Gv_32_64(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Gv_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_Gv_Ib(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Gv_CL final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_Gv_CL(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Mp final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Mp(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Eb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Eb(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ew final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ew(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushSimple2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_PushSimple2(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple2(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple2Iw final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple2Iw(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple3 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple3(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple5 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple5(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple5_ModRM_as final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple5_ModRM_as(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple4 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple4(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushSimpleReg final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::int32_t index = 0;
		/* readonly */
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_PushSimpleReg(std::int32_t index, Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_SimpleReg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		std::int32_t index = 0;
	public:
		OpCodeHandler_SimpleReg(Code code, std::int32_t index);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Xchg_Reg_rAX final : public OpCodeHandler
	{
	private:
		inline constexpr static std::array s_codes = std::to_array<Code>({ Code::Nopw, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Xchg_r16_AX, Code::Nopd, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Xchg_r32_EAX, Code::Nopq, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX, Code::Xchg_r64_RAX });
		/* readonly */
	private:
		std::int32_t index = 0;
		/* readonly */
		const decltype(s_codes)& codes = s_codes;
	public:
		OpCodeHandler_Xchg_Reg_rAX(std::int32_t index);
	public:
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Iz final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Iz(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RegIb3 final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::int32_t index = 0;
		/* readonly */
		std::vector<Register> withRexPrefix;
	public:
		OpCodeHandler_RegIb3(std::int32_t index);
	private:
		static std::vector<Register> s_withRexPrefix;
	public:
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RegIz2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::int32_t index = 0;
	public:
		OpCodeHandler_RegIz2(std::int32_t index);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushIb2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_PushIb2(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_PushIz final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_PushIz(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ma final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ma(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RvMw_Gw final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_RvMw_Gw(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev_Ib(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev_Ib_REX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev_Ib_REX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev_32_64 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		std::uint32_t disallowReg = 0;
		/* readonly */
		std::uint32_t disallowMem = 0;
	public:
		OpCodeHandler_Gv_Ev_32_64(Code code32, Code code64, bool allowReg, bool allowMem);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev_Iz final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev_Iz(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Yb_Reg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Yb_Reg(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Yv_Reg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Yv_Reg(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Yv_Reg2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Yv_Reg2(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Xb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Reg_Xb(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Xv final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Xv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Xv2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Xv2(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Yb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Reg_Yb(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Yv final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Yv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Yb_Xb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Yb_Xb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Yv_Xv final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Yv_Xv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Xb_Yb final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Xb_Yb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Xv_Yv final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Xv_Yv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Sw final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_Sw(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_M_Sw final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_M_Sw(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_M final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_M(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Sw_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Sw_Ev(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Sw_M final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Sw_M(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ap final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ap(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Ob final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Reg_Ob(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ob_Reg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register reg = static_cast<Register>(0);
	public:
		OpCodeHandler_Ob_Reg(Code code, Register reg);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Ov final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Ov(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ov_Reg final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ov_Reg(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_BranchIw final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_BranchIw(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_BranchSimple final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_BranchSimple(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Iw_Ib final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Iw_Ib(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Reg_Ib2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_Reg_Ib2(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_IbReg2 final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_IbReg2(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_eAX_DX final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_eAX_DX(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_DX_eAX final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
	public:
		OpCodeHandler_DX_eAX(Code code16, Code code32);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Eb_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Eb_Ib(Code code);
		OpCodeHandler_Eb_Ib(Code code, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Eb_1 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Eb_1(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Eb_CL final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Eb_CL(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Eb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Eb(Code code);
		OpCodeHandler_Eb(Code code, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Eb_Gb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_Eb_Gb(Code code);
		OpCodeHandler_Eb_Gb(Code code, HandlerFlags flags);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gb_Eb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Gb_Eb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_M final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_M(Code codeW0, Code codeW1);
		OpCodeHandler_M(Code codeW0);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_M_REXW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		HandlerFlags flags32 = static_cast<HandlerFlags>(0);
		/* readonly */
		HandlerFlags flags64 = static_cast<HandlerFlags>(0);
	public:
		OpCodeHandler_M_REXW(Code code32, Code code64);
		OpCodeHandler_M_REXW(Code code32, Code code64, HandlerFlags flags32, HandlerFlags flags64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MemBx final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MemBx(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code codeR = static_cast<Code>(0);
		/* readonly */
		Code codeM = static_cast<Code>(0);
	public:
		OpCodeHandler_VW(Code codeR, Code codeM);
		OpCodeHandler_VW(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_WV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_WV(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_rDI_VX_RX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_rDI_VX_RX(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_rDI_P_N final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_rDI_P_N(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VM(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MV(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VQ final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VQ(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_Q final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_P_Q(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Q_P final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Q_P(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MP final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MP(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_Q_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_P_Q_Ib(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_P_W(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_R final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_P_R(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_P_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_P_Ev_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_P_Ev_Ib(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_P final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_P(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_W(Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_V_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_V_Ev(Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_VWIb(Code code);
		OpCodeHandler_VWIb(Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VRIbIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VRIbIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RIbIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_RIbIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_RIb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ed_V_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ed_V_Ib(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VX_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VX_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_VX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_VX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VX_E_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VX_E_Ib(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_RX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_RX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_B_MIB final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_B_MIB(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MIB_B final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_MIB_B(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_B_BM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_B_BM(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_BM_B final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_BM_B(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_B_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		std::uint32_t ripRelMask = 0;
	public:
		OpCodeHandler_B_Ev(Code code32, Code code64, bool supportsRipRel);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Mv_Gv_REXW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Mv_Gv_REXW(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_N_Ib_REX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_N_Ib_REX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_N final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_N(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VN final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VN(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Mv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Mv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Mv_Gv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code16 = static_cast<Code>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Mv_Gv(Code code16, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Eb_REX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Eb_REX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Gv_Ev_REX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Gv_Ev_REX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Ev_Gv_REX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_Ev_Gv_REX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_GvM_VX_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_GvM_VX_Ib(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Wbinvd final : public OpCodeHandler
	{
	public:
		OpCodeHandler_Wbinvd();
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
