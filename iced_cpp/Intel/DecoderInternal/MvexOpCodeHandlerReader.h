// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "TableDeserializer.h"
#include "OpCodeHandlers.h"
#include "MvexOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_MVEX.h"
#include <vector>

namespace Iced::Intel::DecoderInternal
{
#define MVEX_OPCODEHANDLER_KINDS \
	OpCodeHandler_RM, \
	OpCodeHandler_Group, \
	OpCodeHandler_W, \
	OpCodeHandler_MandatoryPrefix2, \
	OpCodeHandler_EH, \
	OpCodeHandler_MVEX_M, \
	OpCodeHandler_MVEX_MV, \
	OpCodeHandler_MVEX_VW, \
	OpCodeHandler_MVEX_HWIb, \
	OpCodeHandler_MVEX_VWIb, \
	OpCodeHandler_MVEX_VHW, \
	OpCodeHandler_MVEX_VHWIb, \
	OpCodeHandler_MVEX_VKW, \
	OpCodeHandler_MVEX_KHW, \
	OpCodeHandler_MVEX_KHWIb, \
	OpCodeHandler_MVEX_VSIB, \
	OpCodeHandler_MVEX_VSIB_V, \
	OpCodeHandler_MVEX_V_VSIB

	using MvexTableDeserializer = TableDeserializer<MVEX_OPCODEHANDLER_KINDS>;
	
	class MvexOpCodeHandlerReader final 
		: public OpCodeHandlerReader<MVEX_OPCODEHANDLER_KINDS>
	{
	public:
        constexpr std::int32_t ReadHandlers(MvexTableDeserializer& deserializer, std::vector<const OpCodeHandler*>& result, std::int32_t resultIndex) override
        {
            auto& elem = result[resultIndex];
            switch (deserializer.ReadMvexOpCodeHandlerKind())
            {
            case MvexOpCodeHandlerKind::Invalid:
                elem = &OpCodeHandler_Invalid_Instance;
                return 1;
            case MvexOpCodeHandlerKind::Invalid2:
                result[resultIndex] = &OpCodeHandler_Invalid_Instance;
                result[resultIndex + 1] = &OpCodeHandler_Invalid_Instance;
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
                elem = pool.template Construct<OpCodeHandler_RM>(tempVar0, tempVar1);
            }
            return 1;
            case MvexOpCodeHandlerKind::Group:
            {
                auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(MvexOpCodeHandlerKind::ArrayReference));
                elem = pool.template Construct<OpCodeHandler_Group>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::W:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_W>(tempVar0, tempVar1);
            }
            return 1;
            case MvexOpCodeHandlerKind::MandatoryPrefix2:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                auto tempVar3 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_MandatoryPrefix2>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case MvexOpCodeHandlerKind::EH:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_EH>(tempVar0, tempVar1);
            }
            return 1;
            case MvexOpCodeHandlerKind::M:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_M>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::MV:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_MV>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VW:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VW>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::HWIb:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_HWIb>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VWIb:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VWIb>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VHW:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VHW>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VHWIb:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VHWIb>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VKW:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VKW>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::KHW:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_KHW>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::KHWIb:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_KHWIb>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VSIB:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VSIB>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::VSIB_V:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_VSIB_V>(tempVar0);
            }
            return 1;
            case MvexOpCodeHandlerKind::V_VSIB:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_MVEX_V_VSIB>(tempVar0);
            }
            return 1;
            default:
                throw std::runtime_error("invalid operation");
            }
        }
    };
#undef MVEX_OPCODEHANDLER_KINDS
}
