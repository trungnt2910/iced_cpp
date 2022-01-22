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

#include "../Iced.Intel.Instruction.h"
#include "Enums.h"
#include "../CodeSize.g.h"
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
namespace Iced::Intel::EncoderInternal { class OpCodeHandler; class Op; }

namespace Iced::Intel { class Encoder; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	using TryConvertToDisp8N = std::function<bool(Encoder& encoder, std::shared_ptr<OpCodeHandler> handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)>;
	class OpCodeHandler
	{
	public:
		using TryConvertToDisp8N_ = TryConvertToDisp8N;
	public:
		std::uint32_t OpCode = 0;
		bool Is2ByteOpCode = false;
		std::int32_t GroupIndex = 0;
		std::int32_t RmGroupIndex = 0;
		bool IsDeclareData = false;
		enum EncFlags3 EncFlags3 = static_cast<enum EncFlags3>(0);
		CodeSize OpSize = static_cast<CodeSize>(0);
		CodeSize AddrSize = static_cast<CodeSize>(0);
		std::optional<TryConvertToDisp8N_> TryConvertToDisp8N;
		std::vector<std::shared_ptr<Op>> Operands;
	protected:
		OpCodeHandler(EncFlags2 encFlags2, enum EncFlags3 encFlags3, bool isDeclareData, const std::optional<TryConvertToDisp8N_>& tryConvertToDisp8N, const std::vector<std::shared_ptr<Op>>& operands);
		static std::uint32_t GetOpCode(EncFlags2 encFlags2);
	public:
		virtual void Encode(Encoder& encoder, const Instruction& instruction) = 0;
	};
	class InvalidHandler final : public OpCodeHandler
	{
	public:
		static const std::string ERROR_MESSAGE;
		InvalidHandler();
		void Encode(Encoder& encoder, const Instruction& instruction) override;
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
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
	class LegacyHandler final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::uint32_t tableByte1 = 0, tableByte2 = 0;
		/* readonly */
		std::uint32_t mandatoryPrefix = 0;
		static std::vector<std::shared_ptr<Op>> CreateOps(EncFlags1 encFlags1);
	public:
		LegacyHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3);
		void Encode(Encoder& encoder, const Instruction& instruction) override;
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
		static std::vector<std::shared_ptr<Op>> CreateOps(EncFlags1 encFlags1);
	public:
		VexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3);
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
	class XopHandler final : public OpCodeHandler
	{
	private:
		/* readonly */
	private:
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t lastByte = 0;
		static std::vector<std::shared_ptr<Op>> CreateOps(EncFlags1 encFlags1);
	public:
		XopHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3);
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
	class EvexHandler final : public OpCodeHandler
	{
	private:
		using TryConvertToDisp8N_ = ::Iced::Intel::EncoderInternal::TryConvertToDisp8N;
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
		static std::vector<std::shared_ptr<Op>> CreateOps(EncFlags1 encFlags1);
		static TryConvertToDisp8N_ tryConvertToDisp8N;
	public:
		EvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3);
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			static bool TryConvertToDisp8N(Encoder& encoder, std::shared_ptr<OpCodeHandler> handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	public:
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
	class MvexHandler final : public OpCodeHandler
	{
	private:
		using TryConvertToDisp8N = Iced::Intel::EncoderInternal::TryConvertToDisp8N;
		/* readonly */
	private:
		WBit wbit = static_cast<WBit>(0);
		/* readonly */
		std::uint32_t table = 0;
		/* readonly */
		std::uint32_t p1Bits = 0;
		/* readonly */
		std::uint32_t mask_W = 0;
		static std::vector<std::shared_ptr<Op>> CreateOps(EncFlags1 encFlags1);
		static TryConvertToDisp8N tryConvertToDisp8N;
	public:
		MvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3);
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			static bool TryConvertToDisp8N(Encoder& encoder, std::shared_ptr<OpCodeHandler> handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	public:
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
	class D3nowHandler final : public OpCodeHandler
	{
	private:
		using EncFlags3 = ::Iced::Intel::EncoderInternal::EncFlags3;
		using TryConvertToDisp8N = ::Iced::Intel::EncoderInternal::TryConvertToDisp8N;
	private:
		static std::vector<std::shared_ptr<Op>> operands;
		/* readonly */
		std::uint32_t immediate = 0;
	public:
		D3nowHandler(EncFlags2 encFlags2, EncFlags3 encFlags3);
		void Encode(Encoder& encoder, const Instruction& instruction) override;
	};
}
