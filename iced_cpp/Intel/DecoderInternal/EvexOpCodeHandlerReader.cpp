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

#include "EvexOpCodeHandlerReader.h"
#include "../Code.g.h"
#include "EvexOpCodeHandlerKind.g.h"
#include "OpCodeHandlers_EVEX.h"

namespace Iced::Intel::DecoderInternal
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override int ReadHandlers(ref TableDeserializer deserializer, OpCodeHandler?[] result, int resultIndex)
	std::int32_t EvexOpCodeHandlerReader::ReadHandlers(TableDeserializer& deserializer, std::vector<std::shared_ptr<OpCodeHandler>>& result, std::int32_t resultIndex)
	{
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var elem = ref result[resultIndex];
		auto elem = result[resultIndex];
		Code code;
		switch (deserializer.ReadEvexOpCodeHandlerKind())
		{
		case EvexOpCodeHandlerKind::Invalid:
			elem = OpCodeHandler_Invalid::Instance;
			return 1;
		case EvexOpCodeHandlerKind::Invalid2:
			result[resultIndex] = OpCodeHandler_Invalid::Instance;
			result[resultIndex + 1] = OpCodeHandler_Invalid::Instance;
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
			throw InvalidOperationException();
		case EvexOpCodeHandlerKind::RM:
			elem = std::make_shared<OpCodeHandler_RM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case EvexOpCodeHandlerKind::Group:
			elem = std::make_shared<OpCodeHandler_Group>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(EvexOpCodeHandlerKind::ArrayReference)));
			return 1;
		case EvexOpCodeHandlerKind::W:
			elem = std::make_shared<OpCodeHandler_W>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case EvexOpCodeHandlerKind::MandatoryPrefix2:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix2>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case EvexOpCodeHandlerKind::VectorLength:
			elem = std::make_shared<OpCodeHandler_VectorLength_EVEX>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case EvexOpCodeHandlerKind::VectorLength_er:
			elem = std::make_shared<OpCodeHandler_VectorLength_EVEX_er>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case EvexOpCodeHandlerKind::Ed_V_Ib:
			elem = std::make_shared<OpCodeHandler_EVEX_Ed_V_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::Ev_VX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_EVEX_Ev_VX>(code, (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::Ev_VX_Ib:
			elem = std::make_shared<OpCodeHandler_EVEX_Ev_VX_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case EvexOpCodeHandlerKind::Gv_W_er:
			elem = std::make_shared<OpCodeHandler_EVEX_Gv_W_er>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadBoolean());
			return 1;
		case EvexOpCodeHandlerKind::GvM_VX_Ib:
			elem = std::make_shared<OpCodeHandler_EVEX_GvM_VX_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::HkWIb_3:
			elem = std::make_shared<OpCodeHandler_EVEX_HkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::HkWIb_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_HkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::HWIb:
			elem = std::make_shared<OpCodeHandler_EVEX_HWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::KkHW_3:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::KkHW_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::KkHWIb_sae_3:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHWIb_sae>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::KkHWIb_sae_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHWIb_sae>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::KkHWIb_3:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::KkHWIb_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_KkHWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::KkWIb_3:
			elem = std::make_shared<OpCodeHandler_EVEX_KkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::KkWIb_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_KkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::KP1HW:
			elem = std::make_shared<OpCodeHandler_EVEX_KP1HW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::KR:
			elem = std::make_shared<OpCodeHandler_EVEX_KR>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case EvexOpCodeHandlerKind::MV:
			elem = std::make_shared<OpCodeHandler_EVEX_MV>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::V_H_Ev_er:
			elem = std::make_shared<OpCodeHandler_EVEX_V_H_Ev_er>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::V_H_Ev_Ib:
			elem = std::make_shared<OpCodeHandler_EVEX_V_H_Ev_Ib>(deserializer.ReadRegister(), code = deserializer.ReadCode(), (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VHM:
			elem = std::make_shared<OpCodeHandler_EVEX_VHM>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VHW_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VHW_4:
			elem = std::make_shared<OpCodeHandler_EVEX_VHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VHWIb:
			elem = std::make_shared<OpCodeHandler_EVEX_VHWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VK:
			elem = std::make_shared<OpCodeHandler_EVEX_VK>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case EvexOpCodeHandlerKind::Vk_VSIB:
			elem = std::make_shared<OpCodeHandler_EVEX_Vk_VSIB>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VkEv_REXW_2:
			elem = std::make_shared<OpCodeHandler_EVEX_VkEv_REXW>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case EvexOpCodeHandlerKind::VkEv_REXW_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkEv_REXW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case EvexOpCodeHandlerKind::VkHM:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHM>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VkHW_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_5:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_er_4:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_er_4b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_er_ur_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW_er_ur>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHW_er_ur_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHW_er_ur>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkHWIb_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHWIb_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkHWIb_5:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHWIb>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHWIb_er_4:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHWIb_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkHWIb_er_4b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkHWIb_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkM:
			elem = std::make_shared<OpCodeHandler_EVEX_VkM>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VkW_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkW_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkW_4:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkW_4b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkW_er_4:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean());
			return 1;
		case EvexOpCodeHandlerKind::VkW_er_5:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW_er>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean());
			return 1;
		case EvexOpCodeHandlerKind::VkW_er_6:
			elem = std::make_shared<OpCodeHandler_EVEX_VkW_er>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean(), deserializer.ReadBoolean());
			return 1;
		case EvexOpCodeHandlerKind::VkWIb_3:
			elem = std::make_shared<OpCodeHandler_EVEX_VkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), false);
			return 1;
		case EvexOpCodeHandlerKind::VkWIb_3b:
			elem = std::make_shared<OpCodeHandler_EVEX_VkWIb>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), true);
			return 1;
		case EvexOpCodeHandlerKind::VkWIb_er:
			elem = std::make_shared<OpCodeHandler_EVEX_VkWIb_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VM:
			elem = std::make_shared<OpCodeHandler_EVEX_VM>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VSIB_k1:
			elem = std::make_shared<OpCodeHandler_EVEX_VSIB_k1>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VSIB_k1_VX:
			elem = std::make_shared<OpCodeHandler_EVEX_VSIB_k1_VX>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VW:
			elem = std::make_shared<OpCodeHandler_EVEX_VW>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VW_er:
			elem = std::make_shared<OpCodeHandler_EVEX_VW_er>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::VX_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_EVEX_VX_Ev>(code, (Code)(code + 1), deserializer.ReadTupleType(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::WkHV:
			elem = std::make_shared<OpCodeHandler_EVEX_WkHV>(deserializer.ReadRegister(), deserializer.ReadCode());
			return 1;
		case EvexOpCodeHandlerKind::WkV_3:
			elem = std::make_shared<OpCodeHandler_EVEX_WkV>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::WkV_4a:
			elem = std::make_shared<OpCodeHandler_EVEX_WkV>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::WkV_4b:
			elem = std::make_shared<OpCodeHandler_EVEX_WkV>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType(), deserializer.ReadBoolean());
			return 1;
		case EvexOpCodeHandlerKind::WkVIb:
			elem = std::make_shared<OpCodeHandler_EVEX_WkVIb>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::WkVIb_er:
			elem = std::make_shared<OpCodeHandler_EVEX_WkVIb_er>(deserializer.ReadRegister(), deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		case EvexOpCodeHandlerKind::WV:
			elem = std::make_shared<OpCodeHandler_EVEX_WV>(deserializer.ReadRegister(), deserializer.ReadCode(), deserializer.ReadTupleType());
			return 1;
		default:
			throw InvalidOperationException();
		}
	}
}
