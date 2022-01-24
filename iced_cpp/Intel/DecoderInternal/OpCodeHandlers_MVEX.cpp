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

#include "OpCodeHandlers_MVEX.h"
#include "../EncodingKind.g.h"
#include "../MvexInfo.h"
#include "../Register.g.h"
#include "../OpKind.g.h"
#include "../MvexRegMemConv.g.h"
#include "../Static.h"
#include "../RoundingControl.g.h"
#include "../Iced.Intel.IcedConstants.h"

namespace Iced::Intel::DecoderInternal
{

	OpCodeHandler_EH::OpCodeHandler_EH(std::shared_ptr<OpCodeHandler> handlerEH0, std::shared_ptr<OpCodeHandler> handlerEH1)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerEH0 = handlerEH0 ?? throw new ArgumentNullException(nameof(handlerEH0));
		this->handlerEH0 = (handlerEH0 != nullptr) ? handlerEH0 : throw std::invalid_argument("handlerEH0");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerEH1 = handlerEH1 ?? throw new ArgumentNullException(nameof(handlerEH1));
		this->handlerEH1 = (handlerEH1 != nullptr) ? handlerEH1 : throw std::invalid_argument("handlerEH1");
		assert(handlerEH0->HasModRM == HasModRM);
		assert(handlerEH1->HasModRM == HasModRM);
	}

	void OpCodeHandler_EH::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::MVEX);
		((decoder->state.flags & StateFlags::MvexEH) != 0 ? handlerEH1 : handlerEH0)->Decode(decoder, instruction);
	}

	OpCodeHandler_MVEX_M::OpCodeHandler_MVEX_M(Code code)
	{
		assert((MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert(!(MvexInfo(code)).GetCanUseEvictionHint());
		assert((MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_M::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOpMask(Register::None); // It's ignored (see ctor)
		instruction.SetCode(code);
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss)));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_MV::OpCodeHandler_MVEX_MV(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		this->code = code;
	}

	void OpCodeHandler_MVEX_MV::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if (mvex.GetCanUseEvictionHint() && (state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
	}

	OpCodeHandler_MVEX_VW::OpCodeHandler_MVEX_VW(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_HWIb::OpCodeHandler_MVEX_HWIb(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_HWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0)));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetImmediate8(static_cast<std::uint8_t>(decoder->ReadByte()));
	}

	OpCodeHandler_MVEX_VWIb::OpCodeHandler_MVEX_VWIb(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0)));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0)));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetImmediate8(static_cast<std::uint8_t>(decoder->ReadByte()));
	}

	OpCodeHandler_MVEX_VHW::OpCodeHandler_MVEX_VHW(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VHW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		if (mvex.GetRequireOpMaskRegister() && decoder->invalidCheckMask != 0 && state.aaa == 0)
		{
			decoder->SetInvalidInstruction();
		}
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_VHWIb::OpCodeHandler_MVEX_VHWIb(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VHWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetImmediate8(static_cast<std::uint8_t>(decoder->ReadByte()));
	}

	OpCodeHandler_MVEX_VKW::OpCodeHandler_MVEX_VKW(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VKW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if ((state.vvvv & decoder->invalidCheckMask) > 7)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_KHW::OpCodeHandler_MVEX_KHW(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_KHW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		if (((state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_MVEX_KHWIb::OpCodeHandler_MVEX_KHWIb(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_KHWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + Register::ZMM0));
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				if (mvex.GetCanUseSuppressAllExceptions())
				{
					if ((sss & 4) != 0)
					{
						instruction.InternalSetSuppressAllExceptions();
					}
					if (mvex.GetCanUseRoundingControl())
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						instruction.SetInternalRoundingControl((static_cast<std::uint32_t>(sss) & 3) + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
					}
				}
				else if (mvex.GetNoSaeRc() && (static_cast<std::uint32_t>(sss & decoder->invalidCheckMask)) != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				if ((mvex.GetInvalidSwizzleFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
				{
					decoder->SetInvalidInstruction();
				}
				assert(static_cast<std::uint32_t>(sss) <= 7);
				instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::RegSwizzleNone + sss));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem(instruction, mvex.GetTupleType(sss));
		}
		if (((state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetImmediate8(static_cast<std::uint8_t>(decoder->ReadByte()));
	}

	OpCodeHandler_MVEX_VSIB::OpCodeHandler_MVEX_VSIB(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VSIB::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if (decoder->invalidCheckMask != 0 && ((state.vvvv_invalidCheck & 0xF) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem_VSIB(instruction, Register::ZMM0, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_VSIB_V::OpCodeHandler_MVEX_VSIB_V(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_VSIB_V::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if (decoder->invalidCheckMask != 0 && ((state.vvvv_invalidCheck & 0xF) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem_VSIB(instruction, Register::ZMM0, mvex.GetTupleType(sss));
		}
	}

	OpCodeHandler_MVEX_V_VSIB::OpCodeHandler_MVEX_V_VSIB(Code code)
	{
		assert(!(MvexInfo(code)).GetIgnoresOpMaskRegister());
		assert((MvexInfo(code)).GetCanUseEvictionHint());
		assert(!(MvexInfo(code)).GetIgnoresEvictionHint());
		this->code = code;
	}

	void OpCodeHandler_MVEX_V_VSIB::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::MVEX);
		if (decoder->invalidCheckMask != 0 && ((state.vvvv_invalidCheck & 0xF) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		std::int32_t regNum = static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(regNum + Register::ZMM0));
		auto mvex = MvexInfo(code);
		auto sss = state.GetSss();
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::MvexEH) != 0)
			{
				instruction.InternalSetIsMvexEvictionHint();
			}
			if ((mvex.GetInvalidConvFns() & (1U << sss) & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			instruction.InternalSetMvexRegMemConv((MvexRegMemConv)(MvexRegMemConv::MemConvNone + sss));
			decoder->ReadOpMem_VSIB(instruction, Register::ZMM0, mvex.GetTupleType(sss));
			if (decoder->invalidCheckMask != 0)
			{
				if (static_cast<std::uint32_t>(regNum) == (static_cast<std::uint32_t>(instruction.GetMemoryIndex() - Register::XMM0) % static_cast<std::uint32_t>(IcedConstants::VMM_count)))
				{
					decoder->SetInvalidInstruction();
				}
			}
		}
	}
}
