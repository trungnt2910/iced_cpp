#pragma once

#include "OpCodeHandlers.defs.h"
#include "../Decoder.h"
#include "../MandatoryPrefixByte.g.h"
#include "../Static.h"
#include "../EncodingKind.g.h"

namespace Iced::Intel::DecoderInternal
{
	inline void OpCodeHandler_Invalid::Decode(Decoder& decoder, Instruction& instruction) const
	{
		decoder.SetInvalidInstruction();
	}

	inline void OpCodeHandler_Invalid_NoModRM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		decoder.SetInvalidInstruction();
	}

	inline void OpCodeHandler_Simple_ModRM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		instruction.SetCode(code);
	}

	inline void OpCodeHandler_Group8x8::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		const OpCodeHandler* handler;
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

	inline void OpCodeHandler_Group8x64::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto& state = decoder.state;
		const OpCodeHandler* handler;
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

	inline void OpCodeHandler_Group::Decode(Decoder& decoder, Instruction& instruction) const
	{
		groupHandlers[decoder.state.reg]->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_AnotherTable::Decode(Decoder& decoder, Instruction& instruction) const
	{
		decoder.DecodeTable(std::span<const OpCodeHandler* const>(otherTable.begin(), otherTableSize), instruction);
	}

	inline void OpCodeHandler_MandatoryPrefix2::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::EVEX || decoder.state.GetEncoding() == EncodingKind::XOP || decoder.state.GetEncoding() == EncodingKind::MVEX);
		handlers[static_cast<std::int32_t>(decoder.state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_MandatoryPrefix2_NoModRM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::EVEX || decoder.state.GetEncoding() == EncodingKind::XOP || decoder.state.GetEncoding() == EncodingKind::MVEX);
		handlers[static_cast<std::int32_t>(decoder.state.mandatoryPrefix)]->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_W::Decode(Decoder& decoder, Instruction& instruction) const
	{
		assert(decoder.state.GetEncoding() == EncodingKind::VEX || decoder.state.GetEncoding() == EncodingKind::EVEX || decoder.state.GetEncoding() == EncodingKind::XOP || decoder.state.GetEncoding() == EncodingKind::MVEX);
		((decoder.state.flags & StateFlags::W) != 0 ? handlerW1 : handlerW0)->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_Bitness::Decode(Decoder& decoder, Instruction& instruction) const
	{
		const OpCodeHandler* handler;
		if (decoder.is64bMode)
		{
			handler = handler64;
		}
		else
		{
			handler = handler1632;
		}
		if (handler->HasModRM)
		{
			decoder.ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_Bitness_DontReadModRM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		const OpCodeHandler* handler;
		if (decoder.is64bMode)
		{
			handler = handler64;
		}
		else
		{
			handler = handler1632;
		}
		handler->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_RM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		(decoder.state.mod == 3 ? reg : mem)->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_Options1632::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto handler = defaultHandler;
		auto options = decoder.options;
		if (!decoder.is64bMode && (decoder.options & infoOptions) != 0)
		{
			for (const auto& info : std::span(infos.begin(), infoSize))
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
			decoder.ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_Options::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto handler = defaultHandler;
		auto options = decoder.options;
		if ((decoder.options & infoOptions) != 0)
		{
			for (const auto& info : std::span(infos.begin(), infoSize))
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
			decoder.ReadModRM();
		}
		handler->Decode(decoder, instruction);
	}

	inline void OpCodeHandler_Options_DontReadModRM::Decode(Decoder& decoder, Instruction& instruction) const
	{
		auto handler = defaultHandler;
		auto options = decoder.options;
		for (const auto& info : std::span(infos.begin(), infoSize))
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
