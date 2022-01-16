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
#include "EncoderData.g.h"
#include "../Iced.Intel.IcedConstants.h"
#include "Enums.h"
#include "../EncodingKind.g.h"
#include "../Code.g.h"

namespace Iced::Intel::EncoderInternal
{

	std::vector<OpCodeHandler*> OpCodeHandlers::Handlers;

	OpCodeHandlers::StaticConstructor::StaticConstructor()
	{
		auto encFlags1 = EncoderData::EncFlags1;
		auto encFlags2 = EncoderData::EncFlags2;
		auto encFlags3Data = EncoderData::EncFlags3;
		auto handlers = std::vector<OpCodeHandler*>(IcedConstants::CodeEnumCount);
		std::int32_t i = 0;
		auto invalidHandler = new InvalidHandler();
		for (; i < encFlags1.size(); i++)
		{
			auto encFlags3 = static_cast<EncFlags3>(encFlags3Data[i]);
			OpCodeHandler* handler;
			switch (static_cast<EncodingKind>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::EncodingShift)) & static_cast<std::uint32_t>(EncFlags3::EncodingMask)))
			{
			case EncodingKind::Legacy:
			{
				auto code = static_cast<Code>(i);
				if (code == Code::INVALID)
				{
					handler = invalidHandler;
				}
				else if (code <= Code::DeclareQword)
				{
					handler = new DeclareDataHandler(code);
				}
				else
				{
					handler = new LegacyHandler(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				}
				break;
			}
			case EncodingKind::VEX:
				handler = new VexHandler(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::EVEX:
				handler = new EvexHandler(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::XOP:
				handler = new XopHandler(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::D3NOW:
				handler = new D3nowHandler(static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::MVEX:
				handler = new MvexHandler(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			default:
				throw InvalidOperationException();
			}
			handlers[i] = handler;
		}
		if (i != handlers.size())
		{
			throw InvalidOperationException();
		}
		Handlers = handlers;
	}

	OpCodeHandlers::StaticConstructor OpCodeHandlers::staticConstructor;
}
