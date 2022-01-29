// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "LegacyOpCodeHandlerReader.h"
#include "../Code.g.h"
#include "LegacyOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_Legacy.h"
#include "OpCodeHandlers_D3NOW.h"
#include "OpCodeHandlers_Fpu.h"

namespace Iced::Intel::DecoderInternal
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
	std::int32_t LegacyOpCodeHandlerReader::ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex)
	{
		auto& elem = result[resultIndex];
		Code code;
        switch (deserializer.ReadLegacyOpCodeHandlerKind())
        {
        case LegacyOpCodeHandlerKind::Bitness:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_Bitness>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Bitness_DontReadModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_Bitness_DontReadModRM>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Invalid:
            elem = OpCodeHandler_Invalid::GetInstance();
            return 1;
        case LegacyOpCodeHandlerKind::Invalid_NoModRM:
            elem = OpCodeHandler_Invalid_NoModRM::GetInstance();
            return 1;
        case LegacyOpCodeHandlerKind::Invalid2:
            result[resultIndex] = OpCodeHandler_Invalid::GetInstance();
            result[resultIndex + 1] = OpCodeHandler_Invalid::GetInstance();
            return 2;
        case LegacyOpCodeHandlerKind::Dup:
        {
            std::int32_t count = deserializer.ReadInt32();
            auto handler = deserializer.ReadHandlerOrNull();
            for (std::int32_t i = 0; i < count; i++)
            {
                result[resultIndex + i] = handler;
            }
            return count;
        }
        case LegacyOpCodeHandlerKind::Null:
            elem = nullptr;
            return 1;
        case LegacyOpCodeHandlerKind::HandlerReference:
            elem = deserializer.ReadHandlerReference();
            return 1;
        case LegacyOpCodeHandlerKind::ArrayReference:
            throw std::runtime_error("invalid operation");
        case LegacyOpCodeHandlerKind::RM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_RM>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Options1632_1:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options1632>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Options1632_2:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            auto tempVar3 = deserializer.ReadHandler();
            auto tempVar4 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options1632>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Options3:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Options5:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            auto tempVar3 = deserializer.ReadHandler();
            auto tempVar4 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Options_DontReadModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadDecoderOptions();
            elem = std::make_shared<OpCodeHandler_Options_DontReadModRM>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::AnotherTable:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_AnotherTable>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Group:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Group8x64:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            auto tempVar1 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group8x64>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Group8x8:
        {
            auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            auto tempVar1 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference));
            elem = std::make_shared<OpCodeHandler_Group8x8>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MandatoryPrefix:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MandatoryPrefix4:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            auto tempVar4 = static_cast<std::uint32_t>(deserializer.ReadInt32());
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix4>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MandatoryPrefix_NoModRM:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix_NoModRM>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MandatoryPrefix3:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            auto tempVar2 = deserializer.ReadHandler();
            auto tempVar3 = deserializer.ReadHandler();
            auto tempVar4 = deserializer.ReadHandler();
            auto tempVar5 = deserializer.ReadHandler();
            auto tempVar6 = deserializer.ReadHandler();
            auto tempVar7 = deserializer.ReadHandler();
            auto tempVar8 = deserializer.ReadLegacyHandlerFlags();
            elem = std::make_shared<OpCodeHandler_MandatoryPrefix3>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4, tempVar5, tempVar6, tempVar7, tempVar8);
        }
        return 1;
        case LegacyOpCodeHandlerKind::D3NOW:
        {

            elem = std::make_shared<OpCodeHandler_D3NOW>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::EVEX:
        {
            auto tempVar0 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_EVEX>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VEX2:
        {
            auto tempVar0 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_VEX2>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VEX3:
        {
            auto tempVar0 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_VEX3>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::XOP:
        {
            auto tempVar0 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_XOP>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::AL_DX:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_AL_DX>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ap:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Ap>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::B_BM:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_B_BM>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::B_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadBoolean();
                elem = std::make_shared<OpCodeHandler_B_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::B_MIB:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_B_MIB>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::BM_B:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_BM_B>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::BranchIw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_BranchIw>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::BranchSimple:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_BranchSimple>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::C_R_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadRegister();
                elem = std::make_shared<OpCodeHandler_C_R>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::C_R_3b:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = Code::INVALID;
            auto tempVar2 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_C_R>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::DX_AL:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_DX_AL>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::DX_eAX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_DX_eAX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::eAX_DX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_eAX_DX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Eb_1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Eb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_2:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadHandlerFlags();
            elem = std::make_shared<OpCodeHandler_Eb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_CL:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Eb_CL>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_Gb_1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Eb_Gb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_Gb_2:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadHandlerFlags();
            elem = std::make_shared<OpCodeHandler_Eb_Gb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_Ib_1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Eb_Ib>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb_Ib_2:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadHandlerFlags();
            elem = std::make_shared<OpCodeHandler_Eb_Ib>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Eb1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Eb_1>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ed_V_Ib:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_Ed_V_Ib>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ep:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ep>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_3b:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = Code::INVALID;
                elem = std::make_shared<OpCodeHandler_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_Ev>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_CL:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_CL>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_32_64:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Ev_Gv_32_64>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Gv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_3b:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = Code::INVALID;
                elem = std::make_shared<OpCodeHandler_Ev_Gv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_Ev_Gv>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_CL:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Gv_CL>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_Ib:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Gv_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Gv_REX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Ev_Gv_REX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Ib_3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Ib_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_Ev_Ib>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Ib2_3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Ib2>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Ib2_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_Ev_Ib2>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Iz_3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Iz>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Iz_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_Ev_Iz>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_P:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Ev_P>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_REXW_1a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = Code::INVALID;
                auto tempVar2 = static_cast<std::uint32_t>(deserializer.ReadInt32());
                elem = std::make_shared<OpCodeHandler_Ev_REXW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_REXW:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = static_cast<std::uint32_t>(deserializer.ReadInt32());
                elem = std::make_shared<OpCodeHandler_Ev_REXW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_Sw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_Sw>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev_VX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Ev_VX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ev1:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ev_1>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Evj:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Evj>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Evw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Evw>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Ew:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ew>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gb_Eb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Gb_Eb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Gdq_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gdq_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Eb:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Eb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Eb_REX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Gv_Eb_REX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_32_64:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadBoolean();
                auto tempVar3 = deserializer.ReadBoolean();
                elem = std::make_shared<OpCodeHandler_Gv_Ev_32_64>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_3b:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = Code::INVALID;
                elem = std::make_shared<OpCodeHandler_Gv_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_Ib:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ev_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_Ib_REX:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_Gv_Ev_Ib_REX>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_Iz:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ev_Iz>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev_REX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Gv_Ev_REX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ev2>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ev3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ev3>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ew:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Ew>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_M:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_M>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_M_as:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_M_as>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Ma:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Gv_Ma>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Mp_2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = Code::INVALID;
                elem = std::make_shared<OpCodeHandler_Gv_Mp>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Mp_3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Mp>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_Mv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Gv_Mv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_N:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Gv_N>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_N_Ib_REX:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Gv_N_Ib_REX>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Gv_RX:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_Gv_RX>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Gv_W:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_Gv_W>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::GvM_VX_Ib:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_GvM_VX_Ib>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ib:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Ib>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ib3:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Ib3>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::IbReg:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_IbReg>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::IbReg2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_IbReg2>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Iw_Ib:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Iw_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Jb:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Jb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Jb2:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadCode();
            auto tempVar2 = deserializer.ReadCode();
            auto tempVar3 = deserializer.ReadCode();
            auto tempVar4 = deserializer.ReadCode();
            auto tempVar5 = deserializer.ReadCode();
            auto tempVar6 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Jb2>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4, tempVar5, tempVar6);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Jdisp:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Jdisp>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Jx:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadCode();
                elem = std::make_shared<OpCodeHandler_Jx>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Jz:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Jz>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::M_1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_M>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::M_2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_M>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::M_REXW_2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_M_REXW>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::M_REXW_4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadHandlerFlags();
                auto tempVar3 = deserializer.ReadHandlerFlags();
                elem = std::make_shared<OpCodeHandler_M_REXW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::MemBx:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MemBx>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Mf_1:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Mf>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Mf_2a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Mf>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Mf_2b:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Mf>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MIB_B:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MIB_B>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::MP:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MP>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ms:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ms>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::MV:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_MV>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Mv_Gv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Mv_Gv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Mv_Gv_REXW:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Mv_Gv_REXW>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::NIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_NIb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ob_Reg:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Ob_Reg>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Ov_Reg:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Ov_Reg>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::P_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_P_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::P_Ev_Ib:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_P_Ev_Ib>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::P_Q:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_P_Q>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::P_Q_Ib:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_P_Q_Ib>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::P_R:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_P_R>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::P_W:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_P_W>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::PushEv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_PushEv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushIb2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_PushIb2>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushIz:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_PushIz>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushOpSizeReg_4a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                auto tempVar3 = deserializer.ReadRegister();
                elem = std::make_shared<OpCodeHandler_PushOpSizeReg>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushOpSizeReg_4b:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = Code::INVALID;
                auto tempVar3 = deserializer.ReadRegister();
                elem = std::make_shared<OpCodeHandler_PushOpSizeReg>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushSimple2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_PushSimple2>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::PushSimpleReg:
        {
            auto tempVar0 = deserializer.ReadInt32();
            auto tempVar1 = code = deserializer.ReadCode();
            auto tempVar2 = (Code)(code + 1);
            auto tempVar3 = (Code)(code + 2);
            elem = std::make_shared<OpCodeHandler_PushSimpleReg>(tempVar0, tempVar1, tempVar2, tempVar3);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Q_P:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Q_P>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::R_C_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = deserializer.ReadRegister();
                elem = std::make_shared<OpCodeHandler_R_C>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::R_C_3b:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = Code::INVALID;
            auto tempVar2 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_R_C>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::rDI_P_N:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_rDI_P_N>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::rDI_VX_RX:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_rDI_VX_RX>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reg:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Reg>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reg_Ib2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Reg_Ib2>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Reg_Iz:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Reg_Iz>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Reg_Ob:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Reg_Ob>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reg_Ov:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Reg_Ov>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Reg_Xb:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Reg_Xb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reg_Xv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Reg_Xv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Reg_Xv2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Reg_Xv2>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Reg_Yb:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Reg_Yb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reg_Yv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Reg_Yv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::RegIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_RegIb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::RegIb3:
        {
            auto tempVar0 = deserializer.ReadInt32();
            elem = std::make_shared<OpCodeHandler_RegIb3>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::RegIz2:
        {
            auto tempVar0 = deserializer.ReadInt32();
            elem = std::make_shared<OpCodeHandler_RegIz2>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Reservednop:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = deserializer.ReadHandler();
            elem = std::make_shared<OpCodeHandler_Reservednop>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::RIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_RIb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::RIbIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_RIbIb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Rv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Rv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Rv_32_64:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Rv_32_64>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::RvMw_Gw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_RvMw_Gw>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Simple>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Simple_ModRM:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Simple_ModRM>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Simple2_3a:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Simple2>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple2_3b:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadCode();
            auto tempVar2 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Simple2>(tempVar0, tempVar1, tempVar2);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Simple2Iw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Simple2Iw>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple3:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Simple3>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple4:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Simple4>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple4b:
        {
            code = deserializer.ReadCode();
            auto code2 = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = code2;
                elem = std::make_shared<OpCodeHandler_Simple4>(tempVar0, tempVar1);
            }
            return 1;
        }
        case LegacyOpCodeHandlerKind::Simple5:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Simple5>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Simple5_ModRM_as:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Simple5_ModRM_as>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::SimpleReg:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadInt32();
            elem = std::make_shared<OpCodeHandler_SimpleReg>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::ST_STi:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_ST_STi>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::STi:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_STi>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::STi_ST:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_STi_ST>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Sw_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Sw_Ev>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::V_Ev:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_V_Ev>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VM:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VM>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VN:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VN>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VQ:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VQ>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VRIbIb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VRIbIb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VW_2:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VW>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VW_3:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VW>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VWIb_2:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_VWIb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VWIb_3:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VWIb>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VX_E_Ib:
        {
            auto tempVar0 = code = deserializer.ReadCode();
            auto tempVar1 = (Code)(code + 1);
            elem = std::make_shared<OpCodeHandler_VX_E_Ib>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::VX_Ev:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_VX_Ev>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Wbinvd:
        {

            elem = std::make_shared<OpCodeHandler_Wbinvd>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::WV:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_WV>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Xb_Yb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Xb_Yb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Xchg_Reg_rAX:
        {
            auto tempVar0 = deserializer.ReadInt32();
            elem = std::make_shared<OpCodeHandler_Xchg_Reg_rAX>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Xv_Yv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Xv_Yv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Yb_Reg:
        {
            auto tempVar0 = deserializer.ReadCode();
            auto tempVar1 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_Yb_Reg>(tempVar0, tempVar1);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Yb_Xb:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Yb_Xb>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Yv_Reg:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Yv_Reg>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Yv_Reg2:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                elem = std::make_shared<OpCodeHandler_Yv_Reg2>(tempVar0, tempVar1);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Yv_Xv:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                auto tempVar1 = (Code)(code + 1);
                auto tempVar2 = (Code)(code + 2);
                elem = std::make_shared<OpCodeHandler_Yv_Xv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
        case LegacyOpCodeHandlerKind::M_Sw:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                elem = std::make_shared<OpCodeHandler_M_Sw>(tempVar0);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Sw_M:
            code = deserializer.ReadCode();
            {
                auto tempVar0 = code;
                elem = std::make_shared<OpCodeHandler_Sw_M>(tempVar0);
            }
            return 1;
        case LegacyOpCodeHandlerKind::Rq:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Rq>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Gd_Rd:
        {
            auto tempVar0 = deserializer.ReadCode();
            elem = std::make_shared<OpCodeHandler_Gd_Rd>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixEsCsSsDs:
        {
            auto tempVar0 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_PrefixEsCsSsDs>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixFsGs:
        {
            auto tempVar0 = deserializer.ReadRegister();
            elem = std::make_shared<OpCodeHandler_PrefixFsGs>(tempVar0);
        }
        return 1;
        case LegacyOpCodeHandlerKind::Prefix66:
        {

            elem = std::make_shared<OpCodeHandler_Prefix66>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::Prefix67:
        {

            elem = std::make_shared<OpCodeHandler_Prefix67>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixF0:
        {

            elem = std::make_shared<OpCodeHandler_PrefixF0>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixF2:
        {

            elem = std::make_shared<OpCodeHandler_PrefixF2>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixF3:
        {

            elem = std::make_shared<OpCodeHandler_PrefixF3>();
        }
        return 1;
        case LegacyOpCodeHandlerKind::PrefixREX:
        {
            auto tempVar0 = deserializer.ReadHandler();
            auto tempVar1 = static_cast<std::uint32_t>(deserializer.ReadInt32());
            elem = std::make_shared<OpCodeHandler_PrefixREX>(tempVar0, tempVar1);
        }
        return 1;
        default:
            throw std::runtime_error("invalid operation");
        }
    }
}
