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

#include "MvexOpCodeHandlerReader.h"
#include "MvexOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_MVEX.h"

namespace Iced::Intel::DecoderInternal
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
	std::int32_t MvexOpCodeHandlerReader::ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var elem = ref result[resultIndex];
		auto elem = result[resultIndex];
		switch (deserializer.ReadMvexOpCodeHandlerKind())
		{
		case MvexOpCodeHandlerKind::Invalid:
			elem = OpCodeHandler_Invalid::Instance;
			return 1;
		case MvexOpCodeHandlerKind::Invalid2:
			result[resultIndex] = OpCodeHandler_Invalid::Instance;
			result[resultIndex + 1] = OpCodeHandler_Invalid::Instance;
			return 2;
		case MvexOpCodeHandlerKind::Dup:
		{
			std::int32_t count = deserializer.ReadInt32();
			auto handler = deserializer.ReadHandler();
			for (std::int32_t i = 0; i < count; i++)
			{
				result[resultIndex + i] = handler;
			}
			return count;
		}
		case MvexOpCodeHandlerKind::HandlerReference:
			elem = deserializer.ReadHandlerReference();
			return 1;
		case MvexOpCodeHandlerKind::ArrayReference:
			throw InvalidOperationException();
		case MvexOpCodeHandlerKind::RM:
			elem = std::make_shared<OpCodeHandler_RM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case MvexOpCodeHandlerKind::Group:
			elem = std::make_shared<OpCodeHandler_Group>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(MvexOpCodeHandlerKind::ArrayReference)));
			return 1;
		case MvexOpCodeHandlerKind::W:
			elem = std::make_shared<OpCodeHandler_W>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case MvexOpCodeHandlerKind::MandatoryPrefix2:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case MvexOpCodeHandlerKind::EH:
			elem = std::make_shared<OpCodeHandler_EH>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case MvexOpCodeHandlerKind::M:
			elem = std::make_shared<OpCodeHandler_MVEX_M>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::MV:
			elem = std::make_shared<OpCodeHandler_MVEX_MV>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VW:
			elem = std::make_shared<OpCodeHandler_MVEX_VW>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::HWIb:
			elem = std::make_shared<OpCodeHandler_MVEX_HWIb>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VWIb:
			elem = std::make_shared<OpCodeHandler_MVEX_VWIb>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VHW:
			elem = std::make_shared<OpCodeHandler_MVEX_VHW>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VHWIb:
			elem = std::make_shared<OpCodeHandler_MVEX_VHWIb>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VKW:
			elem = std::make_shared<OpCodeHandler_MVEX_VKW>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::KHW:
			elem = std::make_shared<OpCodeHandler_MVEX_KHW>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::KHWIb:
			elem = std::make_shared<OpCodeHandler_MVEX_KHWIb>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VSIB:
			elem = std::make_shared<OpCodeHandler_MVEX_VSIB>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::VSIB_V:
			elem = std::make_shared<OpCodeHandler_MVEX_VSIB_V>(deserializer.ReadCode());
			return 1;
		case MvexOpCodeHandlerKind::V_VSIB:
			elem = std::make_shared<OpCodeHandler_MVEX_V_VSIB>(deserializer.ReadCode());
			return 1;
		default:
			throw InvalidOperationException();
		}
	}
}
