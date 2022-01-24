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

#include "OpCodeHandlers.h"
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../Code.g.h"
#include "../Register.g.h"
#include <vector>
#include <stdexcept>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_VectorLength_VEX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_VectorLength_VEX(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VectorLength_NoModRM_VEX final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_VectorLength_NoModRM_VEX(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Simple final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Simple(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHEv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHEv(Register baseReg, Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHEvIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHEvIb(Register baseReg, Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VW final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VW(Register baseReg, Code code);
		OpCodeHandler_VEX_VW(Register baseReg1, Register baseReg2, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VX_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VX_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Ev_VX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Ev_VX(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_WV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_WV(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VM(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_MV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_MV(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_M final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_M(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_RdRq final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_RdRq(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_rDI_VX_RX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_rDI_VX_RX(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VWIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VWIb(Register baseReg, Code code);
		OpCodeHandler_VEX_VWIb(Register baseReg, Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_WVIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register baseReg2 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_WVIb(Register baseReg1, Register baseReg2, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Ed_V_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Ed_V_Ib(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHW final : public OpCodeHandlerModRM
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
	public:
		OpCodeHandler_VEX_VHW(Register baseReg, Code codeR, Code codeM);
		OpCodeHandler_VEX_VHW(Register baseReg, Code code);
		OpCodeHandler_VEX_VHW(Register baseReg1, Register baseReg2, Register baseReg3, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VWH final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VWH(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_WHV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeR = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_WHV(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHM(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_MHV final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_MHV(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHWIb final : public OpCodeHandlerModRM
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
	public:
		OpCodeHandler_VEX_VHWIb(Register baseReg, Code code);
		OpCodeHandler_VEX_VHWIb(Register baseReg1, Register baseReg2, Register baseReg3, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_HRIb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_HRIb(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHWIs4 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHWIs4(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHIs4W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHIs4W(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHWIs5 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHWIs5(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VHIs5W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VHIs5W(Register baseReg, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_HK_RK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VK_HK_RK(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_RK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VK_RK(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_RK_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VK_RK_Ib(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_WK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VK_WK(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_M_VK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_M_VK(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_R final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register gpr = static_cast<Register>(0);
	public:
		OpCodeHandler_VEX_VK_R(Code code, Register gpr);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_G_VK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register gpr = static_cast<Register>(0);
	public:
		OpCodeHandler_VEX_G_VK(Code code, Register gpr);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code codeW0 = static_cast<Code>(0);
		/* readonly */
		Code codeW1 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_W(Register baseReg, Code codeW0, Code codeW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_RX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_RX(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_GPR_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_GPR_Ib(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VX_VSIB_HX final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg1 = static_cast<Register>(0);
		/* readonly */
		Register vsibIndex = static_cast<Register>(0);
		/* readonly */
		Register baseReg3 = static_cast<Register>(0);
		/* readonly */
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VX_VSIB_HX(Register baseReg1, Register vsibIndex, Register baseReg3, Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_Gv_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_Gv_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Gv final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_Ev_Gv(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Hv_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Hv_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Hv_Ed_Id final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Hv_Ed_Id(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_GvM_VX_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Register baseReg = static_cast<Register>(0);
		/* readonly */
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_GvM_VX_Ib(Register baseReg, Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_Ev_Ib(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Id final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_Ev_Id(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VT_SIBMEM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VT_SIBMEM(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_SIBMEM_VT final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_SIBMEM_VT(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VT final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VT(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VT_RT_HT final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_VT_RT_HT(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gq_HK_RK final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gq_HK_RK(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_VK_R_Ib final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
		/* readonly */
		Register gpr = static_cast<Register>(0);
	public:
		OpCodeHandler_VEX_VK_R_Ib(Code code, Register gpr);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_K_Jb final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_K_Jb(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_K_Jz final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_K_Jz(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Gv_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Gv_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_VEX_Ev final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code32 = static_cast<Code>(0);
		/* readonly */
		Code code64 = static_cast<Code>(0);
	public:
		OpCodeHandler_VEX_Ev(Code code32, Code code64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
