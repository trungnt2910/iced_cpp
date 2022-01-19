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

#include "OpCodeHandlers_Legacy.h"
#include "../EncodingKind.g.h"
#include "../MandatoryPrefixByte.g.h"
#include "../OpKind.g.h"
#include "../Static.h"
#include "../DecoderOptions.g.h"
#include "../CodeSize.g.h"
#include <csharp/exceptionhelper.h>

namespace Iced::Intel::DecoderInternal
{

	OpCodeHandler_VEX2::OpCodeHandler_VEX2(std::shared_ptr<OpCodeHandler> handlerMem)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerMem = handlerMem ?? throw new ArgumentNullException(nameof(handlerMem));
		this->handlerMem = (handlerMem != nullptr) ? handlerMem : throw std::invalid_argument("handlerMem");
	}

	void OpCodeHandler_VEX2::Decode(Decoder* decoder, Instruction& instruction)
	{
		if (decoder->is64bMode)
		{
			decoder->VEX2(instruction);
		}
		else if (decoder->state.mod == 3)
		{
			decoder->VEX2(instruction);
		}
		else
		{
			handlerMem->Decode(decoder, instruction);
		}
	}

	OpCodeHandler_VEX3::OpCodeHandler_VEX3(std::shared_ptr<OpCodeHandler> handlerMem)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerMem = handlerMem ?? throw new ArgumentNullException(nameof(handlerMem));
		this->handlerMem = (handlerMem != nullptr) ? handlerMem : throw std::invalid_argument("handlerMem");
	}

	void OpCodeHandler_VEX3::Decode(Decoder* decoder, Instruction& instruction)
	{
		if (decoder->is64bMode)
		{
			decoder->VEX3(instruction);
		}
		else if (decoder->state.mod == 3)
		{
			decoder->VEX3(instruction);
		}
		else
		{
			handlerMem->Decode(decoder, instruction);
		}
	}

	OpCodeHandler_XOP::OpCodeHandler_XOP(std::shared_ptr<OpCodeHandler> handler_reg0)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handler_reg0 = handler_reg0 ?? throw new ArgumentNullException(nameof(handler_reg0));
		this->handler_reg0 = (handler_reg0 != nullptr) ? handler_reg0 : throw std::invalid_argument("handler_reg0");
	}

	void OpCodeHandler_XOP::Decode(Decoder* decoder, Instruction& instruction)
	{
		if ((decoder->state.modrm & 0x1F) < 8)
		{
			handler_reg0->Decode(decoder, instruction);
		}
		else
		{
			decoder->XOP(instruction);
		}
	}

	OpCodeHandler_EVEX::OpCodeHandler_EVEX(std::shared_ptr<OpCodeHandler> handlerMem)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerMem = handlerMem ?? throw new ArgumentNullException(nameof(handlerMem));
		this->handlerMem = (handlerMem != nullptr) ? handlerMem : throw std::invalid_argument("handlerMem");
	}

	void OpCodeHandler_EVEX::Decode(Decoder* decoder, Instruction& instruction)
	{
		if (decoder->is64bMode)
		{
			decoder->EVEX_MVEX(instruction);
		}
		else if (decoder->state.mod == 3)
		{
			decoder->EVEX_MVEX(instruction);
		}
		else
		{
			handlerMem->Decode(decoder, instruction);
		}
	}

	OpCodeHandler_PrefixEsCsSsDs::OpCodeHandler_PrefixEsCsSsDs(Register seg)
	{
		assert(seg == Register::ES || seg == Register::CS || seg == Register::SS || seg == Register::DS);
		this->seg = seg;
	}

	void OpCodeHandler_PrefixEsCsSsDs::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		if (!decoder->is64bMode || decoder->state.segmentPrio <= 0)
		{
			instruction.SetSegmentPrefix(seg);
		}
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_PrefixFsGs::OpCodeHandler_PrefixFsGs(Register seg)
	{
		assert(seg == Register::FS || seg == Register::GS);
		this->seg = seg;
	}

	void OpCodeHandler_PrefixFsGs::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetSegmentPrefix(seg);
		decoder->state.segmentPrio = 1;
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_Prefix66::OpCodeHandler_Prefix66()
	{
	}

	void OpCodeHandler_Prefix66::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		decoder->state.flags |= StateFlags::Has66;
		decoder->state.operandSize = decoder->defaultInvertedOperandSize;
		if (decoder->state.mandatoryPrefix == MandatoryPrefixByte::None)
		{
			decoder->state.mandatoryPrefix = MandatoryPrefixByte::P66;
		}
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_Prefix67::OpCodeHandler_Prefix67()
	{
	}

	void OpCodeHandler_Prefix67::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		decoder->state.addressSize = decoder->defaultInvertedAddressSize;
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_PrefixF0::OpCodeHandler_PrefixF0()
	{
	}

	void OpCodeHandler_PrefixF0::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.InternalSetHasLockPrefix();
		decoder->state.flags |= StateFlags::Lock;
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_PrefixF2::OpCodeHandler_PrefixF2()
	{
	}

	void OpCodeHandler_PrefixF2::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.InternalSetHasRepnePrefix();
		decoder->state.mandatoryPrefix = MandatoryPrefixByte::PF2;
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_PrefixF3::OpCodeHandler_PrefixF3()
	{
	}

	void OpCodeHandler_PrefixF3::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.InternalSetHasRepePrefix();
		decoder->state.mandatoryPrefix = MandatoryPrefixByte::PF3;
		decoder->ResetRexPrefixState();
		decoder->CallOpCodeHandlerXXTable(instruction);
	}

	OpCodeHandler_PrefixREX::OpCodeHandler_PrefixREX(std::shared_ptr<OpCodeHandler> handler, std::uint32_t rex)
	{
		assert(rex <= 0x0F);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handler = handler ?? throw new InvalidOperationException();
		this->handler = (handler != nullptr) ? handler : throw InvalidOperationException();
		this->rex = rex;
	}

	void OpCodeHandler_PrefixREX::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if ((rex & 8) != 0)
			{
				decoder->state.operandSize = OpSize::Size64;
				decoder->state.flags |= StateFlags::HasRex | StateFlags::W;
			}
			else
			{
				decoder->state.flags |= StateFlags::HasRex;
				decoder->state.flags &= ~StateFlags::W;
				if ((decoder->state.flags & StateFlags::Has66) == 0)
				{
					decoder->state.operandSize = OpSize::Size32;
				}
				else
				{
					decoder->state.operandSize = OpSize::Size16;
				}
			}
			decoder->state.extraRegisterBase = (rex & 4) << 1;
			decoder->state.extraIndexRegisterBase = (rex & 2) << 2;
			decoder->state.extraBaseRegisterBase = (rex & 1) << 3;
			decoder->CallOpCodeHandlerXXTable(instruction);
		}
		else
		{
			handler->Decode(decoder, instruction);
		}
	}

	OpCodeHandler_Reg::OpCodeHandler_Reg(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Reg::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
	}

	OpCodeHandler_RegIb::OpCodeHandler_RegIb(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_RegIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_IbReg::OpCodeHandler_IbReg(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_IbReg::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(reg);
	}

	OpCodeHandler_AL_DX::OpCodeHandler_AL_DX(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_AL_DX::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::AL);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::DX);
	}

	OpCodeHandler_DX_AL::OpCodeHandler_DX_AL(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_DX_AL::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::DX);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::AL);
	}

	OpCodeHandler_Ib::OpCodeHandler_Ib(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Ib3::OpCodeHandler_Ib3(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Ib3::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_MandatoryPrefix::OpCodeHandler_MandatoryPrefix(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2)
	{
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers = std::make_shared<OpCodeHandler>[4] { handler ?? throw new ArgumentNullException(nameof(handler)), handler66 ?? throw new ArgumentNullException(nameof(handler66)), handlerF3 ?? throw new ArgumentNullException(nameof(handlerF3)), handlerF2 ?? throw new ArgumentNullException(nameof(handlerF2))};
		handlers = { (handler != nullptr) ? handler : throw std::invalid_argument("handler"), (handler66 != nullptr) ? handler66 : throw std::invalid_argument("handler66"), (handlerF3 != nullptr) ? handlerF3 : throw std::invalid_argument("handlerF3"), (handlerF2 != nullptr) ? handlerF2 : throw std::invalid_argument("handlerF2") };
		assert(handler->HasModRM == HasModRM);
		assert(handler66->HasModRM == HasModRM);
		assert(handlerF3->HasModRM == HasModRM);
		assert(handlerF2->HasModRM == HasModRM);
	}

	void OpCodeHandler_MandatoryPrefix::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		decoder->ClearMandatoryPrefix(instruction);
		handlers[static_cast<std::int32_t>(decoder->state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	OpCodeHandler_MandatoryPrefix3::Info::Info(std::shared_ptr<OpCodeHandler> handler, bool mandatoryPrefix)
	{
		this->handler = handler;
		this->mandatoryPrefix = mandatoryPrefix;
	}

	OpCodeHandler_MandatoryPrefix3::OpCodeHandler_MandatoryPrefix3(std::shared_ptr<OpCodeHandler> handler_reg, std::shared_ptr<OpCodeHandler> handler_mem, std::shared_ptr<OpCodeHandler> handler66_reg, std::shared_ptr<OpCodeHandler> handler66_mem, std::shared_ptr<OpCodeHandler> handlerF3_reg, std::shared_ptr<OpCodeHandler> handlerF3_mem, std::shared_ptr<OpCodeHandler> handlerF2_reg, std::shared_ptr<OpCodeHandler> handlerF2_mem, LegacyHandlerFlags flags)
	{
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers_reg = new Info[4] { new Info(handler_reg ?? throw new ArgumentNullException(nameof(handler_reg)), (flags & LegacyHandlerFlags.HandlerReg) == 0), new Info(handler66_reg ?? throw new ArgumentNullException(nameof(handler66_reg)), (flags & LegacyHandlerFlags.Handler66Reg) == 0), new Info(handlerF3_reg ?? throw new ArgumentNullException(nameof(handlerF3_reg)), (flags & LegacyHandlerFlags.HandlerF3Reg) == 0), new Info(handlerF2_reg ?? throw new ArgumentNullException(nameof(handlerF2_reg)), (flags & LegacyHandlerFlags.HandlerF2Reg) == 0)};
		handlers_reg =
		{
			Info((handler_reg == nullptr) ? throw ArgumentNullException(nameof(handler_reg)) : handler_reg, (flags & LegacyHandlerFlags::HandlerReg) == 0),
			Info((handler66_reg == nullptr) ? throw ArgumentNullException(nameof(handler66_reg)) : handler66_reg, (flags & LegacyHandlerFlags::Handler66Reg) == 0),
			Info((handlerF3_reg == nullptr) ? throw new ArgumentNullException(nameof(handlerF3_reg)) : handlerF3_reg, (flags & LegacyHandlerFlags::HandlerF3Reg) == 0),
			Info((handlerF2_reg == nullptr) ? throw new ArgumentNullException(nameof(handlerF2_reg)) : handlerF2_reg, (flags & LegacyHandlerFlags::HandlerF2Reg) == 0),
		};
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers_mem = new Info[4] { new Info(handler_mem ?? throw new ArgumentNullException(nameof(handler_mem)), (flags & LegacyHandlerFlags.HandlerMem) == 0), new Info(handler66_mem ?? throw new ArgumentNullException(nameof(handler66_mem)), (flags & LegacyHandlerFlags.Handler66Mem) == 0), new Info(handlerF3_mem ?? throw new ArgumentNullException(nameof(handlerF3_mem)), (flags & LegacyHandlerFlags.HandlerF3Mem) == 0), new Info(handlerF2_mem ?? throw new ArgumentNullException(nameof(handlerF2_mem)), (flags & LegacyHandlerFlags.HandlerF2Mem) == 0)};
		handlers_mem =
		{
			Info((handler_mem == nullptr) ? throw ArgumentNullException(nameof(handler_mem)) : handler_mem, (flags & LegacyHandlerFlags::HandlerMem) == 0),
			Info((handler66_mem == nullptr) ? throw ArgumentNullException(nameof(handler66_mem)) : handler66_mem, (flags & LegacyHandlerFlags::Handler66Mem) == 0),
			Info((handlerF3_mem == nullptr) ? throw ArgumentNullException(nameof(handlerF3_mem)) : handlerF3_mem, (flags & LegacyHandlerFlags::HandlerF3Mem) == 0),
			Info((handlerF2_mem == nullptr) ? throw ArgumentNullException(nameof(handlerF2_mem)) : handlerF2_mem, (flags & LegacyHandlerFlags::HandlerF2Mem) == 0),
		};
		assert(handler_reg->HasModRM == HasModRM);
		assert(handler_mem->HasModRM == HasModRM);
		assert(handler66_reg->HasModRM == HasModRM);
		assert(handler66_mem->HasModRM == HasModRM);
		assert(handlerF3_reg->HasModRM == HasModRM);
		assert(handlerF3_mem->HasModRM == HasModRM);
		assert(handlerF2_reg->HasModRM == HasModRM);
		assert(handlerF2_mem->HasModRM == HasModRM);
	}

	void OpCodeHandler_MandatoryPrefix3::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		auto handlers = decoder->state.mod == 3 ? handlers_reg : handlers_mem;
		Info& info = handlers[static_cast<std::int32_t>(decoder->state.mandatoryPrefix)];
		if (info.mandatoryPrefix)
		{
			decoder->ClearMandatoryPrefix(instruction);
		}
		info.handler->Decode(decoder, instruction);
	}

	OpCodeHandler_MandatoryPrefix4::OpCodeHandler_MandatoryPrefix4(std::shared_ptr<OpCodeHandler> handlerNP, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2, std::uint32_t flags)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerNP = handlerNP ?? throw new ArgumentNullException(nameof(handlerNP));
		this->handlerNP = (handlerNP != nullptr) ? handlerNP : throw std::invalid_argument("handlerNP");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handler66 = handler66 ?? throw new ArgumentNullException(nameof(handler66));
		this->handler66 = (handler66 != nullptr) ? handler66 : throw std::invalid_argument("handler66");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerF3 = handlerF3 ?? throw new ArgumentNullException(nameof(handlerF3));
		this->handlerF3 = (handlerF3 != nullptr) ? handlerF3 : throw std::invalid_argument("handlerF3");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerF2 = handlerF2 ?? throw new ArgumentNullException(nameof(handlerF2));
		this->handlerF2 = (handlerF2 != nullptr) ? handlerF2 : throw std::invalid_argument("handlerF2");
		this->flags = flags;
	}

	void OpCodeHandler_MandatoryPrefix4::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		std::shared_ptr<OpCodeHandler> handler;
		auto prefix = decoder->state.mandatoryPrefix;
		switch (prefix)
		{
		case MandatoryPrefixByte::None:
			handler = handlerNP;
			break;
		case MandatoryPrefixByte::P66:
			handler = handler66;
			break;
		case MandatoryPrefixByte::PF3:
			if ((flags & 4) != 0)
			{
				decoder->ClearMandatoryPrefixF3(instruction);
			}
			handler = handlerF3;
			break;
		case MandatoryPrefixByte::PF2:
			if ((flags & 8) != 0)
			{
				decoder->ClearMandatoryPrefixF2(instruction);
			}
			handler = handlerF2;
			break;
		default:
			throw InvalidOperationException();
		}
		if (handler->HasModRM && (flags & 0x10) != 0)
		{
			decoder->ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_MandatoryPrefix_NoModRM::OpCodeHandler_MandatoryPrefix_NoModRM(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2)
	{
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: handlers = std::make_shared<OpCodeHandler>[4] { handler ?? throw new ArgumentNullException(nameof(handler)), handler66 ?? throw new ArgumentNullException(nameof(handler66)), handlerF3 ?? throw new ArgumentNullException(nameof(handlerF3)), handlerF2 ?? throw new ArgumentNullException(nameof(handlerF2))};
		handlers = { (handler != nullptr) ? handler : throw std::invalid_argument("handler"), (handler66 != nullptr) ? handler66 : throw std::invalid_argument("handler66"), (handlerF3 != nullptr) ? handlerF3 : throw std::invalid_argument("handlerF3"), (handlerF2 != nullptr) ? handlerF2 : throw std::invalid_argument("handlerF2") };
		assert(handler->HasModRM == HasModRM);
		assert(handler66->HasModRM == HasModRM);
		assert(handlerF3->HasModRM == HasModRM);
		assert(handlerF2->HasModRM == HasModRM);
	}

	void OpCodeHandler_MandatoryPrefix_NoModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		decoder->ClearMandatoryPrefix(instruction);
		handlers[static_cast<std::int32_t>(decoder->state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	OpCodeHandler_NIb::OpCodeHandler_NIb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_NIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Reservednop::OpCodeHandler_Reservednop(std::shared_ptr<OpCodeHandler> reservedNopHandler, std::shared_ptr<OpCodeHandler> otherHandler)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.reservedNopHandler = reservedNopHandler ?? throw new ArgumentNullException(nameof(reservedNopHandler));
		this->reservedNopHandler = (reservedNopHandler != nullptr) ? reservedNopHandler : throw std::invalid_argument("reservedNopHandler");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.otherHandler = otherHandler ?? throw new ArgumentNullException(nameof(otherHandler));
		this->otherHandler = (otherHandler != nullptr) ? otherHandler : throw std::invalid_argument("otherHandler");
	}

	void OpCodeHandler_Reservednop::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		((decoder->options & DecoderOptions::ForceReservedNop) != 0 ? reservedNopHandler : otherHandler)->Decode(decoder, instruction);
	}

	OpCodeHandler_Ev_Iz::OpCodeHandler_Ev_Iz(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_Ev_Iz::OpCodeHandler_Ev_Iz(Code code16, Code code32, Code code64, HandlerFlags flags)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
	}

	void OpCodeHandler_Ev_Iz::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			instruction.SetOp1Kind(OpKind::Immediate32);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			instruction.SetOp1Kind(OpKind::Immediate32to64);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp1Kind(OpKind::Immediate16);
			instruction.SetInternalImmediate16(decoder->ReadUInt16());
		}
	}

	OpCodeHandler_Ev_Ib::OpCodeHandler_Ev_Ib(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_Ev_Ib::OpCodeHandler_Ev_Ib(Code code16, Code code32, Code code64, HandlerFlags flags)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
	}

	void OpCodeHandler_Ev_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			instruction.SetOp1Kind(OpKind::Immediate8to32);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			instruction.SetOp1Kind(OpKind::Immediate8to64);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp1Kind(OpKind::Immediate8to16);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
	}

	OpCodeHandler_Ev_Ib2::OpCodeHandler_Ev_Ib2(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_Ev_Ib2::OpCodeHandler_Ev_Ib2(Code code16, Code code32, Code code64, HandlerFlags flags)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
	}

	void OpCodeHandler_Ev_Ib2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Ev_1::OpCodeHandler_Ev_1(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_1::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(1);
		state.flags |= StateFlags::NoImm;
	}

	OpCodeHandler_Ev_CL::OpCodeHandler_Ev_CL(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_CL::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::CL);
	}

	OpCodeHandler_Ev::OpCodeHandler_Ev(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_Ev::OpCodeHandler_Ev(Code code16, Code code32, Code code64, HandlerFlags flags)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
	}

	void OpCodeHandler_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
	}

	OpCodeHandler_Rv::OpCodeHandler_Rv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Rv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::AX));
		}
		assert(state.mod == 3);
	}

	OpCodeHandler_Rv_32_64::OpCodeHandler_Rv_32_64(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Rv_32_64::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register baseReg;
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			baseReg = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			baseReg = Register::EAX;
		}
		assert(state.mod == 3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
	}

	OpCodeHandler_Rq::OpCodeHandler_Rq(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Rq::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		assert(state.mod == 3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
	}

	OpCodeHandler_Ev_REXW::OpCodeHandler_Ev_REXW(Code code32, Code code64, std::uint32_t flags)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
		disallowReg = (flags & 1) != 0 ? 0 : std::numeric_limits<std::uint32_t>::max();
		disallowMem = (flags & 2) != 0 ? 0 : std::numeric_limits<std::uint32_t>::max();
	}

	void OpCodeHandler_Ev_REXW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		Static::Assert(static_cast<std::uint32_t>(StateFlags::Has66) != 4 ? 0 : -1);
		if ((((flags & 4) | (uint)(state.flags & StateFlags::Has66)) & decoder->invalidCheckMask) == (4 | (uint)StateFlags::Has66))
		{
			decoder->SetInvalidInstruction();
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			if ((state.flags & StateFlags::W) != 0)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
			}
			if ((disallowReg & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			if ((disallowMem & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
	}

	OpCodeHandler_Evj::OpCodeHandler_Evj(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Evj::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
			if (state.mod == 3)
			{
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
				}
				else
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::AX));
				}
			}
			else
			{
				instruction.SetOp0Kind(OpKind::Memory);
				decoder->ReadOpMem(instruction);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
			if (state.mod == 3)
			{
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				if (state.operandSize == OpSize::Size32)
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm) + Register::EAX));
				}
				else
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm) + Register::AX));
				}
			}
			else
			{
				instruction.SetOp0Kind(OpKind::Memory);
				decoder->ReadOpMem(instruction);
			}
		}
	}

	OpCodeHandler_Ep::OpCodeHandler_Ep(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ep::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size64 && (decoder->options & DecoderOptions::AMD) == 0)
		{
			instruction.SetCode(code64);
		}
		else if (state.operandSize == OpSize::Size16)
		{
			instruction.SetCode(code16);
		}
		else
		{
			instruction.SetCode(code32);
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Evw::OpCodeHandler_Evw(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Evw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ew::OpCodeHandler_Ew(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ew::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ms::OpCodeHandler_Ms(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ms::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
		}
		else if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else
		{
			instruction.SetCode(code16);
		}
		assert(state.mod != 3);
		instruction.SetOp0Kind(OpKind::Memory);
		decoder->ReadOpMem(instruction);
	}

	OpCodeHandler_Gv_Ev::OpCodeHandler_Gv_Ev(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gd_Rd::OpCodeHandler_Gd_Rd(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Gd_Rd::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_Gv_M_as::OpCodeHandler_Gv_M_as(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_M_as::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gdq_Ev::OpCodeHandler_Gdq_Ev(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gdq_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gv_Ev3::OpCodeHandler_Gv_Ev3(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev3::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gv_Ev2::OpCodeHandler_Gv_Ev2(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_R_C::OpCodeHandler_R_C(Code code32, Code code64, Register baseReg)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->baseReg = baseReg;
	}

	void OpCodeHandler_R_C::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		auto extraRegisterBase = state.extraRegisterBase;
		// LOCK MOV CR0 is supported by some AMD CPUs
		if (baseReg == Register::CR0 && instruction.GetHasLockPrefix() && (decoder->options & DecoderOptions::AMD) != 0)
		{
			if ((extraRegisterBase & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			extraRegisterBase = 8;
			instruction.InternalClearHasLockPrefix();
			state.flags &= ~StateFlags::Lock;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		auto reg = static_cast<std::int32_t>(state.reg + extraRegisterBase);
		if (decoder->invalidCheckMask != 0)
		{
			if (baseReg == Register::CR0)
			{
				if (reg == 1 || (reg != 8 && reg >= 5))
				{
					decoder->SetInvalidInstruction();
				}
			}
			else if (baseReg == Register::DR0)
			{
				if (reg > 7)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				assert(!decoder->is64bMode);
				assert(baseReg == Register::TR0);
			}
		}
		instruction.SetOp1Register((Register)(reg + baseReg));
	}

	OpCodeHandler_C_R::OpCodeHandler_C_R(Code code32, Code code64, Register baseReg)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->baseReg = baseReg;
	}

	void OpCodeHandler_C_R::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		auto extraRegisterBase = state.extraRegisterBase;
		// LOCK MOV CR0 is supported by some AMD CPUs
		if (baseReg == Register::CR0 && instruction.GetHasLockPrefix() && (decoder->options & DecoderOptions::AMD) != 0)
		{
			if ((extraRegisterBase & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
			extraRegisterBase = 8;
			instruction.InternalClearHasLockPrefix();
			state.flags &= ~StateFlags::Lock;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		auto reg = static_cast<std::int32_t>(state.reg + extraRegisterBase);
		if (decoder->invalidCheckMask != 0)
		{
			if (baseReg == Register::CR0)
			{
				if (reg == 1 || (reg != 8 && reg >= 5))
				{
					decoder->SetInvalidInstruction();
				}
			}
			else if (baseReg == Register::DR0)
			{
				if (reg > 7)
				{
					decoder->SetInvalidInstruction();
				}
			}
			else
			{
				assert(!decoder->is64bMode);
				assert(baseReg == Register::TR0);
			}
		}
		instruction.SetOp0Register((Register)(reg + baseReg));
	}

	OpCodeHandler_Jb::OpCodeHandler_Jb(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Jb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		state.flags |= StateFlags::BranchImm8;
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer64());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32()));
			}
		}
		else
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::NearBranch32);
				instruction.SetNearBranch32(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32()));
			}
		}
	}

	OpCodeHandler_Jx::OpCodeHandler_Jx(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Jx::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		state.flags |= StateFlags::Xbegin;
		if (decoder->is64bMode)
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int32_t>(decoder->ReadUInt32())) + decoder->GetCurrentInstructionPointer64());
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetCode(code64);
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int32_t>(decoder->ReadUInt32())) + decoder->GetCurrentInstructionPointer64());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int16_t>(decoder->ReadUInt16())) + decoder->GetCurrentInstructionPointer64());
			}
		}
		else
		{
			assert(decoder->defaultCodeSize == CodeSize::Code16 || decoder->defaultCodeSize == CodeSize::Code32);
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::NearBranch32);
				instruction.SetNearBranch32(decoder->ReadUInt32() + decoder->GetCurrentInstructionPointer32());
			}
			else
			{
				assert(state.operandSize == OpSize::Size16);
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch32);
				instruction.SetNearBranch32(static_cast<std::uint32_t>(static_cast<std::int16_t>(decoder->ReadUInt16())) + decoder->GetCurrentInstructionPointer32());
			}
		}
	}

	OpCodeHandler_Jz::OpCodeHandler_Jz(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Jz::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int32_t>(decoder->ReadUInt32())) + decoder->GetCurrentInstructionPointer64());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(decoder->ReadUInt16() + decoder->GetCurrentInstructionPointer32()));
			}
		}
		else
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::NearBranch32);
				instruction.SetNearBranch32(decoder->ReadUInt32() + decoder->GetCurrentInstructionPointer32());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(decoder->ReadUInt16() + decoder->GetCurrentInstructionPointer32()));
			}
		}
	}

	OpCodeHandler_Jb2::OpCodeHandler_Jb2(Code code16_16, Code code16_32, Code code16_64, Code code32_16, Code code32_32, Code code64_32, Code code64_64)
	{
		this->code16_16 = code16_16;
		this->code16_32 = code16_32;
		this->code16_64 = code16_64;
		this->code32_16 = code32_16;
		this->code32_32 = code32_32;
		this->code64_32 = code64_32;
		this->code64_64 = code64_64;
	}

	void OpCodeHandler_Jb2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		state.flags |= StateFlags::BranchImm8;
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
			{
				if (state.addressSize == OpSize::Size64)
				{
					instruction.SetCode(code64_64);
				}
				else
				{
					instruction.SetCode(code64_32);
				}
				instruction.SetOp0Kind(OpKind::NearBranch64);
				instruction.SetNearBranch64(static_cast<std::uint64_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer64());
			}
			else
			{
				if (state.addressSize == OpSize::Size64)
				{
					instruction.SetCode(code16_64);
				}
				else
				{
					instruction.SetCode(code16_32);
				}
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32()));
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				if (state.addressSize == OpSize::Size32)
				{
					instruction.SetCode(code32_32);
				}
				else
				{
					instruction.SetCode(code32_16);
				}
				instruction.SetOp0Kind(OpKind::NearBranch32);
				instruction.SetNearBranch32(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32());
			}
			else
			{
				if (state.addressSize == OpSize::Size32)
				{
					instruction.SetCode(code16_32);
				}
				else
				{
					instruction.SetCode(code16_16);
				}
				instruction.SetOp0Kind(OpKind::NearBranch16);
				instruction.SetInternalNearBranch16(static_cast<std::uint16_t>(static_cast<std::uint32_t>(static_cast<std::int8_t>(decoder->ReadByte())) + decoder->GetCurrentInstructionPointer32()));
			}
		}
	}

	OpCodeHandler_Jdisp::OpCodeHandler_Jdisp(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Jdisp::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		assert(!decoder->is64bMode);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			instruction.SetOp0Kind(OpKind::NearBranch32);
			instruction.SetNearBranch32(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp0Kind(OpKind::NearBranch16);
			instruction.SetInternalNearBranch16(decoder->ReadUInt16());
		}
	}

	OpCodeHandler_PushOpSizeReg::OpCodeHandler_PushOpSizeReg(Code code16, Code code32, Code code64, Register reg)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->reg = reg;
	}

	void OpCodeHandler_PushOpSizeReg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
	}

	OpCodeHandler_PushEv::OpCodeHandler_PushEv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_PushEv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (decoder->is64bMode)
			{
				if (state.operandSize != OpSize::Size16)
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
				}
				else
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
				}
			}
			else
			{
				if (state.operandSize == OpSize::Size32)
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
				}
				else
				{
					instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
				}
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ev_Gv::OpCodeHandler_Ev_Gv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_Ev_Gv::OpCodeHandler_Ev_Gv(Code code16, Code code32, Code code64, HandlerFlags flags)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
		this->flags = flags;
	}

	void OpCodeHandler_Ev_Gv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
	}

	OpCodeHandler_Ev_Gv_32_64::OpCodeHandler_Ev_Gv_32_64(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_Gv_32_64::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register baseReg;
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			baseReg = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			baseReg = Register::EAX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
	}

	OpCodeHandler_Ev_Gv_Ib::OpCodeHandler_Ev_Gv_Ib(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_Gv_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Ev_Gv_CL::OpCodeHandler_Ev_Gv_CL(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_Gv_CL::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(Register::CL);
	}

	OpCodeHandler_Gv_Mp::OpCodeHandler_Gv_Mp(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Mp::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size64 && (decoder->options & DecoderOptions::AMD) == 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else if (state.operandSize == OpSize::Size16)
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gv_Eb::OpCodeHandler_Gv_Eb(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Eb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gv_Ew::OpCodeHandler_Gv_Ew(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ew::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::AX));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_PushSimple2::OpCodeHandler_PushSimple2(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_PushSimple2::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (decoder->state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (decoder->state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
	}

	OpCodeHandler_Simple2::OpCodeHandler_Simple2(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
	}

	OpCodeHandler_Simple2Iw::OpCodeHandler_Simple2Iw(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple2Iw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		instruction.SetOp0Kind(OpKind::Immediate16);
		instruction.SetInternalImmediate16(decoder->ReadUInt16());
	}

	OpCodeHandler_Simple3::OpCodeHandler_Simple3(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple3::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
	}

	OpCodeHandler_Simple5::OpCodeHandler_Simple5(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple5::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else
		{
			instruction.SetCode(code16);
		}
	}

	OpCodeHandler_Simple5_ModRM_as::OpCodeHandler_Simple5_ModRM_as(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple5_ModRM_as::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::AX));
		}
	}

	OpCodeHandler_Simple4::OpCodeHandler_Simple4(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Simple4::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
	}

	OpCodeHandler_PushSimpleReg::OpCodeHandler_PushSimpleReg(std::int32_t index, Code code16, Code code32, Code code64)
	{
		assert(0 <= index && index <= 7);
		this->index = index;
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_PushSimpleReg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::RAX));
			}
			else
			{
				instruction.SetCode(code16);
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::AX));
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::EAX));
			}
			else
			{
				instruction.SetCode(code16);
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::AX));
			}
		}
	}

	OpCodeHandler_SimpleReg::OpCodeHandler_SimpleReg(Code code, std::int32_t index)
	{
		assert(0 <= index && index <= 7);
		this->code = code;
		this->index = index;
	}

	void OpCodeHandler_SimpleReg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Static::Assert(static_cast<std::int32_t>(OpSize::Size16) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(OpSize::Size32) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(OpSize::Size64) == 2 ? 0 : -1);
		std::int32_t sizeIndex = static_cast<std::int32_t>(state.operandSize);
		instruction.SetCode((Code)(sizeIndex + code));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		Static::Assert(Register::AX + 16 == Register::EAX ? 0 : -1);
		Static::Assert(Register::AX + 32 == Register::RAX ? 0 : -1);
		instruction.SetOp0Register((Register)(sizeIndex * 16 + (Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::AX)));
	}

	OpCodeHandler_Xchg_Reg_rAX::OpCodeHandler_Xchg_Reg_rAX(std::int32_t index)
	{
		assert(0 <= index && index <= 7);
		this->index = index;
	}

	void OpCodeHandler_Xchg_Reg_rAX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (index == 0 && state.mandatoryPrefix == MandatoryPrefixByte::PF3 && (decoder->options & DecoderOptions::NoPause) == 0)
		{
			decoder->ClearMandatoryPrefixF3(instruction);
			instruction.SetCode(Code::Pause);
		}
		else
		{
			Static::Assert(static_cast<std::int32_t>(OpSize::Size16) == 0 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(OpSize::Size32) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(OpSize::Size64) == 2 ? 0 : -1);
			std::int32_t sizeIndex = static_cast<std::int32_t>(state.operandSize);
			std::int32_t codeIndex = index + static_cast<std::int32_t>(state.extraBaseRegisterBase);
			instruction.SetCode(codes[sizeIndex * 16 + codeIndex]);
			if (codeIndex != 0)
			{
				Static::Assert(Register::AX + 16 == Register::EAX ? 0 : -1);
				Static::Assert(Register::AX + 32 == Register::RAX ? 0 : -1);
				auto reg = sizeIndex * 16 + codeIndex + Register::AX;
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op0Kind = OpKind.Register;
				instruction.SetOp0Register((Register)reg);
				Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
				//instruction.Op1Kind = OpKind.Register;
				instruction.SetOp1Register((Register)(sizeIndex * 16 + Register::AX));
			}
		}
	}

	OpCodeHandler_Reg_Iz::OpCodeHandler_Reg_Iz(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Reg_Iz::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::EAX);
			instruction.SetOp1Kind(OpKind::Immediate32);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::RAX);
			instruction.SetOp1Kind(OpKind::Immediate32to64);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::AX);
			instruction.SetOp1Kind(OpKind::Immediate16);
			instruction.SetInternalImmediate16(decoder->ReadUInt16());
		}
	}

	OpCodeHandler_RegIb3::OpCodeHandler_RegIb3(std::int32_t index)
	{
		assert(0 <= index && index <= 7);
		this->index = index;
		withRexPrefix = s_withRexPrefix;
	}

	std::vector<Register> OpCodeHandler_RegIb3::s_withRexPrefix = { Register::AL, Register::CL, Register::DL, Register::BL, Register::SPL, Register::BPL, Register::SIL, Register::DIL, Register::R8L, Register::R9L, Register::R10L, Register::R11L, Register::R12L, Register::R13L, Register::R14L, Register::R15L };

	void OpCodeHandler_RegIb3::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register register_;
		if ((state.flags & StateFlags::HasRex) != 0)
		{
			register_ = withRexPrefix[index + static_cast<std::int32_t>(state.extraBaseRegisterBase)];
		}
		else
		{
			register_ = (Register)(index + Register::AL);
		}
		instruction.SetCode(Code::Mov_r8_imm8);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_RegIz2::OpCodeHandler_RegIz2(std::int32_t index)
	{
		assert(0 <= index && index <= 7);
		this->index = index;
	}

	void OpCodeHandler_RegIz2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(Code::Mov_r32_imm32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::EAX));
			instruction.SetOp1Kind(OpKind::Immediate32);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(Code::Mov_r64_imm64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::RAX));
			instruction.SetOp1Kind(OpKind::Immediate64);
			instruction.SetInternalImmediate64Lo(decoder->ReadUInt32());
			instruction.SetInternalImmediate64Hi(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetCode(Code::Mov_r16_imm16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(index + static_cast<std::int32_t>(state.extraBaseRegisterBase) + Register::AX));
			instruction.SetOp1Kind(OpKind::Immediate16);
			instruction.SetInternalImmediate16(decoder->ReadUInt16());
		}
	}

	OpCodeHandler_PushIb2::OpCodeHandler_PushIb2(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_PushIb2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
				instruction.SetOp0Kind(OpKind::Immediate8to64);
				instruction.SetInternalImmediate8(decoder->ReadByte());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::Immediate8to16);
				instruction.SetInternalImmediate8(decoder->ReadByte());
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::Immediate8to32);
				instruction.SetInternalImmediate8(decoder->ReadByte());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::Immediate8to16);
				instruction.SetInternalImmediate8(decoder->ReadByte());
			}
		}
	}

	OpCodeHandler_PushIz::OpCodeHandler_PushIz(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_PushIz::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
				instruction.SetOp0Kind(OpKind::Immediate32to64);
				instruction.SetImmediate32(decoder->ReadUInt32());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::Immediate16);
				instruction.SetInternalImmediate16(decoder->ReadUInt16());
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
				instruction.SetOp0Kind(OpKind::Immediate32);
				instruction.SetImmediate32(decoder->ReadUInt32());
			}
			else
			{
				instruction.SetCode(code16);
				instruction.SetOp0Kind(OpKind::Immediate16);
				instruction.SetInternalImmediate16(decoder->ReadUInt16());
			}
		}
	}

	OpCodeHandler_Gv_Ma::OpCodeHandler_Gv_Ma(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Gv_Ma::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		assert(state.mod != 3);
		instruction.SetOp1Kind(OpKind::Memory);
		decoder->ReadOpMem(instruction);
	}

	OpCodeHandler_RvMw_Gw::OpCodeHandler_RvMw_Gw(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_RvMw_Gw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register baseReg;
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
			baseReg = Register::EAX;
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
			baseReg = Register::AX;
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
	}

	OpCodeHandler_Gv_Ev_Ib::OpCodeHandler_Gv_Ev_Ib(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if (state.operandSize == OpSize::Size32)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
			instruction.SetCode(code32);
			instruction.SetOp2Kind(OpKind::Immediate8to32);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
			instruction.SetCode(code64);
			instruction.SetOp2Kind(OpKind::Immediate8to64);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
		else
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
			instruction.SetCode(code16);
			instruction.SetOp2Kind(OpKind::Immediate8to16);
			instruction.SetInternalImmediate8(decoder->ReadByte());
		}
	}

	OpCodeHandler_Gv_Ev_Ib_REX::OpCodeHandler_Gv_Ev_Ib_REX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev_Ib_REX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		assert(state.mod == 3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Gv_Ev_32_64::OpCodeHandler_Gv_Ev_32_64(Code code32, Code code64, bool allowReg, bool allowMem)
	{
		this->code32 = code32;
		this->code64 = code64;
		disallowMem = allowMem ? 0 : std::numeric_limits<std::uint32_t>::max();
		disallowReg = allowReg ? 0 : std::numeric_limits<std::uint32_t>::max();
	}

	void OpCodeHandler_Gv_Ev_32_64::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register baseReg;
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			baseReg = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			baseReg = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + baseReg));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
			if ((disallowReg & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			if ((disallowMem & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
	}

	OpCodeHandler_Gv_Ev_Iz::OpCodeHandler_Gv_Ev_Iz(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev_Iz::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
			instruction.SetOp2Kind(OpKind::Immediate32);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
			instruction.SetOp2Kind(OpKind::Immediate32to64);
			instruction.SetImmediate32(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
			instruction.SetOp2Kind(OpKind::Immediate16);
			instruction.SetInternalImmediate16(decoder->ReadUInt16());
		}
	}

	OpCodeHandler_Yb_Reg::OpCodeHandler_Yb_Reg(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Yb_Reg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(reg);
	}

	OpCodeHandler_Yv_Reg::OpCodeHandler_Yv_Reg(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Yv_Reg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::EAX);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::RAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::AX);
		}
	}

	OpCodeHandler_Yv_Reg2::OpCodeHandler_Yv_Reg2(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Yv_Reg2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
		}
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::DX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::DX);
		}
	}

	OpCodeHandler_Reg_Xb::OpCodeHandler_Reg_Xb(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Reg_Xb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else
		{
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
	}

	OpCodeHandler_Reg_Xv::OpCodeHandler_Reg_Xv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Reg_Xv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else
		{
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::EAX);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::RAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::AX);
		}
	}

	OpCodeHandler_Reg_Xv2::OpCodeHandler_Reg_Xv2(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Reg_Xv2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else
		{
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::DX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::DX);
		}
	}

	OpCodeHandler_Reg_Yb::OpCodeHandler_Reg_Yb(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Reg_Yb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
	}

	OpCodeHandler_Reg_Yv::OpCodeHandler_Reg_Yv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Reg_Yv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::EAX);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::RAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::AX);
		}
	}

	OpCodeHandler_Yb_Xb::OpCodeHandler_Yb_Xb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Yb_Xb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
	}

	OpCodeHandler_Yv_Xv::OpCodeHandler_Yv_Xv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Yv_Xv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
	}

	OpCodeHandler_Xb_Yb::OpCodeHandler_Xb_Yb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Xb_Yb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemorySegRSI);
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemorySegESI);
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemorySegSI);
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
	}

	OpCodeHandler_Xv_Yv::OpCodeHandler_Xv_Yv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Xv_Yv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetOp0Kind(OpKind::MemorySegRSI);
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetOp0Kind(OpKind::MemorySegESI);
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else
		{
			instruction.SetOp0Kind(OpKind::MemorySegSI);
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
	}

	OpCodeHandler_Ev_Sw::OpCodeHandler_Ev_Sw(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_Sw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(decoder->ReadOpSegReg());
	}

	OpCodeHandler_M_Sw::OpCodeHandler_M_Sw(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_M_Sw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(decoder->ReadOpSegReg());
	}

	OpCodeHandler_Gv_M::OpCodeHandler_Gv_M(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_M::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Sw_Ev::OpCodeHandler_Sw_Ev(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Sw_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code16);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		auto sreg = decoder->ReadOpSegReg();
		if (decoder->invalidCheckMask != 0 && sreg == Register::CS)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp0Register(sreg);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::EAX));
			}
			else if (state.operandSize == OpSize::Size64)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Sw_M::OpCodeHandler_Sw_M(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Sw_M::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(decoder->ReadOpSegReg());
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ap::OpCodeHandler_Ap(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Ap::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
		}
		else
		{
			instruction.SetCode(code16);
		}
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetOp0Kind(OpKind::FarBranch32);
			instruction.SetFarBranch32(decoder->ReadUInt32());
		}
		else
		{
			instruction.SetOp0Kind(OpKind::FarBranch16);
			instruction.SetInternalFarBranch16(decoder->ReadUInt16());
		}
		instruction.SetInternalFarBranchSelector(decoder->ReadUInt16());
	}

	OpCodeHandler_Reg_Ob::OpCodeHandler_Reg_Ob(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Reg_Ob::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(reg);
		decoder->displIndex = state.instructionLength;
		if (state.addressSize == OpSize::Size64)
		{
			instruction.InternalSetMemoryDisplSize(4);
			state.flags |= StateFlags::Addr64;
			instruction.SetMemoryDisplacement64(decoder->ReadUInt64());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.InternalSetMemoryDisplSize(3);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt32());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
		else
		{
			instruction.InternalSetMemoryDisplSize(2);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt16());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
	}

	OpCodeHandler_Ob_Reg::OpCodeHandler_Ob_Reg(Code code, Register reg)
	{
		this->code = code;
		this->reg = reg;
	}

	void OpCodeHandler_Ob_Reg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		decoder->displIndex = state.instructionLength;
		if (state.addressSize == OpSize::Size64)
		{
			instruction.InternalSetMemoryDisplSize(4);
			state.flags |= StateFlags::Addr64;
			instruction.SetMemoryDisplacement64(decoder->ReadUInt64());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.InternalSetMemoryDisplSize(3);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt32());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		else
		{
			instruction.InternalSetMemoryDisplSize(2);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt16());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(reg);
	}

	OpCodeHandler_Reg_Ov::OpCodeHandler_Reg_Ov(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Reg_Ov::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		decoder->displIndex = state.instructionLength;
		if (state.addressSize == OpSize::Size64)
		{
			instruction.InternalSetMemoryDisplSize(4);
			state.flags |= StateFlags::Addr64;
			instruction.SetMemoryDisplacement64(decoder->ReadUInt64());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.InternalSetMemoryDisplSize(3);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt32());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
		else
		{
			instruction.InternalSetMemoryDisplSize(2);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt16());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp1Kind(OpKind::Memory);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::EAX);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::RAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::AX);
		}
	}

	OpCodeHandler_Ov_Reg::OpCodeHandler_Ov_Reg(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ov_Reg::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		decoder->displIndex = state.instructionLength;
		if (state.addressSize == OpSize::Size64)
		{
			instruction.InternalSetMemoryDisplSize(4);
			state.flags |= StateFlags::Addr64;
			instruction.SetMemoryDisplacement64(decoder->ReadUInt64());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.InternalSetMemoryDisplSize(3);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt32());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		else
		{
			instruction.InternalSetMemoryDisplSize(2);
			instruction.SetMemoryDisplacement64(decoder->ReadUInt16());
			//instruction.InternalMemoryIndexScale = 0;
			//instruction.InternalMemoryBase = Register.None;
			//instruction.InternalMemoryIndex = Register.None;
			instruction.SetOp0Kind(OpKind::Memory);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::EAX);
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::RAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::AX);
		}
	}

	OpCodeHandler_BranchIw::OpCodeHandler_BranchIw(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_BranchIw::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		instruction.SetOp0Kind(OpKind::Immediate16);
		instruction.SetInternalImmediate16(decoder->ReadUInt16());
	}

	OpCodeHandler_BranchSimple::OpCodeHandler_BranchSimple(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_BranchSimple::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if ((decoder->options & DecoderOptions::AMD) == 0 || decoder->state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (decoder->state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
	}

	OpCodeHandler_Iw_Ib::OpCodeHandler_Iw_Ib(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Iw_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (decoder->is64bMode)
		{
			if (state.operandSize != OpSize::Size16)
			{
				instruction.SetCode(code64);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		else
		{
			if (state.operandSize == OpSize::Size32)
			{
				instruction.SetCode(code32);
			}
			else
			{
				instruction.SetCode(code16);
			}
		}
		instruction.SetOp0Kind(OpKind::Immediate16);
		instruction.SetInternalImmediate16(decoder->ReadUInt16());
		instruction.SetOp1Kind(OpKind::Immediate8_2nd);
		instruction.SetInternalImmediate8_2nd(decoder->ReadByte());
	}

	OpCodeHandler_Reg_Ib2::OpCodeHandler_Reg_Ib2(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Reg_Ib2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			instruction.SetOp0Register(Register::EAX);
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp0Register(Register::AX);
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_IbReg2::OpCodeHandler_IbReg2(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_IbReg2::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetOp0Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			instruction.SetOp1Register(Register::EAX);
		}
		else
		{
			instruction.SetCode(code16);
			instruction.SetOp1Register(Register::AX);
		}
	}

	OpCodeHandler_eAX_DX::OpCodeHandler_eAX_DX(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_eAX_DX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::EAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register(Register::AX);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::DX);
	}

	OpCodeHandler_DX_eAX::OpCodeHandler_DX_eAX(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_DX_eAX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::DX);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::EAX);
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register(Register::AX);
		}
	}

	OpCodeHandler_Eb_Ib::OpCodeHandler_Eb_Ib(Code code)
	{
		this->code = code;
	}

	OpCodeHandler_Eb_Ib::OpCodeHandler_Eb_Ib(Code code, HandlerFlags flags)
	{
		this->code = code;
		this->flags = flags;
	}

	void OpCodeHandler_Eb_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Eb_1::OpCodeHandler_Eb_1(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Eb_1::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(1);
		state.flags |= StateFlags::NoImm;
	}

	OpCodeHandler_Eb_CL::OpCodeHandler_Eb_CL(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Eb_CL::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::CL);
	}

	OpCodeHandler_Eb::OpCodeHandler_Eb(Code code)
	{
		this->code = code;
	}

	OpCodeHandler_Eb::OpCodeHandler_Eb(Code code, HandlerFlags flags)
	{
		this->code = code;
		this->flags = flags;
	}

	void OpCodeHandler_Eb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
	}

	OpCodeHandler_Eb_Gb::OpCodeHandler_Eb_Gb(Code code)
	{
		this->code = code;
	}

	OpCodeHandler_Eb_Gb::OpCodeHandler_Eb_Gb(Code code, HandlerFlags flags)
	{
		this->code = code;
		this->flags = flags;
	}

	void OpCodeHandler_Eb_Gb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		std::uint32_t index;
		if (state.mod == 3)
		{
			index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
		}
		index = state.reg + state.extraRegisterBase;
		if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
		{
			index += 4;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
	}

	OpCodeHandler_Gb_Eb::OpCodeHandler_Gb_Eb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Gb_Eb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		std::uint32_t index = state.reg + state.extraRegisterBase;
		if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
		{
			index += 4;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		if (state.mod == 3)
		{
			index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_M::OpCodeHandler_M(Code codeW0, Code codeW1)
	{
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	OpCodeHandler_M::OpCodeHandler_M(Code codeW0)
	{
		this->codeW0 = codeW0;
		codeW1 = codeW0;
	}

	void OpCodeHandler_M::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(codeW1);
		}
		else
		{
			instruction.SetCode(codeW0);
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_M_REXW::OpCodeHandler_M_REXW(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	OpCodeHandler_M_REXW::OpCodeHandler_M_REXW(Code code32, Code code64, HandlerFlags flags32, HandlerFlags flags64)
	{
		this->code32 = code32;
		this->code64 = code64;
		this->flags32 = flags32;
		this->flags64 = flags64;
	}

	void OpCodeHandler_M_REXW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			auto flags = (state.flags & StateFlags::W) != 0 ? flags64 : flags32;
			if ((flags & (HandlerFlags::Xacquire | HandlerFlags::Xrelease)) != 0)
			{
				decoder->SetXacquireXrelease(instruction);
			}
			Static::Assert(static_cast<std::int32_t>(HandlerFlags::Lock) == 8 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(StateFlags::AllowLock) == 0x00002000 ? 0 : -1);
			state.flags |= static_cast<StateFlags>(static_cast<std::uint32_t>(flags & HandlerFlags::Lock) << (13 - 3));
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_MemBx::OpCodeHandler_MemBx(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_MemBx::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		//instruction.MemoryDisplacement64 = 0;
		//instruction.InternalMemoryIndexScale = 0;
		//instruction.InternalSetMemoryDisplSize(0);
		if (state.addressSize == OpSize::Size64)
		{
			instruction.SetInternalMemoryBase(Register::RBX);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			instruction.SetInternalMemoryBase(Register::EBX);
		}
		else
		{
			instruction.SetInternalMemoryBase(Register::BX);
		}
		instruction.SetInternalMemoryIndex(Register::AL);
		instruction.SetOp0Kind(OpKind::Memory);
	}

	OpCodeHandler_VW::OpCodeHandler_VW(Code codeR, Code codeM)
	{
		this->codeR = codeR;
		this->codeM = codeM;
	}

	OpCodeHandler_VW::OpCodeHandler_VW(Code code)
	{
		codeR = code;
		codeM = code;
	}

	void OpCodeHandler_VW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			instruction.SetCode(codeR);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			instruction.SetCode(codeM);
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_WV::OpCodeHandler_WV(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_WV::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
	}

	OpCodeHandler_rDI_VX_RX::OpCodeHandler_rDI_VX_RX(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_rDI_VX_RX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
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
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_rDI_P_N::OpCodeHandler_rDI_P_N(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_rDI_P_N::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
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
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op2Kind = OpKind.Register;
			instruction.SetOp2Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_VM::OpCodeHandler_VM(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_VM::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_MV::OpCodeHandler_MV(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_MV::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
	}

	OpCodeHandler_VQ::OpCodeHandler_VQ(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_VQ::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_P_Q::OpCodeHandler_P_Q(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_P_Q::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Q_P::OpCodeHandler_Q_P(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Q_P::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
	}

	OpCodeHandler_MP::OpCodeHandler_MP(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_MP::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
	}

	OpCodeHandler_P_Q_Ib::OpCodeHandler_P_Q_Ib(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_P_Q_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_P_W::OpCodeHandler_P_W(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_P_W::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_P_R::OpCodeHandler_P_R(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_P_R::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_P_Ev::OpCodeHandler_P_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_P_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_P_Ev_Ib::OpCodeHandler_P_Ev_Ib(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_P_Ev_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + gpr));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Ev_P::OpCodeHandler_Ev_P(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_P::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::MM0));
	}

	OpCodeHandler_Gv_W::OpCodeHandler_Gv_W(Code codeW0, Code codeW1)
	{
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	void OpCodeHandler_Gv_W::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
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
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_V_Ev::OpCodeHandler_V_Ev(Code codeW0, Code codeW1)
	{
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	void OpCodeHandler_V_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if (state.operandSize != OpSize::Size64)
		{
			instruction.SetCode(codeW0);
			gpr = Register::EAX;
		}
		else
		{
			instruction.SetCode(codeW1);
			gpr = Register::RAX;
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
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_VWIb::OpCodeHandler_VWIb(Code code)
	{
		codeW0 = code;
		codeW1 = code;
	}

	OpCodeHandler_VWIb::OpCodeHandler_VWIb(Code codeW0, Code codeW1)
	{
		this->codeW0 = codeW0;
		this->codeW1 = codeW1;
	}

	void OpCodeHandler_VWIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(codeW1);
		}
		else
		{
			instruction.SetCode(codeW0);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_VRIbIb::OpCodeHandler_VRIbIb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_VRIbIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
		instruction.SetOp3Kind(OpKind::Immediate8_2nd);
		instruction.SetInternalImmediate8_2nd(decoder->ReadByte());
	}

	OpCodeHandler_RIbIb::OpCodeHandler_RIbIb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_RIbIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
		instruction.SetOp2Kind(OpKind::Immediate8_2nd);
		instruction.SetInternalImmediate8_2nd(decoder->ReadByte());
	}

	OpCodeHandler_RIb::OpCodeHandler_RIb(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_RIb::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp1Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Ed_V_Ib::OpCodeHandler_Ed_V_Ib(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ed_V_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_VX_Ev::OpCodeHandler_VX_Ev(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_VX_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ev_VX::OpCodeHandler_Ev_VX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_VX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
	}

	OpCodeHandler_VX_E_Ib::OpCodeHandler_VX_E_Ib(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_VX_E_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Gv_RX::OpCodeHandler_Gv_RX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_RX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::XMM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_B_MIB::OpCodeHandler_B_MIB(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_B_MIB::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.reg > 3 || (state.extraRegisterBase & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::BND0));
		assert(state.mod != 3);
		instruction.SetOp1Kind(OpKind::Memory);
		decoder->ReadOpMem_MPX(instruction);
		// It can't be EIP since if it's MPX + 64-bit, the address size is always 64-bit
		if (decoder->invalidCheckMask != 0 && instruction.GetMemoryBase() == Register::RIP)
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_MIB_B::OpCodeHandler_MIB_B(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_MIB_B::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.reg > 3 || (state.extraRegisterBase & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetCode(code);
		assert(state.mod != 3);
		instruction.SetOp0Kind(OpKind::Memory);
		decoder->ReadOpMem_MPX(instruction);
		// It can't be EIP since if it's MPX + 64-bit, the address size is always 64-bit
		if (decoder->invalidCheckMask != 0 && instruction.GetMemoryBase() == Register::RIP)
		{
			decoder->SetInvalidInstruction();
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::BND0));
	}

	OpCodeHandler_B_BM::OpCodeHandler_B_BM(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_B_BM::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.reg > 3 || (state.extraRegisterBase & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::BND0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::BND0));
			if (state.rm > 3 || (state.extraBaseRegisterBase & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem_MPX(instruction);
		}
	}

	OpCodeHandler_BM_B::OpCodeHandler_BM_B(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_BM_B::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.reg > 3 || ((state.extraRegisterBase & decoder->invalidCheckMask) != 0))
		{
			decoder->SetInvalidInstruction();
		}
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.rm) + Register::BND0));
			if (state.rm > 3 || (state.extraBaseRegisterBase & decoder->invalidCheckMask) != 0)
			{
				decoder->SetInvalidInstruction();
			}
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem_MPX(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg) + Register::BND0));
	}

	OpCodeHandler_B_Ev::OpCodeHandler_B_Ev(Code code32, Code code64, bool supportsRipRel)
	{
		this->code32 = code32;
		this->code64 = code64;
		ripRelMask = supportsRipRel ? 0 : std::numeric_limits<std::uint32_t>::max();
	}

	void OpCodeHandler_B_Ev::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.reg > 3 || (state.extraRegisterBase & decoder->invalidCheckMask) != 0)
		{
			decoder->SetInvalidInstruction();
		}
		Register baseReg;
		if (decoder->is64bMode)
		{
			instruction.SetCode(code64);
			baseReg = Register::RAX;
		}
		else
		{
			instruction.SetCode(code32);
			baseReg = Register::EAX;
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg) + Register::BND0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + baseReg));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem_MPX(instruction);
			// It can't be EIP since if it's MPX + 64-bit, the address size is always 64-bit
			if ((ripRelMask & decoder->invalidCheckMask) != 0 && instruction.GetMemoryBase() == Register::RIP)
			{
				decoder->SetInvalidInstruction();
			}
		}
	}

	OpCodeHandler_Mv_Gv_REXW::OpCodeHandler_Mv_Gv_REXW(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Mv_Gv_REXW::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
	}

	OpCodeHandler_Gv_N_Ib_REX::OpCodeHandler_Gv_N_Ib_REX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_N_Ib_REX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Gv_N::OpCodeHandler_Gv_N(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_N::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
		}
		else
		{
			instruction.SetCode(code32);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_VN::OpCodeHandler_VN(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_VN::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm) + Register::MM0));
		}
		else
		{
			decoder->SetInvalidInstruction();
		}
	}

	OpCodeHandler_Gv_Mv::OpCodeHandler_Gv_Mv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Mv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Mv_Gv::OpCodeHandler_Mv_Gv(Code code16, Code code32, Code code64)
	{
		this->code16 = code16;
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Mv_Gv::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.mod == 3)
		{
			decoder->SetInvalidInstruction();
		}
		else
		{
			instruction.SetOp0Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
		if (state.operandSize == OpSize::Size32)
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		else if (state.operandSize == OpSize::Size64)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code16);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::AX));
		}
	}

	OpCodeHandler_Gv_Eb_REX::OpCodeHandler_Gv_Eb_REX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Eb_REX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			std::uint32_t index = state.rm + state.extraBaseRegisterBase;
			if ((state.flags & StateFlags::HasRex) != 0 && index >= 4)
			{
				index += 4;
			}
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(index) + Register::AL));
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Gv_Ev_REX::OpCodeHandler_Gv_Ev_REX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Gv_Ev_REX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op0Kind = OpKind.Register;
			instruction.SetOp0Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
		if (state.mod == 3)
		{
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			if ((state.flags & StateFlags::W) != 0)
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::RAX));
			}
			else
			{
				instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.rm + state.extraBaseRegisterBase) + Register::EAX));
			}
		}
		else
		{
			instruction.SetOp1Kind(OpKind::Memory);
			decoder->ReadOpMem(instruction);
		}
	}

	OpCodeHandler_Ev_Gv_REX::OpCodeHandler_Ev_Gv_REX(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_Ev_Gv_REX::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		assert(state.mod != 3);
		instruction.SetOp0Kind(OpKind::Memory);
		decoder->ReadOpMem(instruction);
		if ((state.flags & StateFlags::W) != 0)
		{
			instruction.SetCode(code64);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::RAX));
		}
		else
		{
			instruction.SetCode(code32);
			Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
			//instruction.Op1Kind = OpKind.Register;
			instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::EAX));
		}
	}

	OpCodeHandler_GvM_VX_Ib::OpCodeHandler_GvM_VX_Ib(Code code32, Code code64)
	{
		this->code32 = code32;
		this->code64 = code64;
	}

	void OpCodeHandler_GvM_VX_Ib::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		Register gpr;
		if ((state.flags & StateFlags::W) != 0)
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
			decoder->ReadOpMem(instruction);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register((Register)(static_cast<std::int32_t>(state.reg + state.extraRegisterBase) + Register::XMM0));
		instruction.SetOp2Kind(OpKind::Immediate8);
		instruction.SetInternalImmediate8(decoder->ReadByte());
	}

	OpCodeHandler_Wbinvd::OpCodeHandler_Wbinvd()
	{
	}

	void OpCodeHandler_Wbinvd::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		if ((decoder->options & DecoderOptions::NoWbnoinvd) != 0 || decoder->state.mandatoryPrefix != MandatoryPrefixByte::PF3)
		{
			instruction.SetCode(Code::Wbinvd);
		}
		else
		{
			decoder->ClearMandatoryPrefixF3(instruction);
			instruction.SetCode(Code::Wbnoinvd);
		}
	}
}
