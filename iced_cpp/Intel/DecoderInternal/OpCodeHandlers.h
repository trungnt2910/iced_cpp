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

#include "../Decoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../Code.g.h"
#include "../DecoderOptions.g.h"
#include <vector>
#include <stdexcept>
#include <csharp/exceptionhelper.h>
#include <cassert>

namespace Iced::Intel { class Decoder; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler
	{
	public:
		bool HasModRM = false;
	protected:
		OpCodeHandler();
		OpCodeHandler(bool hasModRM);
	public:
		virtual void Decode(Decoder* decoder, Instruction& instruction) = 0;
	};
	class OpCodeHandlerModRM : public OpCodeHandler
	{
	protected:
		OpCodeHandlerModRM();
	};
	class OpCodeHandler_Invalid final : public OpCodeHandlerModRM
	{
	public:
		static std::shared_ptr<OpCodeHandler_Invalid> Instance;
	private:
		OpCodeHandler_Invalid();
	public:
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Invalid_NoModRM final : public OpCodeHandler
	{
	public:
		static std::shared_ptr<OpCodeHandler_Invalid_NoModRM> Instance;
	private:
		OpCodeHandler_Invalid_NoModRM();
	public:
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple final : public OpCodeHandler
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Simple_ModRM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		Code code = static_cast<Code>(0);
	public:
		OpCodeHandler_Simple_ModRM(Code code);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Group8x8 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> tableLow;
		/* readonly */
		std::vector<std::shared_ptr<OpCodeHandler>> tableHigh;
	public:
		OpCodeHandler_Group8x8(const std::vector<std::shared_ptr<OpCodeHandler>>& tableLow, const std::vector<std::shared_ptr<OpCodeHandler>>& tableHigh);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Group8x64 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> tableLow;
		/* readonly */
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: OpCodeHandler?[] tableHigh;
		std::vector<std::shared_ptr<OpCodeHandler>> tableHigh;
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public OpCodeHandler_Group8x64(OpCodeHandler[] tableLow, OpCodeHandler?[] tableHigh)
		OpCodeHandler_Group8x64(const std::vector<std::shared_ptr<OpCodeHandler>>& tableLow, const std::vector<std::shared_ptr<OpCodeHandler>>& tableHigh);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Group final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> groupHandlers;
	public:
		OpCodeHandler_Group(const std::vector<std::shared_ptr<OpCodeHandler>>& groupHandlers);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_AnotherTable final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> otherTable;
	public:
		OpCodeHandler_AnotherTable(const std::vector<std::shared_ptr<OpCodeHandler>>& otherTable);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix2 final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_MandatoryPrefix2(std::shared_ptr<OpCodeHandler> handler);
		OpCodeHandler_MandatoryPrefix2(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_MandatoryPrefix2_NoModRM final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::vector<std::shared_ptr<OpCodeHandler>> handlers;
	public:
		OpCodeHandler_MandatoryPrefix2_NoModRM(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_W final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handlerW0;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handlerW1;
	public:
		OpCodeHandler_W(std::shared_ptr<OpCodeHandler> handlerW0, std::shared_ptr<OpCodeHandler> handlerW1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Bitness final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handler1632;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handler64;
	public:
		OpCodeHandler_Bitness(std::shared_ptr<OpCodeHandler> handler1632, std::shared_ptr<OpCodeHandler> handler64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Bitness_DontReadModRM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> handler1632;
		/* readonly */
		std::shared_ptr<OpCodeHandler> handler64;
	public:
		OpCodeHandler_Bitness_DontReadModRM(std::shared_ptr<OpCodeHandler> handler1632, std::shared_ptr<OpCodeHandler> handler64);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_RM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> reg;
		/* readonly */
		std::shared_ptr<OpCodeHandler> mem;
	public:
		OpCodeHandler_RM(std::shared_ptr<OpCodeHandler> reg, std::shared_ptr<OpCodeHandler> mem);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	/* readonly */
	class HandlerOptions
	{
	public:
		std::shared_ptr<OpCodeHandler> handler;
		DecoderOptions options = static_cast<DecoderOptions>(0);
		HandlerOptions(std::shared_ptr<OpCodeHandler> handler, DecoderOptions options);

		HandlerOptions() = default;
	};
	class OpCodeHandler_Options1632 final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> defaultHandler;
		/* readonly */
		std::vector<HandlerOptions> infos;
		/* readonly */
		DecoderOptions infoOptions = static_cast<DecoderOptions>(0);
	public:
		OpCodeHandler_Options1632(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1);
		OpCodeHandler_Options1632(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1, std::shared_ptr<OpCodeHandler> handler2, DecoderOptions options2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Options final : public OpCodeHandler
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> defaultHandler;
		/* readonly */
		std::vector<HandlerOptions> infos;
		/* readonly */
		DecoderOptions infoOptions = static_cast<DecoderOptions>(0);
	public:
		OpCodeHandler_Options(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1);
		OpCodeHandler_Options(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1, std::shared_ptr<OpCodeHandler> handler2, DecoderOptions options2);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
	class OpCodeHandler_Options_DontReadModRM final : public OpCodeHandlerModRM
	{
		/* readonly */
	private:
		std::shared_ptr<OpCodeHandler> defaultHandler;
		/* readonly */
		std::vector<HandlerOptions> infos;
	public:
		OpCodeHandler_Options_DontReadModRM(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1);
		void Decode(Decoder* decoder, Instruction& instruction) override;
	};
}
