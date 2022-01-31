// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "TableDeserializer.h"
#include "OpCodeHandlers.h"
#include "OpCodeHandlers_EVEX.h"
#include "../Code.g.h"
#include "EvexOpCodeHandlerKind.g.h"
#include <vector>

namespace Iced::Intel::DecoderInternal
{
#define EVEX_OPCODEHANDLER_KINDS \
	OpCodeHandler_RM, \
	OpCodeHandler_Group, \
	OpCodeHandler_W, \
	OpCodeHandler_MandatoryPrefix2, \
	OpCodeHandler_VectorLength_EVEX, \
	OpCodeHandler_VectorLength_EVEX_er, \
	OpCodeHandler_EVEX_Ed_V_Ib, \
	OpCodeHandler_EVEX_Ev_VX, \
	OpCodeHandler_EVEX_Ev_VX_Ib, \
	OpCodeHandler_EVEX_Gv_W_er, \
	OpCodeHandler_EVEX_GvM_VX_Ib, \
	OpCodeHandler_EVEX_HkWIb, \
	OpCodeHandler_EVEX_HWIb, \
	OpCodeHandler_EVEX_KkHW, \
	OpCodeHandler_EVEX_KkHWIb_sae, \
	OpCodeHandler_EVEX_KkHWIb, \
	OpCodeHandler_EVEX_KkWIb, \
	OpCodeHandler_EVEX_KP1HW, \
	OpCodeHandler_EVEX_KR, \
	OpCodeHandler_EVEX_MV, \
	OpCodeHandler_EVEX_V_H_Ev_er, \
	OpCodeHandler_EVEX_V_H_Ev_Ib, \
	OpCodeHandler_EVEX_VHM, \
	OpCodeHandler_EVEX_VHW, \
	OpCodeHandler_EVEX_VHWIb, \
	OpCodeHandler_EVEX_VK, \
	OpCodeHandler_EVEX_Vk_VSIB, \
	OpCodeHandler_EVEX_VkEv_REXW, \
	OpCodeHandler_EVEX_VkHM, \
	OpCodeHandler_EVEX_VkHW, \
	OpCodeHandler_EVEX_VkHW_er, \
	OpCodeHandler_EVEX_VkHW_er_ur, \
	OpCodeHandler_EVEX_VkHWIb, \
	OpCodeHandler_EVEX_VkHWIb_er, \
	OpCodeHandler_EVEX_VkM, \
	OpCodeHandler_EVEX_VkW, \
	OpCodeHandler_EVEX_VkW_er, \
	OpCodeHandler_EVEX_VkWIb, \
	OpCodeHandler_EVEX_VkWIb_er, \
	OpCodeHandler_EVEX_VM, \
	OpCodeHandler_EVEX_VSIB_k1, \
	OpCodeHandler_EVEX_VSIB_k1_VX, \
	OpCodeHandler_EVEX_VW, \
	OpCodeHandler_EVEX_VW_er, \
	OpCodeHandler_EVEX_VX_Ev, \
	OpCodeHandler_EVEX_WkHV, \
	OpCodeHandler_EVEX_WkV, \
	OpCodeHandler_EVEX_WkVIb, \
	OpCodeHandler_EVEX_WkVIb_er, \
	OpCodeHandler_EVEX_WV

	using EvexTableDeserializer = TableDeserializer<EVEX_OPCODEHANDLER_KINDS>;
    template <std::size_t N, std::array<std::size_t, N> Sizes>
    using EvexArrayPool = Internal::ArrayPool<N, Sizes, EVEX_OPCODEHANDLER_KINDS>;

	class EvexOpCodeHandlerReader final
        : public OpCodeHandlerReader<EVEX_OPCODEHANDLER_KINDS>
	{
	public:
        constexpr std::int32_t ReadHandlers(EvexTableDeserializer& deserializer, std::vector<const OpCodeHandler*>& result, std::int32_t resultIndex) override
        {
            auto& elem = result[resultIndex];
            Code code;
            switch (deserializer.ReadEvexOpCodeHandlerKind())
            {
            case EvexOpCodeHandlerKind::Invalid:
                elem = &OpCodeHandler_Invalid_Instance;
                return 1;
            case EvexOpCodeHandlerKind::Invalid2:
                result[resultIndex] = &OpCodeHandler_Invalid_Instance;
                result[resultIndex + 1] = &OpCodeHandler_Invalid_Instance;
                return 2;
            case EvexOpCodeHandlerKind::Dup:
            {
                std::int32_t count = deserializer.ReadInt32();
                auto handler = deserializer.ReadHandler();
                for (std::int32_t i = 0; i < count; i++)
                {
                    result[resultIndex + i] = handler;
                }
                return count;
            }
            case EvexOpCodeHandlerKind::HandlerReference:
                elem = deserializer.ReadHandlerReference();
                return 1;
            case EvexOpCodeHandlerKind::ArrayReference:
                throw std::runtime_error("invalid operation");
            case EvexOpCodeHandlerKind::RM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_RM>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::Group:
            {
                auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(EvexOpCodeHandlerKind::ArrayReference));
                elem = pool.template Construct<OpCodeHandler_Group>(tempVar0);
            }
            return 1;
            case EvexOpCodeHandlerKind::W:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_W>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::MandatoryPrefix2:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                auto tempVar3 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_MandatoryPrefix2>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VectorLength:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_VectorLength_EVEX>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VectorLength_er:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_VectorLength_EVEX_er>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::Ed_V_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_Ed_V_Ib>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::Ev_VX:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    auto tempVar2 = deserializer.ReadTupleType();
                    auto tempVar3 = deserializer.ReadTupleType();
                    elem = pool.template Construct<OpCodeHandler_EVEX_Ev_VX>(tempVar0, tempVar1, tempVar2, tempVar3);
                }
                return 1;
            case EvexOpCodeHandlerKind::Ev_VX_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_EVEX_Ev_VX_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::Gv_W_er:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadBoolean();
                elem = pool.template Construct<OpCodeHandler_EVEX_Gv_W_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::GvM_VX_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_GvM_VX_Ib>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::HkWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_HkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::HkWIb_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_HkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::HWIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_HWIb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHW_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHWIb_sae_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHWIb_sae>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHWIb_sae_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHWIb_sae>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkHWIb_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KkWIb_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_KkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::KP1HW:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_KP1HW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::KR:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_EVEX_KR>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::MV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_MV>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::V_H_Ev_er:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_V_H_Ev_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::V_H_Ev_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_V_H_Ev_Ib>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VHM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VHM>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VHW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VHW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VHW_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VHWIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VHWIb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VK:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_EVEX_VK>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::Vk_VSIB:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_Vk_VSIB>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkEv_REXW_2:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkEv_REXW>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkEv_REXW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkEv_REXW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHM>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_5:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadRegister();
                auto tempVar3 = deserializer.ReadCode();
                auto tempVar4 = deserializer.ReadTupleType();
                auto tempVar5 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4, tempVar5);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_er_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = deserializer.ReadBoolean();
                auto tempVar4 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_er_4b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = deserializer.ReadBoolean();
                auto tempVar4 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_er_ur_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW_er_ur>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHW_er_ur_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHW_er_ur>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHWIb_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHWIb_5:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadRegister();
                auto tempVar3 = deserializer.ReadCode();
                auto tempVar4 = deserializer.ReadTupleType();
                auto tempVar5 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHWIb>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4, tempVar5);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHWIb_er_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHWIb_er>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkHWIb_er_4b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkHWIb_er>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkM>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_4b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_er_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = deserializer.ReadBoolean();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW_er>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_er_5:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadBoolean();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkW_er_6:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                auto tempVar4 = deserializer.ReadBoolean();
                auto tempVar5 = deserializer.ReadBoolean();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkW_er>(tempVar0, tempVar1, tempVar2, tempVar3, tempVar4, tempVar5);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = false;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkWIb_3b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = true;
                elem = pool.template Construct<OpCodeHandler_EVEX_VkWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VkWIb_er:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VkWIb_er>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VM>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VSIB_k1:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VSIB_k1>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VSIB_k1_VX:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VSIB_k1_VX>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::VW:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VW_er:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_VW_er>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::VX_Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    auto tempVar2 = deserializer.ReadTupleType();
                    auto tempVar3 = deserializer.ReadTupleType();
                    elem = pool.template Construct<OpCodeHandler_EVEX_VX_Ev>(tempVar0, tempVar1, tempVar2, tempVar3);
                }
                return 1;
            case EvexOpCodeHandlerKind::WkHV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkHV>(tempVar0, tempVar1);
            }
            return 1;
            case EvexOpCodeHandlerKind::WkV_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkV>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case EvexOpCodeHandlerKind::WkV_4a:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkV>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::WkV_4b:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                auto tempVar3 = deserializer.ReadBoolean();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkV>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::WkVIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkVIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::WkVIb_er:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                auto tempVar3 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_WkVIb_er>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case EvexOpCodeHandlerKind::WV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadTupleType();
                elem = pool.template Construct<OpCodeHandler_EVEX_WV>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            default:
                throw std::runtime_error("invalid operation");
            }
        }
    };

#undef EVEX_OPCODEHANDLER_KINDS
}
