// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "OpCodeHandlers.h"
#include "../Code.g.h"
#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../EncodingKind.g.h"
#include "../OpKind.g.h"
#include "../Static.h"
#include "../Register.g.h"
#include <cassert>

namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler_ST_STi final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_ST_STi(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_STi_ST final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_STi_ST(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_STi final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_STi(Code code);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Mf final : public OpCodeHandlerModRM
	{
	private:
		Code code16 = static_cast<Code>(0);
		Code code32 = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_Mf(Code code);
		constexpr OpCodeHandler_Mf(Code code16, Code code32);
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
}

namespace Iced::Intel::DecoderInternal
{
	constexpr OpCodeHandler_ST_STi::OpCodeHandler_ST_STi(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_ST_STi::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(Register::ST0);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(((Register)(Register::ST0 + static_cast<std::int32_t>(decoder.state.rm))));
	}

	constexpr OpCodeHandler_STi_ST::OpCodeHandler_STi_ST(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_STi_ST::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(Register::ST0 + static_cast<std::int32_t>(decoder.state.rm)));
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(Register::ST0);
	}

	constexpr OpCodeHandler_STi::OpCodeHandler_STi(Code code)
	{
		this->code = code;
	}

	inline void OpCodeHandler_STi::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::Legacy);
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register((Register)(Register::ST0 + static_cast<std::int32_t>(decoder.state.rm)));
	}

	constexpr OpCodeHandler_Mf::OpCodeHandler_Mf(Code code)
	{
		code16 = code;
		code32 = code;
	}

	constexpr OpCodeHandler_Mf::OpCodeHandler_Mf(Code code16, Code code32)
	{
		this->code16 = code16;
		this->code32 = code32;
	}

	inline void OpCodeHandler_Mf::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		assert(state.GetEncoding() == EncodingKind::Legacy);
		if (state.operandSize != OpSize::Size16)
		{
			instruction.SetCode(code32);
		}
		else
		{
			instruction.SetCode(code16);
		}
		assert(state.mod != 3);
		instruction.SetOp0Kind(OpKind::Memory);
		decoder.ReadOpMem(instruction);
	}
}
