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

#include "OpCodeHandlers_EVEX.h"
#include "../Static.h"
#include "../VectorLength.g.h"
#include "../EncodingKind.g.h"
#include "../OpKind.g.h"
#include "../RoundingControl.g.h"
#include "../Iced.Intel.IcedConstants.h"

namespace Iced::Intel::DecoderInternal
{

	OpCodeHandler_VectorLength_EVEX::OpCodeHandler_VectorLength_EVEX(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256, std::shared_ptr<OpCodeHandler> handler512)
	{
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L512) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::Unknown) == 3 ? 0 : -1);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers = std::make_shared<OpCodeHandler>[4] { handler128 ?? throw new ArgumentNullException(nameof(handler128)), handler256 ?? throw new ArgumentNullException(nameof(handler256)), handler512 ?? throw new ArgumentNullException(nameof(handler512)), OpCodeHandler_Invalid.Instance};
		handlers = { (handler128 != nullptr) ? handler128 : throw std::invalid_argument("handler128"), (handler256 != nullptr) ? handler256 : throw std::invalid_argument("handler256"), (handler512 != nullptr) ? handler512 : throw std::invalid_argument("handler512"), OpCodeHandler_Invalid::Instance };
		assert(handler128->HasModRM == HasModRM);
		assert(handler256->HasModRM == HasModRM);
		assert(handler512->HasModRM == HasModRM);
	}

	void OpCodeHandler_VectorLength_EVEX::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::EVEX);
		handlers[static_cast<std::int32_t>(decoder->state.vectorLength)]->Decode(decoder, instruction);
	}

	OpCodeHandler_VectorLength_EVEX_er::OpCodeHandler_VectorLength_EVEX_er(std::shared_ptr<OpCodeHandler> handler128, std::shared_ptr<OpCodeHandler> handler256, std::shared_ptr<OpCodeHandler> handler512)
	{
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L512) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::Unknown) == 3 ? 0 : -1);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers = std::make_shared<OpCodeHandler>[4] { handler128 ?? throw new ArgumentNullException(nameof(handler128)), handler256 ?? throw new ArgumentNullException(nameof(handler256)), handler512 ?? throw new ArgumentNullException(nameof(handler512)), OpCodeHandler_Invalid.Instance};
		handlers = { (handler128 != nullptr) ? handler128 : throw std::invalid_argument("handler128"), (handler256 != nullptr) ? handler256 : throw std::invalid_argument("handler256"), (handler512 != nullptr) ? handler512 : throw std::invalid_argument("handler512"), OpCodeHandler_Invalid::Instance };
		assert(handler128->HasModRM == HasModRM);
		assert(handler256->HasModRM == HasModRM);
		assert(handler512->HasModRM == HasModRM);
	}

	void OpCodeHandler_VectorLength_EVEX_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		std::int32_t index = static_cast<std::int32_t>(state.vectorLength);
		if (state.mod == 3 && (state.flags & StateFlags::b) != 0)
		{
			index = static_cast<std::int32_t>(VectorLength::L512);
		}
		handlers[index]->Decode(decoder, instruction);
	}

	OpCodeHandler_EVEX_V_H_Ev_er::OpCodeHandler_EVEX_V_H_Ev_er(Register baseReg, Code codeW0, Code codeW1, TupleType tupleTypeW0, TupleType tupleTypeW1)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
		this->tupleTypeW0 = tupleTypeW0;
		this->tupleTypeW1 = tupleTypeW1;
	}

	void OpCodeHandler_EVEX_V_H_Ev_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		TupleType tupleType;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
		{
			instruction.SetCode(codeW1);
			tupleType = tupleTypeW1;
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(codeW0);
			tupleType = tupleTypeW0;
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
			if ((state.flags & StateFlags::b) != 0)
			{
				Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
				instruction.SetInternalRoundingControl(state.vectorLength + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
	}

	OpCodeHandler_EVEX_V_H_Ev_Ib::OpCodeHandler_EVEX_V_H_Ev_Ib(Register baseReg, Code codeW0, Code codeW1, TupleType tupleTypeW0, TupleType tupleTypeW1)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
		this->tupleTypeW0 = tupleTypeW0;
		this->tupleTypeW1 = tupleTypeW1;
	}

	void OpCodeHandler_EVEX_V_H_Ev_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
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
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
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
			if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
			{
				decoder->ReadOpMem(instruction, tupleTypeW1);
			}
			else
			{
				decoder->ReadOpMem(instruction, tupleTypeW0);
			}
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_Ed_V_Ib::OpCodeHandler_EVEX_Ed_V_Ib(Register baseReg, Code code32, Code code64, TupleType tupleType32, TupleType tupleType64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
		this->tupleType32 = tupleType32;
		this->tupleType64 = tupleType64;
	}

	void OpCodeHandler_EVEX_Ed_V_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
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
			if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
			{
				decoder->ReadOpMem(instruction, tupleType64);
			}
			else
			{
				decoder->ReadOpMem(instruction, tupleType32);
			}
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VkHW_er::OpCodeHandler_EVEX_VkHW_er(Register baseReg, Code code, TupleType tupleType, bool onlySAE, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->onlySAE = onlySAE;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkHW_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((state.flags & StateFlags::b) != 0)
			{
				if (onlySAE)
				{
					instruction.InternalSetSuppressAllExceptions();
				}
				else
				{
					Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
					instruction.SetInternalRoundingControl(state.vectorLength + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
				}
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkHW_er_ur::OpCodeHandler_EVEX_VkHW_er_ur(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkHW_er_ur::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		std::int32_t regNum0 = static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX);
		instruction.SetOp0Register((Register)(regNum0 + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			std::int32_t regNum2 = static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX);
			instruction.SetOp2Register((Register)(regNum2 + baseReg));
			if (decoder->invalidCheckMask != 0 && (regNum0 == static_cast<std::int32_t>(state.vvvv) || regNum0 == regNum2))
			{
				decoder->SetInvalidInstruction();
			}
			if ((state.flags & StateFlags::b) != 0)
			{
				Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
				instruction.SetInternalRoundingControl(state.vectorLength + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
			}
		}
		else
		{
			if (decoder->invalidCheckMask != 0 && regNum0 == static_cast<std::int32_t>(state.vvvv))
			{
				decoder->SetInvalidInstruction();
			}
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkW_er::OpCodeHandler_EVEX_VkW_er(Register baseReg, Code code, TupleType tupleType, bool onlySAE)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->onlySAE = onlySAE;
		canBroadcast = true;
	}

	OpCodeHandler_EVEX_VkW_er::OpCodeHandler_EVEX_VkW_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool onlySAE)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
		this->onlySAE = onlySAE;
		canBroadcast = true;
	}

	OpCodeHandler_EVEX_VkW_er::OpCodeHandler_EVEX_VkW_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool onlySAE, bool canBroadcast)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
		this->onlySAE = onlySAE;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkW_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((state.flags & StateFlags::b) != 0)
			{
				if (onlySAE)
				{
					instruction.InternalSetSuppressAllExceptions();
				}
				else
				{
					Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
					instruction.SetInternalRoundingControl(state.vectorLength + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
				}
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkWIb_er::OpCodeHandler_EVEX_VkWIb_er(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VkWIb_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetSuppressAllExceptions();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetIsBroadcast();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VkW::OpCodeHandler_EVEX_VkW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	OpCodeHandler_EVEX_VkW::OpCodeHandler_EVEX_VkW(Register baseReg1, Register baseReg2, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_WkV::OpCodeHandler_EVEX_WkV(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		disallowZeroingMasking = 0;
	}

	OpCodeHandler_EVEX_WkV::OpCodeHandler_EVEX_WkV(Register baseReg, Code code, TupleType tupleType, bool allowZeroingMasking)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		disallowZeroingMasking = allowZeroingMasking ? 0 : std::numeric_limits<std::uint32_t>::max();
	}

	OpCodeHandler_EVEX_WkV::OpCodeHandler_EVEX_WkV(Register baseReg1, Register baseReg2, Code code, TupleType tupleType)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
		disallowZeroingMasking = 0;
	}

	void OpCodeHandler_EVEX_WkV::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::b) | state.vvvv_invalidCheck) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg1));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::z) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg2));
		if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::z) & disallowZeroingMasking & decoder->invalidCheckMask)) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_VkM::OpCodeHandler_EVEX_VkM(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VkM::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::b) | state.vvvv_invalidCheck) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkWIb::OpCodeHandler_EVEX_VkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_WkVIb::OpCodeHandler_EVEX_WkVIb(Register baseReg1, Register baseReg2, Code code, TupleType tupleType)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_WkVIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::b) | state.vvvv_invalidCheck) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg1));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::z) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg2));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_HkWIb::OpCodeHandler_EVEX_HkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_HkWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_HWIb::OpCodeHandler_EVEX_HWIb(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_HWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::z | StateFlags::b)) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_WkVIb_er::OpCodeHandler_EVEX_WkVIb_er(Register baseReg1, Register baseReg2, Code code, TupleType tupleType)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_WkVIb_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if ((state.vvvv_invalidCheck & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg1));
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetSuppressAllExceptions();
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			if ((static_cast<std::uint32_t>((uint)(state.flags & (StateFlags::b | StateFlags::z)) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg2));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VW_er::OpCodeHandler_EVEX_VW_er(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VW_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetSuppressAllExceptions();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_VW::OpCodeHandler_EVEX_VW(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::z | StateFlags::b)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_WV::OpCodeHandler_EVEX_WV(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_WV::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::z | StateFlags::b)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg2));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
	}

	OpCodeHandler_EVEX_VM::OpCodeHandler_EVEX_VM(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VM::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::z | StateFlags::b)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VK::OpCodeHandler_EVEX_VK(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	void OpCodeHandler_EVEX_VK::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::K0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_KR::OpCodeHandler_EVEX_KR(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	void OpCodeHandler_EVEX_KR::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_KkHWIb_sae::OpCodeHandler_EVEX_KkHWIb_sae(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_KkHWIb_sae::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetSuppressAllExceptions();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VkHW::OpCodeHandler_EVEX_VkHW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	OpCodeHandler_EVEX_VkHW::OpCodeHandler_EVEX_VkHW(Register baseReg1, Register baseReg2, Register baseReg3, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->baseReg3 = baseReg3;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkHW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg3));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkHM::OpCodeHandler_EVEX_VkHM(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VkHM::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VkHWIb::OpCodeHandler_EVEX_VkHWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	OpCodeHandler_EVEX_VkHWIb::OpCodeHandler_EVEX_VkHWIb(Register baseReg1, Register baseReg2, Register baseReg3, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg1 = baseReg1;
		this->baseReg2 = baseReg2;
		this->baseReg3 = baseReg3;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkHWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg3));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VkHWIb_er::OpCodeHandler_EVEX_VkHWIb_er(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_VkHWIb_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg3));
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetSuppressAllExceptions();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_KkHW::OpCodeHandler_EVEX_KkHW(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_KkHW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_KP1HW::OpCodeHandler_EVEX_KP1HW(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_KP1HW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				instruction.InternalSetIsBroadcast();
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.aaa | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_KkHWIb::OpCodeHandler_EVEX_KkHWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_KkHWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_WkHV::OpCodeHandler_EVEX_WkHV(Register baseReg, Code code)
	{
		this->baseReg = baseReg;
		this->code = code;
	}

	void OpCodeHandler_EVEX_WkHV::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		instruction.SetCode(code);
		assert(state.mod == 3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
		if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
	}

	OpCodeHandler_EVEX_VHWIb::OpCodeHandler_EVEX_VHWIb(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VHWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp3Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_VHW::OpCodeHandler_EVEX_VHW(Register baseReg, Code codeR, Code codeM, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		this->codeR = codeR;
		this->codeM = codeM;
		this->tupleType = tupleType;
	}

	OpCodeHandler_EVEX_VHW::OpCodeHandler_EVEX_VHW(Register baseReg, Code code, TupleType tupleType)
	{
		baseReg1 = baseReg;
		baseReg2 = baseReg;
		baseReg3 = baseReg;
		codeR = code;
		codeM = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VHW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg1));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg2));
		if (state.mod == 3)
		{
			instruction.SetCode(codeR);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg3));
		}
		else
		{
			instruction.SetCode(codeM);
			instruction.SetOp2Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_VHM::OpCodeHandler_EVEX_VHM(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VHM::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.vvvv) + baseReg));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp2Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_Gv_W_er::OpCodeHandler_EVEX_Gv_W_er(Register baseReg, Code codeW0, Code codeW1, TupleType tupleType, bool onlySAE)
	{
		this->baseReg = baseReg;
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
		this->tupleType = tupleType;
		this->onlySAE = onlySAE;
	}

	void OpCodeHandler_EVEX_Gv_W_er::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.vvvv_invalidCheck | state.aaa | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
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
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((state.flags & StateFlags::b) != 0)
			{
				if (onlySAE)
				{
					instruction.InternalSetSuppressAllExceptions();
				}
				else
				{
					Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
					instruction.SetInternalRoundingControl(state.vectorLength + static_cast<std::uint32_t>(RoundingControl::RoundToNearest));
				}
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
	}

	OpCodeHandler_EVEX_VX_Ev::OpCodeHandler_EVEX_VX_Ev(Code code32, Code code64, TupleType tupleTypeW0, TupleType tupleTypeW1)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->tupleTypeW0 = tupleTypeW0;
		this->tupleTypeW1 = tupleTypeW1;
	}

	void OpCodeHandler_EVEX_VX_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		TupleType tupleType;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			tupleType = tupleTypeW1;
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			tupleType = tupleTypeW0;
			gpr = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
	}

	OpCodeHandler_EVEX_Ev_VX::OpCodeHandler_EVEX_Ev_VX(Code code32, Code code64, TupleType tupleTypeW0, TupleType tupleTypeW1)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->tupleTypeW0 = tupleTypeW0;
		this->tupleTypeW1 = tupleTypeW1;
	}

	void OpCodeHandler_EVEX_Ev_VX::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		TupleType tupleType;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
		{
			instruction.SetCode(code64);
			tupleType = tupleTypeW1;
			gpr = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			tupleType = tupleTypeW0;
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
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + Register::XMM0));
	}

	OpCodeHandler_EVEX_Ev_VX_Ib::OpCodeHandler_EVEX_Ev_VX_Ib(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_EVEX_Ev_VX_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
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
		assert(state.mod == 3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_MV::OpCodeHandler_EVEX_MV(Register baseReg, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_MV::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction, tupleType);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
	}

	OpCodeHandler_EVEX_VkEv_REXW::OpCodeHandler_EVEX_VkEv_REXW(Register baseReg, Code code32)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		code64 = Code::INVALID;
	}

	OpCodeHandler_EVEX_VkEv_REXW::OpCodeHandler_EVEX_VkEv_REXW(Register baseReg, Code code32, Code code64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_EVEX_VkEv_REXW::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::b) | state.vvvv_invalidCheck) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
		{
			assert(code64 != Code::INVALID);
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
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_EVEX_Vk_VSIB::OpCodeHandler_EVEX_Vk_VSIB(Register baseReg, Register vsibBase, Code code, TupleType tupleType)
	{
		this->baseReg = baseReg;
		this->vsibBase = vsibBase;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_Vk_VSIB::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (decoder->invalidCheckMask != 0 && ((static_cast<std::uint32_t>(state.flags & (StateFlags::z | StateFlags::b)) | (state.vvvv_invalidCheck & 0xF)) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		std::int32_t regNum = static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(regNum + baseReg));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem_VSIB(instruction, vsibBase, tupleType);
			if (decoder->invalidCheckMask != 0)
			{
				if (static_cast<std::uint32_t>(regNum) == (static_cast<std::uint32_t>(instruction.GetMemoryIndex() - Register::XMM0) % static_cast<std::uint32_t>(IcedConstants::VMM_count)))
				{
					decoder->SetInvalidInstruction();
				}
			}
		}
	}

	OpCodeHandler_EVEX_VSIB_k1_VX::OpCodeHandler_EVEX_VSIB_k1_VX(Register vsibIndex, Register baseReg, Code code, TupleType tupleType)
	{
		this->vsibIndex = vsibIndex;
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VSIB_k1_VX::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (decoder->invalidCheckMask != 0 && ((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | (state.vvvv_invalidCheck & 0xF)) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem_VSIB(instruction, vsibIndex, tupleType);
		}
	}

	OpCodeHandler_EVEX_VSIB_k1::OpCodeHandler_EVEX_VSIB_k1(Register vsibIndex, Code code, TupleType tupleType)
	{
		this->vsibIndex = vsibIndex;
		this->code = code;
		this->tupleType = tupleType;
	}

	void OpCodeHandler_EVEX_VSIB_k1::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (decoder->invalidCheckMask != 0 && ((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | (state.vvvv_invalidCheck & 0xF)) != 0 || state.aaa == 0))
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem_VSIB(instruction, vsibIndex, tupleType);
		}
	}

	OpCodeHandler_EVEX_GvM_VX_Ib::OpCodeHandler_EVEX_GvM_VX_Ib(Register baseReg, Code code32, Code code64, TupleType tupleType32, TupleType tupleType64)
	{
		this->baseReg = baseReg;
		this->code32 = code32;
		this->code64 = code64;
		this->tupleType32 = tupleType32;
		this->tupleType64 = tupleType64;
	}

	void OpCodeHandler_EVEX_GvM_VX_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & (StateFlags::b | StateFlags::z)) | state.vvvv_invalidCheck | state.aaa) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register gpr;
		if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
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
			if ((static_cast<std::uint32_t>((uint)state.flags &decoder->is64bMode_and_W)) != 0)
			{
				decoder->ReadOpMem(instruction, tupleType64);
			}
			else
			{
				decoder->ReadOpMem(instruction, tupleType32);
			}
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase + state.extraRegisterBaseEVEX) + baseReg));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_EVEX_KkWIb::OpCodeHandler_EVEX_KkWIb(Register baseReg, Code code, TupleType tupleType, bool canBroadcast)
	{
		this->baseReg = baseReg;
		this->code = code;
		this->tupleType = tupleType;
		this->canBroadcast = canBroadcast;
	}

	void OpCodeHandler_EVEX_KkWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::EVEX);
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::z) | state.vvvv_invalidCheck | state.extraRegisterBase | state.extraRegisterBaseEVEX) & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::K0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBaseEVEX) + baseReg));
			if ((static_cast<std::uint32_t>((uint)(state.flags & StateFlags::b) & decoder->invalidCheckMask)) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			if ((state.flags & StateFlags::b) != 0)
			{
				if (canBroadcast)
				{
					instruction.InternalSetIsBroadcast();
				}
				else if (decoder->invalidCheckMask != 0)
				{
					decoder->SetInvalidInstruction();
				}
			}
			decoder->ReadOpMem(instruction, tupleType);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}
}
