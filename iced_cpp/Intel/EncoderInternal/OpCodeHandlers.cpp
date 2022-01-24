// C# helper headers

#include <csharp/enum.h>



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

	std::vector<std::shared_ptr<OpCodeHandler>> OpCodeHandlers::Handlers;

	OpCodeHandlers::StaticConstructor::StaticConstructor()
	{
		const auto& encFlags1 = EncoderData::EncFlags1;
		const auto& encFlags2 = EncoderData::EncFlags2;
		const auto& encFlags3Data = EncoderData::EncFlags3;
		auto handlers = std::vector<std::shared_ptr<OpCodeHandler>>(IcedConstants::CodeEnumCount);
		std::int32_t i = 0;
		auto invalidHandler = std::make_shared<InvalidHandler>();
		for (; i < encFlags1.size(); i++)
		{
			auto encFlags3 = static_cast<EncFlags3>(encFlags3Data[i]);
			std::shared_ptr<OpCodeHandler> handler;
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
					handler = std::make_shared<DeclareDataHandler>(code);
				}
				else
				{
					handler = std::make_shared<LegacyHandler>(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				}
				break;
			}
			case EncodingKind::VEX:
				handler = std::make_shared<VexHandler>(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::EVEX:
				handler = std::make_shared<EvexHandler>(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::XOP:
				handler = std::make_shared<XopHandler>(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::D3NOW:
				handler = std::make_shared<D3nowHandler>(static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			case EncodingKind::MVEX:
				handler = std::make_shared<MvexHandler>(static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), encFlags3);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			handlers[i] = handler;
		}
		if (i != handlers.size())
		{
			throw std::runtime_error("invalid operation");
		}
		Handlers = handlers;
	}

	OpCodeHandlers::StaticConstructor OpCodeHandlers::staticConstructor;
}
