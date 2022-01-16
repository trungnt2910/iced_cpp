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

#pragma once

#include "../Encoder.h"
#include "../Iced.Intel.Instruction.h"
#include "Enums.h"
#include "../CodeSize.g.h"
#include "../Decoder.h"
#include "OpHandlers.h"
#include "../Code.g.h"
#include "../TupleType.g.h"
#include <string>
#include <vector>
#include <limits>
#include <optional>
#include <format>
#include <csharp/exceptionhelper.h>
#include <cassert>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel::EncoderInternal { class OpCodeHandler; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	using TryConvertToDisp8N = std::function<bool(Encoder* encoder, OpCodeHandler* handler, Instruction const instruction, std::int32_t displ, std::int8_t& compressedValue)>;
	class OpCodeHandler
	{
	public:
		std::uint32_t OpCode = 0;
		bool Is2ByteOpCode = false;
		std::int32_t GroupIndex = 0;
		std::int32_t RmGroupIndex = 0;
		bool IsDeclareData = false;
		EncFlags3 EncFlags3 = static_cast<EncFlags3>(0);
		CodeSize OpSize = static_cast<CodeSize>(0);
		CodeSize AddrSize = static_cast<CodeSize>(0);
		std::optional<TryConvertToDisp8N> TryConvertToDisp8N;
		std::vector<Op*> Operands;
	protected:
		OpCodeHandler(EncFlags2 encFlags2, EncFlags3 encFlags3, bool isDeclareData, std::optional<TryConvertToDisp8N>& tryConvertToDisp8N, std::vector<Op*>& operands);
		static std::uint32_t GetOpCode(EncFlags2 encFlags2);
	public:
		virtual void Encode(Encoder* encoder, Instruction const instruction) = 0;
	};
	class InvalidHandler final : public OpCodeHandler
	{
	public:
		static const std::string ERROR_MESSAGE;
		InvalidHandler();
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class DeclareDataHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::int32_t elemLength = 0;
		/* readonly */
		std::int32_t maxLength = 0;
	public:
		DeclareDataHandler(Code code);
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class LegacyHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::uint32_t tableByte1 = 0, tableByte2 = 0;
		/* readonly */
		std::uint32_t mandatoryPrefix = 0;
		static std::vector<Op*> CreateOps(EncFlags1 encFlags1);
	public:
		LegacyHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3);
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class VexHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t lastByte = 0;
		/* readonly */
		std::uint32_t mask_W_L = 0;
		/* readonly */
		std::uint32_t mask_L = 0;
		/* readonly */
		std::uint32_t W1 = 0;
		static std::vector<Op*> CreateOps(EncFlags1 encFlags1);
	public:
		VexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3);
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class XopHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t lastByte = 0;
		static std::vector<Op*> CreateOps(EncFlags1 encFlags1);
	public:
		XopHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3);
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class EvexHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		WBit wbit = static_cast<WBit>(0);
		/* readonly */
		TupleType tupleType = static_cast<TupleType>(0);
		/* readonly */
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t p1Bits = 0;
		/* readonly */
		std::uint32_t llBits = 0;
		/* readonly */
		std::uint32_t mask_W = 0;
		/* readonly */
		std::uint32_t mask_LL = 0;
		static std::vector<Op*> CreateOps(EncFlags1 encFlags1);
		static TryConvertToDisp8N tryConvertToDisp8N;
	public:
		EvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3);
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			static bool TryConvertToDisp8N(Encoder* encoder, OpCodeHandler* handler, Instruction const instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	public:
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class MvexHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		WBit wbit = static_cast<WBit>(0);
		/* readonly */
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t p1Bits = 0;
		/* readonly */
		std::uint32_t mask_W = 0;
		static std::vector<Op*> CreateOps(EncFlags1 encFlags1);
		static TryConvertToDisp8N tryConvertToDisp8N;
	public:
		MvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3);
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			static bool TryConvertToDisp8N(Encoder* encoder, OpCodeHandler* handler, Instruction const instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	public:
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
	class D3nowHandler final : public OpCodeHandler
	{
	private:
		static std::vector<Op*> operands;
		/* readonly */
		std::uint32_t immediate = 0;
	public:
		D3nowHandler(EncFlags2 encFlags2, EncFlags3 encFlags3);
		void Encode(Encoder* encoder, Instruction const instruction) override;
	};
}
