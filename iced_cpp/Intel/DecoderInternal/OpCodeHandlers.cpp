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

#include "OpCodeHandlers.h"
#include "../MandatoryPrefixByte.g.h"
#include "../Static.h"
#include "../EncodingKind.g.h"

namespace Iced::Intel::DecoderInternal
{

	OpCodeHandler::OpCodeHandler()
	{
	}

	OpCodeHandler::OpCodeHandler(bool hasModRM)
	{
		HasModRM = hasModRM;
	}

	OpCodeHandlerModRM::OpCodeHandlerModRM() : OpCodeHandler(true)
	{
	}

	std::shared_ptr<OpCodeHandler_Invalid> OpCodeHandler_Invalid::Instance = OpCodeHandler_Invalid::GetInstance();

	std::shared_ptr<OpCodeHandler_Invalid> OpCodeHandler_Invalid::GetInstance()
	{
		static auto instance = std::shared_ptr<OpCodeHandler_Invalid>(new OpCodeHandler_Invalid);
		return instance;
	}

	OpCodeHandler_Invalid::OpCodeHandler_Invalid()
	{
	}

	void OpCodeHandler_Invalid::Decode(Decoder* decoder, Instruction& instruction)
	{
		decoder->SetInvalidInstruction();
	}

	std::shared_ptr<OpCodeHandler_Invalid_NoModRM> OpCodeHandler_Invalid_NoModRM::Instance = OpCodeHandler_Invalid_NoModRM::GetInstance();

	std::shared_ptr<OpCodeHandler_Invalid_NoModRM> OpCodeHandler_Invalid_NoModRM::GetInstance()
	{
		static auto instance = std::shared_ptr<OpCodeHandler_Invalid_NoModRM>(new OpCodeHandler_Invalid_NoModRM);
		return instance;
	}

	OpCodeHandler_Invalid_NoModRM::OpCodeHandler_Invalid_NoModRM()
	{
	}

	void OpCodeHandler_Invalid_NoModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		decoder->SetInvalidInstruction();
	}

	OpCodeHandler_Simple::OpCodeHandler_Simple(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Simple::Decode(Decoder* decoder, Instruction& instruction)
	{
		instruction.SetCode(code);
	}

	OpCodeHandler_Simple_ModRM::OpCodeHandler_Simple_ModRM(Code code)
	{
		this->code = code;
	}

	void OpCodeHandler_Simple_ModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		instruction.SetCode(code);
	}

	OpCodeHandler_Group8x8::OpCodeHandler_Group8x8(const std::vector<std::shared_ptr<OpCodeHandler>>& tableLow, const std::vector<std::shared_ptr<OpCodeHandler>>& tableHigh)
	{
		if (tableLow.size() != 8)
		{
			throw ArgumentOutOfRangeException("tableLow");
		}
		if (tableHigh.size() != 8)
		{
			throw ArgumentOutOfRangeException("tableHigh");
		}
		this->tableLow = tableLow;
		this->tableHigh = tableHigh;
	}

	void OpCodeHandler_Group8x8::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		std::shared_ptr<OpCodeHandler> handler;
		if (state.mod == 3)
		{
			handler = tableHigh[state.reg];
		}
		else
		{
			handler = tableLow[state.reg];
		}
		handler->Decode(decoder, instruction);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public OpCodeHandler_Group8x64(OpCodeHandler[] tableLow, OpCodeHandler?[] tableHigh)
	OpCodeHandler_Group8x64::OpCodeHandler_Group8x64(const std::vector<std::shared_ptr<OpCodeHandler>>& tableLow, const std::vector<std::shared_ptr<OpCodeHandler>>& tableHigh)
	{
		if (tableLow.size() != 8)
		{
			throw ArgumentOutOfRangeException("tableLow");
		}
		if (tableHigh.size() != 64)
		{
			throw ArgumentOutOfRangeException("tableHigh");
		}
		this->tableLow = tableLow;
		this->tableHigh = tableHigh;
	}

	void OpCodeHandler_Group8x64::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto& state = decoder->state;
		std::shared_ptr<OpCodeHandler> handler;
		if (state.mod == 3)
		{
			// A handler can be null in tableHigh, useful in 0F01 table and similar tables
			handler = (tableHigh[state.modrm & 0x3F] != nullptr) ? tableHigh[state.modrm & 0x3F] : tableLow[state.reg];
		}
		else
		{
			handler = tableLow[state.reg];
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_Group::OpCodeHandler_Group(const std::vector<std::shared_ptr<OpCodeHandler>>& groupHandlers)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.groupHandlers = groupHandlers ?? throw new ArgumentNullException(nameof(groupHandlers));
		this->groupHandlers = groupHandlers;
	}

	void OpCodeHandler_Group::Decode(Decoder* decoder, Instruction& instruction)
	{
		groupHandlers[decoder->state.reg]->Decode(decoder, instruction);
	}

	OpCodeHandler_AnotherTable::OpCodeHandler_AnotherTable(const std::vector<std::shared_ptr<OpCodeHandler>>& otherTable)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.otherTable = otherTable ?? throw new ArgumentNullException(nameof(otherTable));
		this->otherTable = otherTable;
	}

	void OpCodeHandler_AnotherTable::Decode(Decoder* decoder, Instruction& instruction)
	{
		decoder->DecodeTable(otherTable, instruction);
	}

	OpCodeHandler_MandatoryPrefix2::OpCodeHandler_MandatoryPrefix2(std::shared_ptr<OpCodeHandler> handler) : OpCodeHandler_MandatoryPrefix2(handler, OpCodeHandler_Invalid::GetInstance(), OpCodeHandler_Invalid::GetInstance(), OpCodeHandler_Invalid::GetInstance())
	{
	}

	OpCodeHandler_MandatoryPrefix2::OpCodeHandler_MandatoryPrefix2(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2)
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

	void OpCodeHandler_MandatoryPrefix2::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::VEX || decoder->state.GetEncoding() == EncodingKind::EVEX || decoder->state.GetEncoding() == EncodingKind::XOP || decoder->state.GetEncoding() == EncodingKind::MVEX);
		handlers[static_cast<std::int32_t>(decoder->state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	OpCodeHandler_MandatoryPrefix2_NoModRM::OpCodeHandler_MandatoryPrefix2_NoModRM(std::shared_ptr<OpCodeHandler> handler, std::shared_ptr<OpCodeHandler> handler66, std::shared_ptr<OpCodeHandler> handlerF3, std::shared_ptr<OpCodeHandler> handlerF2)
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

	void OpCodeHandler_MandatoryPrefix2_NoModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::VEX || decoder->state.GetEncoding() == EncodingKind::EVEX || decoder->state.GetEncoding() == EncodingKind::XOP || decoder->state.GetEncoding() == EncodingKind::MVEX);
		handlers[static_cast<std::int32_t>(decoder->state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	OpCodeHandler_W::OpCodeHandler_W(std::shared_ptr<OpCodeHandler> handlerW0, std::shared_ptr<OpCodeHandler> handlerW1)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerW0 = handlerW0 ?? throw new ArgumentNullException(nameof(handlerW0));
		this->handlerW0 = (handlerW0 != nullptr) ? handlerW0 : throw std::invalid_argument("handlerW0");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.handlerW1 = handlerW1 ?? throw new ArgumentNullException(nameof(handlerW1));
		this->handlerW1 = (handlerW1 != nullptr) ? handlerW1 : throw std::invalid_argument("handlerW1");
		assert(handlerW0->HasModRM == HasModRM);
		assert(handlerW1->HasModRM == HasModRM);
	}

	void OpCodeHandler_W::Decode(Decoder* decoder, Instruction& instruction)
	{
		assert(decoder->state.GetEncoding() == EncodingKind::VEX || decoder->state.GetEncoding() == EncodingKind::EVEX || decoder->state.GetEncoding() == EncodingKind::XOP || decoder->state.GetEncoding() == EncodingKind::MVEX);
		((decoder->state.flags & StateFlags::W) != 0 ? handlerW1 : handlerW0)->Decode(decoder, instruction);
	}

	OpCodeHandler_Bitness::OpCodeHandler_Bitness(std::shared_ptr<OpCodeHandler> handler1632, std::shared_ptr<OpCodeHandler> handler64)
	{
		this->handler1632 = handler1632;
		this->handler64 = handler64;
	}

	void OpCodeHandler_Bitness::Decode(Decoder* decoder, Instruction& instruction)
	{
		std::shared_ptr<OpCodeHandler> handler;
		if (decoder->is64bMode)
		{
			handler = handler64;
		}
		else
		{
			handler = handler1632;
		}
		if (handler->HasModRM)
		{
			decoder->ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_Bitness_DontReadModRM::OpCodeHandler_Bitness_DontReadModRM(std::shared_ptr<OpCodeHandler> handler1632, std::shared_ptr<OpCodeHandler> handler64)
	{
		this->handler1632 = handler1632;
		this->handler64 = handler64;
	}

	void OpCodeHandler_Bitness_DontReadModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		std::shared_ptr<OpCodeHandler> handler;
		if (decoder->is64bMode)
		{
			handler = handler64;
		}
		else
		{
			handler = handler1632;
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_RM::OpCodeHandler_RM(std::shared_ptr<OpCodeHandler> reg, std::shared_ptr<OpCodeHandler> mem)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.reg = reg ?? throw new ArgumentNullException(nameof(reg));
		this->reg = (reg != nullptr) ? reg : throw std::invalid_argument("reg");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.mem = mem ?? throw new ArgumentNullException(nameof(mem));
		this->mem = (mem != nullptr) ? mem : throw std::invalid_argument("mem");
	}

	void OpCodeHandler_RM::Decode(Decoder* decoder, Instruction& instruction)
	{
		(decoder->state.mod == 3 ? reg : mem)->Decode(decoder, instruction);
	}

	HandlerOptions::HandlerOptions(std::shared_ptr<OpCodeHandler> handler, DecoderOptions options)
	{
		this->handler = handler;
		this->options = options;
	}

	OpCodeHandler_Options1632::OpCodeHandler_Options1632(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.defaultHandler = defaultHandler ?? throw new ArgumentNullException(nameof(defaultHandler));
		this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
		infos = { HandlerOptions(handler1, options1) };
		infoOptions = options1;
	}

	OpCodeHandler_Options1632::OpCodeHandler_Options1632(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1, std::shared_ptr<OpCodeHandler> handler2, DecoderOptions options2)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.defaultHandler = defaultHandler ?? throw new ArgumentNullException(nameof(defaultHandler));
		this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: infos = new HandlerOptions[] { new HandlerOptions(handler1 ?? throw new ArgumentNullException(nameof(handler1)), options1), new HandlerOptions(handler2 ?? throw new ArgumentNullException(nameof(handler2)), options2)};
		infos = { HandlerOptions((handler1 != nullptr) ? handler1 : throw std::invalid_argument("handler1"), options1), HandlerOptions((handler2 != nullptr) ? handler2 : throw std::invalid_argument("handler2"), options2) };
		infoOptions = options1 | options2;
	}

	void OpCodeHandler_Options1632::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto handler = defaultHandler;
		auto options = decoder->options;
		if (!decoder->is64bMode && (decoder->options & infoOptions) != 0)
		{
			for (auto info : infos)
			{
				if ((options & info.options) != 0)
				{
					handler = info.handler;
					break;
				}
			}
		}
		if (handler->HasModRM)
		{
			decoder->ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_Options::OpCodeHandler_Options(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.defaultHandler = defaultHandler ?? throw new ArgumentNullException(nameof(defaultHandler));
		this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
		infos = { HandlerOptions(handler1, options1) };
		infoOptions = options1;
	}

	OpCodeHandler_Options::OpCodeHandler_Options(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1, std::shared_ptr<OpCodeHandler> handler2, DecoderOptions options2)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.defaultHandler = defaultHandler ?? throw new ArgumentNullException(nameof(defaultHandler));
		this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: infos = new HandlerOptions[] { new HandlerOptions(handler1 ?? throw new ArgumentNullException(nameof(handler1)), options1), new HandlerOptions(handler2 ?? throw new ArgumentNullException(nameof(handler2)), options2)};
		infos = { HandlerOptions((handler1 != nullptr) ? handler1 : throw std::invalid_argument("handler1"), options1), HandlerOptions((handler2 != nullptr) ? handler2 : throw std::invalid_argument("handler2"), options2) };
		infoOptions = options1 | options2;
	}

	void OpCodeHandler_Options::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto handler = defaultHandler;
		auto options = decoder->options;
		if ((decoder->options & infoOptions) != 0)
		{
			for (auto info : infos)
			{
				if ((options & info.options) != 0)
				{
					handler = info.handler;
					break;
				}
			}
		}
		if (handler->HasModRM)
		{
			decoder->ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	OpCodeHandler_Options_DontReadModRM::OpCodeHandler_Options_DontReadModRM(std::shared_ptr<OpCodeHandler> defaultHandler, std::shared_ptr<OpCodeHandler> handler1, DecoderOptions options1)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.defaultHandler = defaultHandler ?? throw new ArgumentNullException(nameof(defaultHandler));
		this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
		infos = { HandlerOptions(handler1, options1) };
	}

	void OpCodeHandler_Options_DontReadModRM::Decode(Decoder* decoder, Instruction& instruction)
	{
		auto handler = defaultHandler;
		auto options = decoder->options;
		for (auto info : infos)
		{
			if ((options & info.options) != 0)
			{
				handler = info.handler;
				break;
			}
		}
		handler->Decode(decoder, instruction);
	}
}
