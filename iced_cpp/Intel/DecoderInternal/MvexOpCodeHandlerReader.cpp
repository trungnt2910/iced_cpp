// C# helper headers




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
		auto& elem = result[resultIndex];
        switch (deserializer.ReadMvexOpCodeHandlerKind())
        {
        case MvexOpCodeHandlerKind::Invalid:
            elem = OpCodeHandler_Invalid::GetInstance();
            return 1;
        case MvexOpCodeHandlerKind::Invalid2:
            result[resultIndex] = OpCodeHandler_Invalid::GetInstance();
            result[resultIndex + 1] = OpCodeHandler_Invalid::GetInstance();
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
            throw std::runtime_error("invalid operation");
        case MvexOpCodeHandlerKind::RM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_RM>(tempVar0, tempVar1);
        }
        return 1;
        case MvexOpCodeHandlerKind::Group:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(MvexOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::W:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_W>(tempVar0, tempVar1);
        }
        return 1;
        case MvexOpCodeHandlerKind::MandatoryPrefix2:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case MvexOpCodeHandlerKind::EH:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_EH>(tempVar0, tempVar1);
        }
        return 1;
        case MvexOpCodeHandlerKind::M:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_M>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::MV:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_MV>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VW:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VW>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::HWIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_HWIb>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VWIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VWIb>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VHW:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VHW>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VHWIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VHWIb>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VKW:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VKW>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::KHW:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_KHW>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::KHWIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_KHWIb>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VSIB:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VSIB>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::VSIB_V:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_VSIB_V>(tempVar0);
        }
        return 1;
        case MvexOpCodeHandlerKind::V_VSIB:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MVEX_V_VSIB>(tempVar0);
        }
        return 1;
        default:
            throw std::runtime_error("invalid operation");
        }
    }
}
