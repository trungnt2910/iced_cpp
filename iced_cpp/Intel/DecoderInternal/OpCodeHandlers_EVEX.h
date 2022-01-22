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
#include "../Register.g.h"
#include "../Code.g.h"
#include "../TupleType.g.h"
#include <vector>
#include <limits>
#include <stdexcept>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_VectorLength_EVEX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_VectorLength_EVEX(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256, std::shared_ptr<OpCodeHandler> handler512);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VectorLength_EVEX_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_VectorLength_EVEX_er(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256, std::shared_ptr<OpCodeHandler> handler512);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_V_H_Ev_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleTypeW0 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleTypeW1 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_V_H_Ev_er(Register baseReg, Code codeW0, Code codeW1, TupleType tupleTypeW0, TupleType tupleTypeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_V_H_Ev_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleTypeW0 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleTypeW1 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_V_H_Ev_Ib(Register baseReg, Code codeW0, Code codeW1, TupleType tupleTypeW0, TupleType tupleTypeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_Ed_V_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType32 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleType64 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_Ed_V_Ib(Register baseReg, Code code32, Code code64, TupleType tupleType32, TupleType tupleType64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHW_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool onlySAE = false;
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkHW_er(Register baseReg, Code code, TupleType tupleType, bool onlySAE, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHW_er_ur final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkHW_er_ur(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkW_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool onlySAE = false;
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkW_er(Register baseReg, Code code, TupleType tupleType, bool onlySAE);
		OpCodeHandler_EVEX_VkW_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool onlySAE);
		OpCodeHandler_EVEX_VkW_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool onlySAE, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkWIb_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VkWIb_er(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		OpCodeHandler_EVEX_VkW(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_WkV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		std::uint32_t disallowZeroingMasking = 0;
	public:
		OpCodeHandler_EVEX_WkV(Register baseReg, Code code, TupleType tupleType);
		OpCodeHandler_EVEX_WkV(Register baseReg, Code code, TupleType tupleType, bool allowZeroingMasking);
		OpCodeHandler_EVEX_WkV(Register baseReg1, Register baseReg2, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VkM(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_WkVIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_WkVIb(Register baseReg1, Register baseReg2, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_HkWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_HkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_HWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_HWIb(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_WkVIb_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_WkVIb_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VW_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VW_er(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VW(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_WV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_WV(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VM(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_EVEX_VK(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KR final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_EVEX_KR(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KkHWIb_sae final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_KkHWIb_sae(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Register baseReg3 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkHW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		OpCodeHandler_EVEX_VkHW(Register baseReg1, Register baseReg2, Register baseReg3, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VkHM(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Register baseReg3 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkHWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		OpCodeHandler_EVEX_VkHWIb(Register baseReg1, Register baseReg2, Register baseReg3, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkHWIb_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Register baseReg3 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_VkHWIb_er(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KkHW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_KkHW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KP1HW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_KP1HW(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KkHWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_KkHWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_WkHV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_EVEX_WkHV(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VHWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VHWIb(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VHW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Register baseReg3 = static_cast<Register>(0);
		/* readonly */
		Code codeR = static_cast<Code>(0);
		/* readonly */
		Code codeM = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VHW(Register baseReg, Code codeR, Code codeM, TupleType tupleType);
		OpCodeHandler_EVEX_VHW(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VHM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VHM(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_Gv_W_er final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool onlySAE = false;
	public:
		OpCodeHandler_EVEX_Gv_W_er(Register baseReg, Code codeW0, Code codeW1, TupleType tupleType, bool onlySAE);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VX_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleTypeW0 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleTypeW1 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VX_Ev(Code code32, Code code64, TupleType tupleTypeW0, TupleType tupleTypeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_Ev_VX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleTypeW0 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleTypeW1 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_Ev_VX(Code code32, Code code64, TupleType tupleTypeW0, TupleType tupleTypeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_Ev_VX_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_EVEX_Ev_VX_Ib(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_MV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_MV(Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VkEv_REXW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_EVEX_VkEv_REXW(Register baseReg, Code code32);
		OpCodeHandler_EVEX_VkEv_REXW(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_Vk_VSIB final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Register vsibBase = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_Vk_VSIB(Register baseReg, Register vsibBase, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VSIB_k1_VX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register vsibIndex = static_cast<Register>(0);
		/* readonly */
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VSIB_k1_VX(Register vsibIndex, Register baseReg, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_VSIB_k1 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register vsibIndex = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_VSIB_k1(Register vsibIndex, Code code, TupleType tupleType);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_GvM_VX_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType32 = static_cast<TupleType>(0);
		/* readonly */
		TupleType tupleType64 = static_cast<TupleType>(0);
	public:
		OpCodeHandler_EVEX_GvM_VX_Ib(Register baseReg, Code code32, Code code64, TupleType tupleType32, TupleType tupleType64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_EVEX_KkWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		bool canBroadcast = false;
	public:
		OpCodeHandler_EVEX_KkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
