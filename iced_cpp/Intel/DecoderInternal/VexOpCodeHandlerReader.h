// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "TableDeserializer.h"
#include "OpCodeHandlers.h"
#include "../Code.g.h"
#include "VexOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_VEX.h"
#include <vector>

namespace Iced::Intel::DecoderInternal
{
#define VEX_OPCODEHANDLER_KINDS \
    OpCodeHandler_Bitness, \
    OpCodeHandler_Bitness_DontReadModRM, \
    OpCodeHandler_RM, \
    OpCodeHandler_Group, \
    OpCodeHandler_Group8x64, \
    OpCodeHandler_W, \
    OpCodeHandler_MandatoryPrefix2, \
    OpCodeHandler_MandatoryPrefix2_NoModRM, \
    OpCodeHandler_VectorLength_NoModRM_VEX, \
    OpCodeHandler_VectorLength_VEX, \
    OpCodeHandler_VEX_Ed_V_Ib, \
    OpCodeHandler_VEX_Ev_VX, \
    OpCodeHandler_VEX_G_VK, \
    OpCodeHandler_VEX_Gv_Ev_Gv, \
    OpCodeHandler_VEX_Gv_Ev_Ib, \
    OpCodeHandler_VEX_Gv_Ev_Id, \
    OpCodeHandler_VEX_Gv_GPR_Ib, \
    OpCodeHandler_VEX_Gv_Gv_Ev, \
    OpCodeHandler_VEX_Gv_RX, \
    OpCodeHandler_VEX_Gv_W, \
    OpCodeHandler_VEX_GvM_VX_Ib, \
    OpCodeHandler_VEX_HRIb, \
    OpCodeHandler_VEX_Hv_Ed_Id, \
    OpCodeHandler_VEX_Hv_Ev, \
    OpCodeHandler_VEX_M, \
    OpCodeHandler_VEX_MHV, \
    OpCodeHandler_VEX_M_VK, \
    OpCodeHandler_VEX_MV, \
    OpCodeHandler_VEX_rDI_VX_RX, \
    OpCodeHandler_VEX_RdRq, \
    OpCodeHandler_VEX_Simple, \
    OpCodeHandler_VEX_VHEv, \
    OpCodeHandler_VEX_VHEvIb, \
    OpCodeHandler_VEX_VHIs4W, \
    OpCodeHandler_VEX_VHIs5W, \
    OpCodeHandler_VEX_VHM, \
    OpCodeHandler_VEX_VHW, \
    OpCodeHandler_VEX_VHWIb, \
    OpCodeHandler_VEX_VHWIs4, \
    OpCodeHandler_VEX_VHWIs5, \
    OpCodeHandler_VEX_VK_HK_RK, \
    OpCodeHandler_VEX_VK_R, \
    OpCodeHandler_VEX_VK_RK, \
    OpCodeHandler_VEX_VK_RK_Ib, \
    OpCodeHandler_VEX_VK_WK, \
    OpCodeHandler_VEX_VM, \
    OpCodeHandler_VEX_VW, \
    OpCodeHandler_VEX_VWH, \
    OpCodeHandler_VEX_VWIb, \
    OpCodeHandler_VEX_VX_Ev, \
    OpCodeHandler_VEX_VX_VSIB_HX, \
    OpCodeHandler_VEX_WHV, \
    OpCodeHandler_VEX_WV, \
    OpCodeHandler_VEX_WVIb, \
    OpCodeHandler_VEX_VT_SIBMEM, \
    OpCodeHandler_VEX_SIBMEM_VT, \
    OpCodeHandler_VEX_VT, \
    OpCodeHandler_VEX_VT_RT_HT, \
    OpCodeHandler_Options_DontReadModRM, \
    OpCodeHandler_VEX_Gq_HK_RK, \
    OpCodeHandler_VEX_VK_R_Ib, \
    OpCodeHandler_VEX_Gv_Ev, \
    OpCodeHandler_VEX_Ev, \
    OpCodeHandler_VEX_K_Jb, \
    OpCodeHandler_VEX_K_Jz

	using VexTableDeserializer = TableDeserializer<VEX_OPCODEHANDLER_KINDS>;

	class VexOpCodeHandlerReader final 
		: public OpCodeHandlerReader<VEX_OPCODEHANDLER_KINDS>
	{
	public:
        constexpr std::int32_t ReadHandlers(VexTableDeserializer& deserializer, std::vector<const OpCodeHandler*>& result, std::int32_t resultIndex) override
        {
            auto& elem = result[resultIndex];
            Code code;
            switch (deserializer.ReadVexOpCodeHandlerKind())
            {
            case VexOpCodeHandlerKind::Invalid:
                elem = &OpCodeHandler_Invalid_Instance;
                return 1;
            case VexOpCodeHandlerKind::Invalid2:
                result[resultIndex] = &OpCodeHandler_Invalid_Instance;
                result[resultIndex + 1] = &OpCodeHandler_Invalid_Instance;
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
                elem = &OpCodeHandler_Invalid_NoModRM_Instance;
                return 1;
            case VexOpCodeHandlerKind::Bitness:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_Bitness>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Bitness_DontReadModRM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_Bitness_DontReadModRM>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::HandlerReference:
                elem = deserializer.ReadHandlerReference();
                return 1;
            case VexOpCodeHandlerKind::ArrayReference:
                throw std::runtime_error("invalid operation");
            case VexOpCodeHandlerKind::RM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_RM>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Group:
            {
                auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
                elem = pool.template Construct<OpCodeHandler_Group>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::Group8x64:
            {
                auto tempVar0 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
                auto tempVar1 = deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference));
                elem = pool.template Construct<OpCodeHandler_Group8x64>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::W:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_W>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::MandatoryPrefix2_1:
            {
                auto tempVar0 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_MandatoryPrefix2>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::MandatoryPrefix2_4:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                auto tempVar3 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_MandatoryPrefix2>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case VexOpCodeHandlerKind::MandatoryPrefix2_NoModRM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadHandler();
                auto tempVar3 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_MandatoryPrefix2_NoModRM>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case VexOpCodeHandlerKind::VectorLength_NoModRM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_VectorLength_NoModRM_VEX>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VectorLength:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                elem = pool.template Construct<OpCodeHandler_VectorLength_VEX>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Ed_V_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_Ed_V_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::Ev_VX:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Ev_VX>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::G_VK:
            {
                auto tempVar0 = deserializer.ReadCode();
                auto tempVar1 = deserializer.ReadRegister();
                elem = pool.template Construct<OpCodeHandler_VEX_G_VK>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Gv_Ev_Gv:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Gv_Ev_Gv>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Gv_Ev_Ib:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Gv_Ev_Ib>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Gv_Ev_Id:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Gv_Ev_Id>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Gv_GPR_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_Gv_GPR_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::Gv_Gv_Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Gv_Gv_Ev>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Gv_RX:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_Gv_RX>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::Gv_W:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_Gv_W>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::GvM_VX_Ib:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_GvM_VX_Ib>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::HRIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_HRIb>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Hv_Ed_Id:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Hv_Ed_Id>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Hv_Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Hv_Ev>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::M:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_M>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::MHV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_MHV>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::M_VK:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_M_VK>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::MV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_MV>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::rDI_VX_RX:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_rDI_VX_RX>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::RdRq:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_RdRq>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Simple:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_Simple>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VHEv:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_VHEv>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VHEvIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_VHEvIb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VHIs4W:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHIs4W>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHIs5W:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHIs5W>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHM>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHW_2:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                auto tempVar2 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VHW_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadRegister();
                auto tempVar3 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHW>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case VexOpCodeHandlerKind::VHWIb_2:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHWIb>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHWIb_4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadRegister();
                auto tempVar3 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHWIb>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case VexOpCodeHandlerKind::VHWIs4:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHWIs4>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VHWIs5:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VHWIs5>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_HK_RK:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_HK_RK>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_R:
            {
                auto tempVar0 = deserializer.ReadCode();
                auto tempVar1 = deserializer.ReadRegister();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_R>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_RK:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_RK>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_RK_Ib:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_RK_Ib>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_WK:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_WK>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VM:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VM>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VW_2:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VW>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VW_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VW>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VWH:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VWH>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VWIb_2:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VWIb>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::VWIb_3:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = code = deserializer.ReadCode();
                auto tempVar2 = (Code)(code + 1);
                elem = pool.template Construct<OpCodeHandler_VEX_VWIb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VX_Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_VX_Ev>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::VX_VSIB_HX:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadRegister();
                auto tempVar3 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VX_VSIB_HX>(tempVar0, tempVar1, tempVar2, tempVar3);
            }
            return 1;
            case VexOpCodeHandlerKind::WHV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_WHV>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::WV:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_WV>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::WVIb:
            {
                auto tempVar0 = deserializer.ReadRegister();
                auto tempVar1 = deserializer.ReadRegister();
                auto tempVar2 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_WVIb>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::VT_SIBMEM:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VT_SIBMEM>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::SIBMEM_VT:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_SIBMEM_VT>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VT:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VT>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VT_RT_HT:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_VT_RT_HT>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::Options_DontReadModRM:
            {
                auto tempVar0 = deserializer.ReadHandler();
                auto tempVar1 = deserializer.ReadHandler();
                auto tempVar2 = deserializer.ReadDecoderOptions();
                elem = pool.template Construct<OpCodeHandler_Options_DontReadModRM>(tempVar0, tempVar1, tempVar2);
            }
            return 1;
            case VexOpCodeHandlerKind::Gq_HK_RK:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_Gq_HK_RK>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::VK_R_Ib:
            {
                auto tempVar0 = deserializer.ReadCode();
                auto tempVar1 = deserializer.ReadRegister();
                elem = pool.template Construct<OpCodeHandler_VEX_VK_R_Ib>(tempVar0, tempVar1);
            }
            return 1;
            case VexOpCodeHandlerKind::Gv_Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Gv_Ev>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::Ev:
                code = deserializer.ReadCode();
                {
                    auto tempVar0 = code;
                    auto tempVar1 = (Code)(code + 1);
                    elem = pool.template Construct<OpCodeHandler_VEX_Ev>(tempVar0, tempVar1);
                }
                return 1;
            case VexOpCodeHandlerKind::K_Jb:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_K_Jb>(tempVar0);
            }
            return 1;
            case VexOpCodeHandlerKind::K_Jz:
            {
                auto tempVar0 = deserializer.ReadCode();
                elem = pool.template Construct<OpCodeHandler_VEX_K_Jz>(tempVar0);
            }
            return 1;
            default:
                throw std::runtime_error("invalid operation");
            }
        }
    };
#undef VEX_OPCODEHANDLER_KINDS
}
