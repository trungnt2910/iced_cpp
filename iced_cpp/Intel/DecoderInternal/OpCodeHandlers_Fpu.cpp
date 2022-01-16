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

#include "OpCodeHandlers_Fpu.h"
#include "../EncodingKind.g.h"
#include "../OpKind.g.h"
#include "../Static.h"
#include "../Register.g.h"

namespace Iced::Intel::DecoderInternal
{

	OpCodeHandler_ST_STi::OpCodeHandler_ST_STi(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_ST_STi::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::ST0);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::ST0 + static_cast<std::int32_t>(decoder->state.rm));
	}

	OpCodeHandler_STi_ST::OpCodeHandler_STi_ST(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_STi_ST::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::ST0 + static_cast<std::int32_t>(decoder->state.rm));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::ST0);
	}

	OpCodeHandler_STi::OpCodeHandler_STi(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_STi::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::ST0 + static_cast<std::int32_t>(decoder->state.rm));
	}

	OpCodeHandler_Mf::OpCodeHandler_Mf(Code code)
	{
		code16 = code;
		code32 = code;
	}

	OpCodeHandler_Mf::OpCodeHandler_Mf(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	void OpCodeHandler_Mf::Decode(Decoder* decoder, Instruction& instruction)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var state = ref decoder.state;
		auto state = decoder->state;
		assert(state->Encoding == EncodingKind::Legacy);
		if (state->operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
		}
		else
		{
			instruction.SetCode(code16);
		}
		assert(state->mod != 3);
		instruction.SetOp0Kind(OpKind::Memory);
		decoder->ReadOpMem(instruction);
	}
}