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

#include "VexOpCodeHandlerReader.h"
#include "../Code.g.h"
#include "VexOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_VEX.h"

namespace Iced::Intel::DecoderInternal
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
	std::int32_t VexOpCodeHandlerReader::ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex)
	{
		auto& elem = result[resultIndex];
		Code code;
        switch (deserializer.ReadVexOpCodeHandlerKind())
        {
        case VexOpCodeHandlerKind::Invalid:
            elem = OpCodeHandler_Invalid::GetInstance();
            return 1;
        case VexOpCodeHandlerKind::Invalid2:
            result[resultIndex] = OpCodeHandler_Invalid::GetInstance();
            result[resultIndex + 1] = OpCodeHandler_Invalid::GetInstance();
            return 2;
        case VexOpCodeHandlerKind::Dup:
        {
            std::int32_t count = deserializer.ReadInt32();
            auto handler = deserializer.ReadHandlerOrNull();
            for (std::int32_t i = 0; i < count; i++)
            {
                result[resultIndex + i] = handler;
            }
            return count;
        }
        case VexOpCodeHandlerKind::Null:
            elem = nullptr;
            return 1;
        case VexOpCodeHandlerKind::Invalid_NoModRM:
            elem = OpCodeHandler_Invalid_NoModRM::GetInstance();
            return 1;
        case VexOpCodeHandlerKind::Bitness:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_Bitness>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Bitness_DontReadModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_Bitness_DontReadModRM>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::HandlerReference:
            elem = deserializer.ReadHandlerReference();
            return 1;
        case VexOpCodeHandlerKind::ArrayReference:
            throw InvalidOperationException();
        case VexOpCodeHandlerKind::RM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_RM>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Group:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::Group8x64:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
            auto tempVar1 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group8x64>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::W:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_W>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::MandatoryPrefix2_1:
        {
            auto tempVar0 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::MandatoryPrefix2_4:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case VexOpCodeHandlerKind::MandatoryPrefix2_NoModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix2_NoModRM>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case VexOpCodeHandlerKind::VectorLength_NoModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_VectorLength_NoModRM_VEX>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VectorLength:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_VectorLength_VEX>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Ed_V_Ib:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_Ed_V_Ib>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::Ev_VX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Ev_VX>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::G_VK:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_VEX_G_VK>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Gv_Ev_Gv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Gv>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Gv_Ev_Ib:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Ib>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Gv_Ev_Id:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Id>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Gv_GPR_Ib:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_Gv_GPR_Ib>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::Gv_Gv_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Gv_Gv_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Gv_RX:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_Gv_RX>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::Gv_W:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_Gv_W>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::GvM_VX_Ib:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_GvM_VX_Ib>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::HRIb:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_HRIb>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Hv_Ed_Id:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Hv_Ed_Id>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Hv_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Hv_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::M:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_M>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::MHV:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_MHV>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::M_VK:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_M_VK>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::MV:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_MV>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::rDI_VX_RX:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_rDI_VX_RX>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::RdRq:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_RdRq>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Simple:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_Simple>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VHEv:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_VHEv>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VHEvIb:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_VHEvIb>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VHIs4W:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHIs4W>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHIs5W:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHIs5W>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHM:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHM>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHW_2:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHW_3:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            auto tempVar2 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VHW_4:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadRegister();
            auto tempVar2 = deserializer.ReadRegister();
            auto tempVar3 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case VexOpCodeHandlerKind::VHWIb_2:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHWIb>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHWIb_4:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadRegister();
            auto tempVar2 = deserializer.ReadRegister();
            auto tempVar3 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case VexOpCodeHandlerKind::VHWIs4:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHWIs4>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VHWIs5:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VHWIs5>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_HK_RK:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VK_HK_RK>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_R:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_VEX_VK_R>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_RK:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VK_RK>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_RK_Ib:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VK_RK_Ib>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_WK:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VK_WK>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VM:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VM>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VW_2:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VW>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VW_3:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadRegister();
            auto tempVar2 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VW>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VWH:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VWH>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VWIb_2:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VWIb>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::VWIb_3:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VEX_VWIb>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VX_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_VX_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::VX_VSIB_HX:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadRegister();
            auto tempVar2 = deserializer.ReadRegister();
            auto tempVar3 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VX_VSIB_HX>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case VexOpCodeHandlerKind::WHV:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_WHV>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::WV:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_WV>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::WVIb:
        {
            auto tempVar0 = deserializer.ReadRegister();
            auto tempVar1 = deserializer.ReadRegister();
            auto tempVar2 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_WVIb>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::VT_SIBMEM:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VT_SIBMEM>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::SIBMEM_VT:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_SIBMEM_VT>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VT:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VT>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VT_RT_HT:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_VT_RT_HT>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::Options_DontReadModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options_DontReadModRM>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case VexOpCodeHandlerKind::Gq_HK_RK:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_Gq_HK_RK>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::VK_R_Ib:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_VEX_VK_R_Ib>(tempVar0, tempVar1);
        }
        return 1;
        case VexOpCodeHandlerKind::Gv_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VEX_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case VexOpCodeHandlerKind::K_Jb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_K_Jb>(tempVar0);
        }
        return 1;
        case VexOpCodeHandlerKind::K_Jz:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VEX_K_Jz>(tempVar0);
        }
        return 1;
        default:
            throw InvalidOperationException();
        }
    }
}
