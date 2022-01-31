// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "OpCodeHandlers.h"
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../Code.g.h"
#include "../Register.g.h"
#include "../Static.h"
#include "../VectorLength.g.h"
#include "../EncodingKind.g.h"
#include "../OpKind.g.h"
#include "../TupleType.g.h"
#include "../Iced.Intel.IcedConstants.h"
#include <array>
#include <stdexcept>
#include <cassert>

namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_VectorLength_VEX final : public OpCodeHandlerModRM
	{
	private:
		inline static constexpr std::size_t maxSize = 4;
		std::array<const OpCodeHandler*, maxSize> handlers;
	public:
		constexpr OpCodeHandler_VectorLength_VEX(const OpCodeHandler* handler128, const OpCodeHandler* handler256);
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& infos) override
		{
			for (const auto& [oldPtr, newPtr] : infos)
			{
				for (auto& ptr : handlers)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VectorLength_NoModRM_VEX final : public OpCodeHandler
	{
	private:
		inline static constexpr std::size_t maxSize = 4;
		std::array<const OpCodeHandler*, maxSize> handlers;
	public:
		constexpr OpCodeHandler_VectorLength_NoModRM_VEX(const OpCodeHandler* handler128, const OpCodeHandler* handler256);
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& infos) override
		{
			for (const auto& [oldPtr, newPtr] : infos)
			{
				for (auto& ptr : handlers)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Simple final : public OpCodeHandler
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Simple(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHEv final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code codeW0 = static_cast<Code>(0);
		Code codeW1 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHEv(Register baseReg, Code codeW0, Code codeW1);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHEvIb final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code codeW0 = static_cast<Code>(0);
		Code codeW1 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHEvIb(Register baseReg, Code codeW0, Code codeW1);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VW final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VW(Register baseReg, Code code);
		constexpr OpCodeHandler_VEX_VW(Register baseReg1, Register baseReg2, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VX_Ev final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VX_Ev(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Ev_VX final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Ev_VX(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_WV final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_WV(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VM final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VM(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_MV final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_MV(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_M final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_M(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_RdRq final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_RdRq(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_rDI_VX_RX final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_rDI_VX_RX(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VWIb final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Code codeW0 = static_cast<Code>(0);
		Code codeW1 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VWIb(Register baseReg, Code code);
		constexpr OpCodeHandler_VEX_VWIb(Register baseReg, Code codeW0, Code codeW1);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_WVIb final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_WVIb(Register baseReg1, Register baseReg2, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Ed_V_Ib final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Ed_V_Ib(Register baseReg, Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHW final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Register baseReg3 = static_cast<Register>(0);
		Code codeR = static_cast<Code>(0);
		Code codeM = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHW(Register baseReg, Code codeR, Code codeM);
		constexpr OpCodeHandler_VEX_VHW(Register baseReg, Code code);
		constexpr OpCodeHandler_VEX_VHW(Register baseReg1, Register baseReg2, Register baseReg3, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VWH final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VWH(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_WHV final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code codeR = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_WHV(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHM final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHM(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_MHV final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_MHV(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHWIb final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register baseReg2 = static_cast<Register>(0);
		Register baseReg3 = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHWIb(Register baseReg, Code code);
		constexpr OpCodeHandler_VEX_VHWIb(Register baseReg1, Register baseReg2, Register baseReg3, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_HRIb final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_HRIb(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHWIs4 final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHWIs4(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHIs4W final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHIs4W(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHWIs5 final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHWIs5(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VHIs5W final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VHIs5W(Register baseReg, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_HK_RK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_HK_RK(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_RK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_RK(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_RK_Ib final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_RK_Ib(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_WK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_WK(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_M_VK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_M_VK(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_R final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
		Register gpr = static_cast<Register>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_R(Code code, Register gpr);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_G_VK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
		Register gpr = static_cast<Register>(0);
	public:
		constexpr OpCodeHandler_VEX_G_VK(Code code, Register gpr);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_W final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code codeW0 = static_cast<Code>(0);
		Code codeW1 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_W(Register baseReg, Code codeW0, Code codeW1);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_RX final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_RX(Register baseReg, Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_GPR_Ib final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_GPR_Ib(Register baseReg, Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VX_VSIB_HX final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg1 = static_cast<Register>(0);
		Register vsibIndex = static_cast<Register>(0);
		Register baseReg3 = static_cast<Register>(0);
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VX_VSIB_HX(Register baseReg1, Register vsibIndex, Register baseReg3, Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_Gv_Ev final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_Gv_Ev(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Gv final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_Ev_Gv(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Hv_Ev final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Hv_Ev(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Hv_Ed_Id final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Hv_Ed_Id(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_GvM_VX_Ib final : public OpCodeHandlerModRM
	{
	private:
		Register baseReg = static_cast<Register>(0);
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_GvM_VX_Ib(Register baseReg, Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Ib final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_Ev_Ib(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_Ev_Id final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_Ev_Id(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VT_SIBMEM final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VT_SIBMEM(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_SIBMEM_VT final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_SIBMEM_VT(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VT final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VT(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VT_RT_HT final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_VT_RT_HT(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gq_HK_RK final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gq_HK_RK(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_VK_R_Ib final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
		Register gpr = static_cast<Register>(0);
	public:
		constexpr OpCodeHandler_VEX_VK_R_Ib(Code code, Register gpr);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_K_Jb final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_K_Jb(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_K_Jz final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_K_Jz(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Gv_Ev final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Gv_Ev(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_VEX_Ev final : public OpCodeHandlerModRM
	{
	private:
		Code code32 = static_cast<Code>(0);
		Code code64 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_VEX_Ev(Code code32, Code code64);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
}

namespace Iced::Intel::DecoderInternal
{
	constexpr OpCodeHandler_VectorLength_VEX::OpCodeHandler_VectorLength_VEX(const OpCodeHandler* handler128, const OpCodeHandler* handler256)
	{
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L512) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::Unknown) == 3 ? 0 : -1);
		handlers = 
		{ 
			(handler128 != nullptr) ? handler128 : throw std::invalid_argument("handler128"), 
			(handler256 != nullptr) ? handler256 : throw std::invalid_argument("handler256"), 
			&OpCodeHandler_Invalid_Instance, 
			&OpCodeHandler_Invalid_Instance
		};
		assert(handler128->HasModRM == HasModRM);
		assert(handler256->HasModRM == HasModRM);
	}

	inline void OpCodeHandler_VectorLength_VEX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::XOP);
		handlers[static_cast<std::int32_t>(decoder.state.vectorLength)]->Decode(decoder, instruction);
	}

	constexpr OpCodeHandler_VectorLength_NoModRM_VEX::OpCodeHandler_VectorLength_NoModRM_VEX(const OpCodeHandler* handler128, const OpCodeHandler* handler256)
	{
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L512) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::Unknown) == 3 ? 0 : -1);
		handlers = 
		{ 
			(handler128 != nullptr) ? handler128 : throw std::invalid_argument("handler128"), 
			(handler256 != nullptr) ? handler256 : throw std::invalid_argument("handler256"), 
			&OpCodeHandler_Invalid_Instance, 
			&OpCodeHandler_Invalid_Instance
		};
		assert(handler128->HasModRM == HasModRM);
		assert(handler256->HasModRM == HasModRM);
	}

	inline void OpCodeHandler_VectorLength_NoModRM_VEX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::XOP);
		handlers[static_cast<std::int32_t>(decoder.state.vectorLength)]->Decode(decoder, instruction);
	}

	constexpr OpCodeHandler_VEX_Simple::OpCodeHandler_VEX_Simple(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_Simple::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::XOP);
		if ((decoder.state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
	}

	constexpr OpCodeHandler_VEX_VHEv::OpCodeHandler_VEX_VHEv(Register baseReg, Code codeW0, Code codeW1)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	inline void OpCodeHandler_VEX_VHEv::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(codeW1);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(codeW0);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_VHEvIb::OpCodeHandler_VEX_VHEvIb(Register baseReg, Code codeW0, Code codeW1)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	inline void OpCodeHandler_VEX_VHEvIb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(codeW1);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(codeW0);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_VW::OpCodeHandler_VEX_VW(Register baseReg, Code code)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
	}

	constexpr OpCodeHandler_VEX_VW::OpCodeHandler_VEX_VW(Register baseReg1, Register baseReg2, Code code)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VW::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg2));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_VX_Ev::OpCodeHandler_VEX_VX_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_VX_Ev::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_Ev_VX::OpCodeHandler_VEX_Ev_VX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Ev_VX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
	}

	constexpr OpCodeHandler_VEX_WV::OpCodeHandler_VEX_WV(Register baseReg, Code code)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_WV::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg2));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg1));
	}

	constexpr OpCodeHandler_VEX_VM::OpCodeHandler_VEX_VM(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_MV::OpCodeHandler_VEX_MV(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_MV::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
	}

	constexpr OpCodeHandler_VEX_M::OpCodeHandler_VEX_M(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_M::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_RdRq::OpCodeHandler_VEX_RdRq(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_RdRq::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		if (state.mod != 3)
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_rDI_VX_RX::OpCodeHandler_VEX_rDI_VX_RX(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_rDI_VX_RX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemorySegRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemorySegEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemorySegDI);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_VWIb::OpCodeHandler_VEX_VWIb(Register baseReg, Code code)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		codeW0 = code;
		codeW1 = code;
	}

	constexpr OpCodeHandler_VEX_VWIb::OpCodeHandler_VEX_VWIb(Register baseReg, Code codeW0, Code codeW1)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	inline void OpCodeHandler_VEX_VWIb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(codeW1);
		}
		else
		{
			instruction.SetCode(codeW0);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg2));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_WVIb::OpCodeHandler_VEX_WVIb(Register baseReg1, Register baseReg2, Code code)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_WVIb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg1));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg2));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_Ed_V_Ib::OpCodeHandler_VEX_Ed_V_Ib(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Ed_V_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_VHW::OpCodeHandler_VEX_VHW(Register baseReg, Code codeR, Code codeM)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->codeR = codeR;
		this->codeM = codeM;
	}

	constexpr OpCodeHandler_VEX_VHW::OpCodeHandler_VEX_VHW(Register baseReg, Code code)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		codeR = code;
		codeM = code;
	}

	constexpr OpCodeHandler_VEX_VHW::OpCodeHandler_VEX_VHW(Register baseReg1, Register baseReg2, Register baseReg3, Code code)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->baseReg3 = baseReg3;
		codeR = code;
		codeM = code;
	}

	inline void OpCodeHandler_VEX_VHW::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			instruction.SetCode(codeR);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg3));
		}
		else
		{
			instruction.SetCode(codeM);
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_VWH::OpCodeHandler_VEX_VWH(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VWH::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
	}

	constexpr OpCodeHandler_VEX_WHV::OpCodeHandler_VEX_WHV(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		codeR = code;
	}

	inline void OpCodeHandler_VEX_WHV::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		assert(state.mod == 3);
		instruction.SetCode(codeR);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
	}

	constexpr OpCodeHandler_VEX_VHM::OpCodeHandler_VEX_VHM(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_MHV::OpCodeHandler_VEX_MHV(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_MHV::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
	}

	constexpr OpCodeHandler_VEX_VHWIb::OpCodeHandler_VEX_VHWIb(Register baseReg, Code code)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->code = code;
	}

	constexpr OpCodeHandler_VEX_VHWIb::OpCodeHandler_VEX_VHWIb(Register baseReg1, Register baseReg2, Register baseReg3, Code code)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->baseReg3 = baseReg3;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHWIb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg3));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_HRIb::OpCodeHandler_VEX_HRIb(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_HRIb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_VHWIs4::OpCodeHandler_VEX_VHWIs4(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHWIs4::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register((Register)(static_cast<std::int32_t>((decoder.ReadByte() >> 4) & decoder.reg15Mask) + baseReg));
	}

	constexpr OpCodeHandler_VEX_VHIs4W::OpCodeHandler_VEX_VHIs4W(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHIs4W::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op3Kind = OpKind.Register;
			instruction.SetOp3Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp3Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>((decoder.ReadByte() >> 4) & decoder.reg15Mask) + baseReg));
	}

	constexpr OpCodeHandler_VEX_VHWIs5::OpCodeHandler_VEX_VHWIs5(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHWIs5::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		std::uint32_t ib = decoder.ReadByte();
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register((Register)(static_cast<std::int32_t>((ib >> 4) & decoder.reg15Mask) + baseReg));
		assert(instruction.GetOp4Kind() == OpKind::Immediate8); // It's hard coded
		instruction.SetInternalImmediate8(ib & 0xF);
	}

	constexpr OpCodeHandler_VEX_VHIs5W::OpCodeHandler_VEX_VHIs5W(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VHIs5W::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op3Kind = OpKind.Register;
			instruction.SetOp3Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp3Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		std::uint32_t ib = decoder.ReadByte();
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>((ib >> 4) & decoder.reg15Mask) + baseReg));
		assert(instruction.GetOp4Kind() == OpKind::Immediate8); // It's hard coded
		instruction.SetInternalImmediate8(ib & 0xF);
	}

	constexpr OpCodeHandler_VEX_VK_HK_RK::OpCodeHandler_VEX_VK_HK_RK(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VK_HK_RK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (decoder.invalidCheckMask != 0 && (state.vvvv > 7 || state.extraRegisterBase != 0))
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv & 7) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_VK_RK::OpCodeHandler_VEX_VK_RK(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VK_RK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_VK_RK_Ib::OpCodeHandler_VEX_VK_RK_Ib(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VK_RK_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_VK_WK::OpCodeHandler_VEX_VK_WK(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VK_WK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_M_VK::OpCodeHandler_VEX_M_VK(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_M_VK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
	}

	constexpr OpCodeHandler_VEX_VK_R::OpCodeHandler_VEX_VK_R(Code code, Register gpr)
	{
		this->code = code;
		this->gpr = gpr;
	}

	inline void OpCodeHandler_VEX_VK_R::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_G_VK::OpCodeHandler_VEX_G_VK(Code code, Register gpr)
	{
		this->code = code;
		this->gpr = gpr;
	}

	inline void OpCodeHandler_VEX_G_VK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_Gv_W::OpCodeHandler_VEX_Gv_W(Register baseReg, Code codeW0, Code codeW1)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	inline void OpCodeHandler_VEX_Gv_W::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(codeW1);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(codeW0);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_Gv_RX::OpCodeHandler_VEX_Gv_RX(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_RX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_Gv_GPR_Ib::OpCodeHandler_VEX_Gv_GPR_Ib(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_GPR_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_VX_VSIB_HX::OpCodeHandler_VEX_VX_VSIB_HX(Register baseReg1, Register vsibIndex, Register baseReg3, Code code)
	{
		this->baseReg1 = baseReg1;
		this->vsibIndex = vsibIndex;
		this->baseReg3 = baseReg3;
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VX_VSIB_HX::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		instruction.SetCode(code);
		std::int32_t regNum = static_cast<std::int32_t>(state.reg + state.extraRegisterBase);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(regNum + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg3));
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem_VSIB(instruction, vsibIndex, TupleType::N1);
			if (decoder.invalidCheckMask != 0)
			{
				std::uint32_t indexNum = (static_cast<std::uint32_t>(instruction.GetMemoryIndex() - Register::XMM0) % static_cast<std::uint32_t>(IcedConstants::VMM_count));
				if (static_cast<std::uint32_t>(regNum) == indexNum || state.vvvv == indexNum || static_cast<std::uint32_t>(regNum) == state.vvvv)
				{
					decoder.SetInvalidInstruction();
				}
			}
		}
	}

	constexpr OpCodeHandler_VEX_Gv_Gv_Ev::OpCodeHandler_VEX_Gv_Gv_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_Gv_Ev::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_Gv_Ev_Gv::OpCodeHandler_VEX_Gv_Ev_Gv(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_Ev_Gv::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.vvvv) + gpr));
	}

	constexpr OpCodeHandler_VEX_Hv_Ev::OpCodeHandler_VEX_Hv_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Hv_Ev::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_Hv_Ed_Id::OpCodeHandler_VEX_Hv_Ed_Id(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Hv_Ed_Id::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate32);
		instruction.SetImmediate32(decoder.ReadUInt32());
	}

	constexpr OpCodeHandler_VEX_GvM_VX_Ib::OpCodeHandler_VEX_GvM_VX_Ib(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_GvM_VX_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_Gv_Ev_Ib::OpCodeHandler_VEX_Gv_Ev_Ib(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_Ev_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_Gv_Ev_Id::OpCodeHandler_VEX_Gv_Ev_Id(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_Ev_Id::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate32);
		instruction.SetImmediate32(decoder.ReadUInt32());
	}

	constexpr OpCodeHandler_VEX_VT_SIBMEM::OpCodeHandler_VEX_VT_SIBMEM(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VT_SIBMEM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::TMM0));
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMemSib(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_SIBMEM_VT::OpCodeHandler_VEX_SIBMEM_VT(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_SIBMEM_VT::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::TMM0));
		if (state.mod == 3)
		{
			decoder.SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMemSib(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_VT::OpCodeHandler_VEX_VT(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VT::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::TMM0));
	}

	constexpr OpCodeHandler_VEX_VT_RT_HT::OpCodeHandler_VEX_VT_RT_HT(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_VT_RT_HT::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (decoder.invalidCheckMask != 0 && (state.vvvv > 7 || state.extraRegisterBase != 0))
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::TMM0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.vvvv & 7) + Register::TMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::TMM0));
			if (decoder.invalidCheckMask != 0)
			{
				if (state.extraBaseRegisterBase != 0 || state.reg == state.vvvv || state.reg == state.rm || state.rm == state.vvvv)
				{
					decoder.SetInvalidInstruction();
				}
			}
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_Gq_HK_RK::OpCodeHandler_VEX_Gq_HK_RK(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_Gq_HK_RK::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (decoder.invalidCheckMask != 0 && state.vvvv > 7)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv & 7) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
	}

	constexpr OpCodeHandler_VEX_VK_R_Ib::OpCodeHandler_VEX_VK_R_Ib(Code code, Register gpr)
	{
		this->code = code;
		this->gpr = gpr;
	}

	inline void OpCodeHandler_VEX_VK_R_Ib::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (((state.vvvv_invalidCheck | state.extraRegisterBase) & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			decoder.SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder.ReadByte());
	}

	constexpr OpCodeHandler_VEX_K_Jb::OpCodeHandler_VEX_K_Jb(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_K_Jb::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		state.flags |= StateFlags::BranchImm8;
		if (decoder.invalidCheckMask != 0 && state.vvvv > 7)
		{
			decoder.SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv & 7) + Register::K0));
		assert(decoder.is64bMode);
		instruction.SetCode(code);
		instruction.SetOp1Kind(OpKind::NearBranch64);
		// The modrm byte has the imm8 value
		instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int8_t>(state.modrm)) + decoder.GetCurrentInstructionPointer64());
	}

	constexpr OpCodeHandler_VEX_K_Jz::OpCodeHandler_VEX_K_Jz(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_VEX_K_Jz::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if (decoder.invalidCheckMask != 0 && state.vvvv > 7)
		{
			decoder.SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv & 7) + Register::K0));
		assert(decoder.is64bMode);
		instruction.SetCode(code);
		instruction.SetOp1Kind(OpKind::NearBranch64);
		// The modrm byte has the low 8 bits of imm32
		std::uint32_t imm = state.modrm | (decoder.ReadByte() << 8) | (decoder.ReadByte() << 16) | (decoder.ReadByte() << 24);
		instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int32_t>(imm)) + decoder.GetCurrentInstructionPointer64());
	}

	constexpr OpCodeHandler_VEX_Gv_Ev::OpCodeHandler_VEX_Gv_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Gv_Ev::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + gpr));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}

	constexpr OpCodeHandler_VEX_Ev::OpCodeHandler_VEX_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	inline void OpCodeHandler_VEX_Ev::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::VEX || state.GetEncoding() == EncodingKind::XOP);
		if ((state.vvvv_invalidCheck & decoder.invalidCheckMask) != 0)
		{
			decoder.SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((std::uint32_t)state.flags & decoder.is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			gpr = Register::EAX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder.ReadOpMem(instruction);
		}
	}
}