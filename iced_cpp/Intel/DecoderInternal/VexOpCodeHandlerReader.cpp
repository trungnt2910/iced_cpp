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
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var elem = ref result[resultIndex];
		auto elem = result[resultIndex];
		Code code;
		switch (deserializer.ReadVexOpCodeHandlerKind())
		{
		case VexOpCodeHandlerKind::Invalid:
			elem = OpCodeHandler_Invalid::Instance;
			return 1;
		case VexOpCodeHandlerKind::Invalid2:
			result[resultIndex] = OpCodeHandler_Invalid::Instance;
			result[resultIndex + 1] = OpCodeHandler_Invalid::Instance;
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
			elem = OpCodeHandler_Invalid_NoModRM::Instance;
			return 1;
		case VexOpCodeHandlerKind::Bitness:
			elem = std::make_shared<OpCodeHandler_Bitness>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::Bitness_DontReadModRM:
			elem = std::make_shared<OpCodeHandler_Bitness_DontReadModRM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::HandlerReference:
			elem = deserializer.ReadHandlerReference();
			return 1;
		case VexOpCodeHandlerKind::ArrayReference:
			throw InvalidOperationException();
		case VexOpCodeHandlerKind::RM:
			elem = std::make_shared<OpCodeHandler_RM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::Group:
			elem = std::make_shared<OpCodeHandler_Group>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference)));
			return 1;
		case VexOpCodeHandlerKind::Group8x64:
			elem = std::make_shared<OpCodeHandler_Group8x64>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference)), deserializer.ReadArrayReference(static_cast<std::uint32_t>(VexOpCodeHandlerKind::ArrayReference)));
			return 1;
		case VexOpCodeHandlerKind::W:
			elem = std::make_shared<OpCodeHandler_W>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::MandatoryPrefix2_1:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::MandatoryPrefix2_4:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::MandatoryPrefix2_NoModRM:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix2_NoModRM>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::VectorLength_NoModRM:
			elem = std::make_shared<OpCodeHandler_VectorLength_NoModRM_VEX>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::VectorLength:
			elem = std::make_shared<OpCodeHandler_VectorLength_VEX>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case VexOpCodeHandlerKind::Ed_V_Ib:
			elem = std::make_shared<OpCodeHandler_VEX_Ed_V_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Ev_VX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Ev_VX>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::G_VK:
			elem = std::make_shared<OpCodeHandler_VEX_G_VK>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case VexOpCodeHandlerKind::Gv_Ev_Gv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Gv>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_Ev_Ib:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Ib>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_Ev_Id:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev_Id>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_GPR_Ib:
			elem = std::make_shared<OpCodeHandler_VEX_Gv_GPR_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_Gv_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Gv_Gv_Ev>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_RX:
			elem = std::make_shared<OpCodeHandler_VEX_Gv_RX>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Gv_W:
			elem = std::make_shared<OpCodeHandler_VEX_Gv_W>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::GvM_VX_Ib:
			elem = std::make_shared<OpCodeHandler_VEX_GvM_VX_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::HRIb:
			elem = std::make_shared<OpCodeHandler_VEX_HRIb>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::Hv_Ed_Id:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Hv_Ed_Id>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Hv_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Hv_Ev>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::M:
			elem = std::make_shared<OpCodeHandler_VEX_M>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::MHV:
			elem = std::make_shared<OpCodeHandler_VEX_MHV>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::M_VK:
			elem = std::make_shared<OpCodeHandler_VEX_M_VK>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::MV:
			elem = std::make_shared<OpCodeHandler_VEX_MV>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::rDI_VX_RX:
			elem = std::make_shared<OpCodeHandler_VEX_rDI_VX_RX>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::RdRq:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_RdRq>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Simple:
			elem = std::make_shared<OpCodeHandler_VEX_Simple>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHEv:
			elem = std::make_shared<OpCodeHandler_VEX_VHEv>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::VHEvIb:
			elem = std::make_shared<OpCodeHandler_VEX_VHEvIb>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::VHIs4W:
			elem = std::make_shared<OpCodeHandler_VEX_VHIs4W>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHIs5W:
			elem = std::make_shared<OpCodeHandler_VEX_VHIs5W>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHM:
			elem = std::make_shared<OpCodeHandler_VEX_VHM>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHW_2:
			elem = std::make_shared<OpCodeHandler_VEX_VHW>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHW_3:
			elem = std::make_shared<OpCodeHandler_VEX_VHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHW_4:
			elem = std::make_shared<OpCodeHandler_VEX_VHW>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHWIb_2:
			elem = std::make_shared<OpCodeHandler_VEX_VHWIb>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHWIb_4:
			elem = std::make_shared<OpCodeHandler_VEX_VHWIb>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHWIs4:
			elem = std::make_shared<OpCodeHandler_VEX_VHWIs4>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VHWIs5:
			elem = std::make_shared<OpCodeHandler_VEX_VHWIs5>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VK_HK_RK:
			elem = std::make_shared<OpCodeHandler_VEX_VK_HK_RK>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VK_R:
			elem = std::make_shared<OpCodeHandler_VEX_VK_R>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case VexOpCodeHandlerKind::VK_RK:
			elem = std::make_shared<OpCodeHandler_VEX_VK_RK>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VK_RK_Ib:
			elem = std::make_shared<OpCodeHandler_VEX_VK_RK_Ib>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VK_WK:
			elem = std::make_shared<OpCodeHandler_VEX_VK_WK>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VM:
			elem = std::make_shared<OpCodeHandler_VEX_VM>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VW_2:
			elem = std::make_shared<OpCodeHandler_VEX_VW>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VW_3:
			elem = std::make_shared<OpCodeHandler_VEX_VW>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VWH:
			elem = std::make_shared<OpCodeHandler_VEX_VWH>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VWIb_2:
			elem = std::make_shared<OpCodeHandler_VEX_VWIb>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VWIb_3:
			elem = std::make_shared<OpCodeHandler_VEX_VWIb>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::VX_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_VX_Ev>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::VX_VSIB_HX:
			elem = std::make_shared<OpCodeHandler_VEX_VX_VSIB_HX>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::WHV:
			elem = std::make_shared<OpCodeHandler_VEX_WHV>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::WV:
			elem = std::make_shared<OpCodeHandler_VEX_WV>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::WVIb:
			elem = std::make_shared<OpCodeHandler_VEX_WVIb>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VT_SIBMEM:
			elem = std::make_shared<OpCodeHandler_VEX_VT_SIBMEM>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::SIBMEM_VT:
			elem = std::make_shared<OpCodeHandler_VEX_SIBMEM_VT>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VT:
			elem = std::make_shared<OpCodeHandler_VEX_VT>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VT_RT_HT:
			elem = std::make_shared<OpCodeHandler_VEX_VT_RT_HT>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::Options_DontReadModRM:
			elem = std::make_shared<OpCodeHandler_Options_DontReadModRM>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case VexOpCodeHandlerKind::Gq_HK_RK:
			elem = std::make_shared<OpCodeHandler_VEX_Gq_HK_RK>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::VK_R_Ib:
			elem = std::make_shared<OpCodeHandler_VEX_VK_R_Ib>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case VexOpCodeHandlerKind::Gv_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Gv_Ev>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VEX_Ev>(code, (Code)(code + 1));
			return 1;
		case VexOpCodeHandlerKind::K_Jb:
			elem = std::make_shared<OpCodeHandler_VEX_K_Jb>(deserializer.ReadCode());
			return 1;
		case VexOpCodeHandlerKind::K_Jz:
			elem = std::make_shared<OpCodeHandler_VEX_K_Jz>(deserializer.ReadCode());
			return 1;
		default:
			throw InvalidOperationException();
		}
	}
}
