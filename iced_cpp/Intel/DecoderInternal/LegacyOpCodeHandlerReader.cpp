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
		//C# TO C++ CONVERTER TODO TASK: 'ref locals' are not converted by C# to C++ Converter:
		//ORIGINAL LINE: ref var elem = ref result[resultIndex];
		auto elem = result[resultIndex];
		Code code;
		switch (deserializer.ReadLegacyOpCodeHandlerKind())
		{
		case LegacyOpCodeHandlerKind::Bitness:
			elem = std::make_shared<OpCodeHandler_Bitness>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::Bitness_DontReadModRM:
			elem = std::make_shared<OpCodeHandler_Bitness_DontReadModRM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::Invalid:
			elem = OpCodeHandler_Invalid::Instance;
			return 1;
		case LegacyOpCodeHandlerKind::Invalid_NoModRM:
			elem = OpCodeHandler_Invalid_NoModRM::Instance;
			return 1;
		case LegacyOpCodeHandlerKind::Invalid2:
			result[resultIndex] = OpCodeHandler_Invalid::Instance;
			result[resultIndex + 1] = OpCodeHandler_Invalid::Instance;
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
			throw InvalidOperationException();
		case LegacyOpCodeHandlerKind::RM:
			elem = std::make_shared<OpCodeHandler_RM>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::Options1632_1:
			elem = std::make_shared<OpCodeHandler_Options1632>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case LegacyOpCodeHandlerKind::Options1632_2:
			elem = std::make_shared<OpCodeHandler_Options1632>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case LegacyOpCodeHandlerKind::Options3:
			elem = std::make_shared<OpCodeHandler_Options>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case LegacyOpCodeHandlerKind::Options5:
			elem = std::make_shared<OpCodeHandler_Options>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case LegacyOpCodeHandlerKind::Options_DontReadModRM:
			elem = std::make_shared<OpCodeHandler_Options_DontReadModRM>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadDecoderOptions());
			return 1;
		case LegacyOpCodeHandlerKind::AnotherTable:
			elem = std::make_shared<OpCodeHandler_AnotherTable>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)));
			return 1;
		case LegacyOpCodeHandlerKind::Group:
			elem = std::make_shared<OpCodeHandler_Group>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)));
			return 1;
		case LegacyOpCodeHandlerKind::Group8x64:
			elem = std::make_shared<OpCodeHandler_Group8x64>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)), deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)));
			return 1;
		case LegacyOpCodeHandlerKind::Group8x8:
			elem = std::make_shared<OpCodeHandler_Group8x8>(deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)), deserializer.ReadArrayReference(static_cast<std::uint32_t>(LegacyOpCodeHandlerKind::ArrayReference)));
			return 1;
		case LegacyOpCodeHandlerKind::MandatoryPrefix:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::MandatoryPrefix4:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix4>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), static_cast<std::uint32_t>(deserializer.ReadInt32()));
			return 1;
		case LegacyOpCodeHandlerKind::MandatoryPrefix_NoModRM:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix_NoModRM>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::MandatoryPrefix3:
			elem = std::make_shared<OpCodeHandler_MandatoryPrefix3>(deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadHandler(), deserializer.ReadLegacyHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::D3NOW:
			elem = std::make_shared<OpCodeHandler_D3NOW>();
			return 1;
		case LegacyOpCodeHandlerKind::EVEX:
			elem = std::make_shared<OpCodeHandler_EVEX>(deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::VEX2:
			elem = std::make_shared<OpCodeHandler_VEX2>(deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::VEX3:
			elem = std::make_shared<OpCodeHandler_VEX3>(deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::XOP:
			elem = std::make_shared<OpCodeHandler_XOP>(deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::AL_DX:
			elem = std::make_shared<OpCodeHandler_AL_DX>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Ap:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ap>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::B_BM:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_B_BM>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::B_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_B_Ev>(code, (Code)(code + 1), deserializer.ReadBoolean());
			return 1;
		case LegacyOpCodeHandlerKind::B_MIB:
			elem = std::make_shared<OpCodeHandler_B_MIB>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::BM_B:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_BM_B>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::BranchIw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_BranchIw>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::BranchSimple:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_BranchSimple>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::C_R_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_C_R>(code, (Code)(code + 1), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::C_R_3b:
			elem = std::make_shared<OpCodeHandler_C_R>(deserializer.ReadCode(), Code::INVALID, deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::DX_AL:
			elem = std::make_shared<OpCodeHandler_DX_AL>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::DX_eAX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_DX_eAX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::eAX_DX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_eAX_DX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Eb_1:
			elem = std::make_shared<OpCodeHandler_Eb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_2:
			elem = std::make_shared<OpCodeHandler_Eb>(deserializer.ReadCode(), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_CL:
			elem = std::make_shared<OpCodeHandler_Eb_CL>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_Gb_1:
			elem = std::make_shared<OpCodeHandler_Eb_Gb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_Gb_2:
			elem = std::make_shared<OpCodeHandler_Eb_Gb>(deserializer.ReadCode(), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_Ib_1:
			elem = std::make_shared<OpCodeHandler_Eb_Ib>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Eb_Ib_2:
			elem = std::make_shared<OpCodeHandler_Eb_Ib>(deserializer.ReadCode(), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Eb1:
			elem = std::make_shared<OpCodeHandler_Eb_1>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Ed_V_Ib:
			elem = std::make_shared<OpCodeHandler_Ed_V_Ib>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ep:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ep>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_3b:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev>(code, (Code)(code + 1), Code::INVALID);
			return 1;
		case LegacyOpCodeHandlerKind::Ev_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Ev_CL:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_CL>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_32_64:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv_32_64>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_3b:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv>(code, (Code)(code + 1), Code::INVALID);
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_CL:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv_CL>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_Ib:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv_Ib>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Gv_REX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Gv_REX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Ib_3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Ib>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Ib_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Ib>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Ib2_3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Ib2>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Ib2_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Ib2>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Iz_3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Iz>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Iz_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Iz>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::Ev_P:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_P>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_REXW_1a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_REXW>(code, Code::INVALID, static_cast<std::uint32_t>(deserializer.ReadInt32()));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_REXW:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_REXW>(code, (Code)(code + 1), static_cast<std::uint32_t>(deserializer.ReadInt32()));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_Sw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_Sw>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ev_VX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_VX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ev1:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ev_1>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Evj:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Evj>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Evw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Evw>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Ew:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ew>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gb_Eb:
			elem = std::make_shared<OpCodeHandler_Gb_Eb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Gdq_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gdq_Ev>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Eb:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Eb>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Eb_REX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Eb_REX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_32_64:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev_32_64>(code, (Code)(code + 1), deserializer.ReadBoolean(), deserializer.ReadBoolean());
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_3b:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev>(code, (Code)(code + 1), Code::INVALID);
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_Ib:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev_Ib>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_Ib_REX:
			elem = std::make_shared<OpCodeHandler_Gv_Ev_Ib_REX>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_Iz:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev_Iz>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev_REX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev_REX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev2>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ev3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ev3>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ew:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ew>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_M:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_M>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_M_as:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_M_as>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Ma:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Ma>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Mp_2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Mp>(code, (Code)(code + 1), Code::INVALID);
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Mp_3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Mp>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_Mv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_Mv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_N:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_N>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_N_Ib_REX:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Gv_N_Ib_REX>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_RX:
			elem = std::make_shared<OpCodeHandler_Gv_RX>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Gv_W:
			elem = std::make_shared<OpCodeHandler_Gv_W>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::GvM_VX_Ib:
			elem = std::make_shared<OpCodeHandler_GvM_VX_Ib>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Ib:
			elem = std::make_shared<OpCodeHandler_Ib>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Ib3:
			elem = std::make_shared<OpCodeHandler_Ib3>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::IbReg:
			elem = std::make_shared<OpCodeHandler_IbReg>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::IbReg2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_IbReg2>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Iw_Ib:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Iw_Ib>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Jb:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Jb>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Jb2:
			elem = std::make_shared<OpCodeHandler_Jb2>(deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Jdisp:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Jdisp>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Jx:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Jx>(code, (Code)(code + 1), deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Jz:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Jz>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::M_1:
			elem = std::make_shared<OpCodeHandler_M>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::M_2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_M>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::M_REXW_2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_M_REXW>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::M_REXW_4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_M_REXW>(code, (Code)(code + 1), deserializer.ReadHandlerFlags(), deserializer.ReadHandlerFlags());
			return 1;
		case LegacyOpCodeHandlerKind::MemBx:
			elem = std::make_shared<OpCodeHandler_MemBx>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Mf_1:
			elem = std::make_shared<OpCodeHandler_Mf>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Mf_2a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Mf>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Mf_2b:
			elem = std::make_shared<OpCodeHandler_Mf>(deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::MIB_B:
			elem = std::make_shared<OpCodeHandler_MIB_B>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::MP:
			elem = std::make_shared<OpCodeHandler_MP>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Ms:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ms>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::MV:
			elem = std::make_shared<OpCodeHandler_MV>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Mv_Gv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Mv_Gv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Mv_Gv_REXW:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Mv_Gv_REXW>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::NIb:
			elem = std::make_shared<OpCodeHandler_NIb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Ob_Reg:
			elem = std::make_shared<OpCodeHandler_Ob_Reg>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Ov_Reg:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Ov_Reg>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::P_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_P_Ev>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::P_Ev_Ib:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_P_Ev_Ib>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::P_Q:
			elem = std::make_shared<OpCodeHandler_P_Q>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::P_Q_Ib:
			elem = std::make_shared<OpCodeHandler_P_Q_Ib>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::P_R:
			elem = std::make_shared<OpCodeHandler_P_R>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::P_W:
			elem = std::make_shared<OpCodeHandler_P_W>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::PushEv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushEv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::PushIb2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushIb2>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::PushIz:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushIz>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::PushOpSizeReg_4a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushOpSizeReg>(code, (Code)(code + 1), (Code)(code + 2), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::PushOpSizeReg_4b:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushOpSizeReg>(code, (Code)(code + 1), Code::INVALID, deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::PushSimple2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_PushSimple2>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::PushSimpleReg:
			elem = std::make_shared<OpCodeHandler_PushSimpleReg>(deserializer.ReadInt32(), code = deserializer.ReadCode(), (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Q_P:
			elem = std::make_shared<OpCodeHandler_Q_P>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::R_C_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_R_C>(code, (Code)(code + 1), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::R_C_3b:
			elem = std::make_shared<OpCodeHandler_R_C>(deserializer.ReadCode(), Code::INVALID, deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::rDI_P_N:
			elem = std::make_shared<OpCodeHandler_rDI_P_N>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::rDI_VX_RX:
			elem = std::make_shared<OpCodeHandler_rDI_VX_RX>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Reg:
			elem = std::make_shared<OpCodeHandler_Reg>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Ib2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Ib2>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Iz:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Iz>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Ob:
			elem = std::make_shared<OpCodeHandler_Reg_Ob>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Ov:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Ov>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Xb:
			elem = std::make_shared<OpCodeHandler_Reg_Xb>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Xv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Xv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Xv2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Xv2>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Yb:
			elem = std::make_shared<OpCodeHandler_Reg_Yb>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Reg_Yv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Reg_Yv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::RegIb:
			elem = std::make_shared<OpCodeHandler_RegIb>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::RegIb3:
			elem = std::make_shared<OpCodeHandler_RegIb3>(deserializer.ReadInt32());
			return 1;
		case LegacyOpCodeHandlerKind::RegIz2:
			elem = std::make_shared<OpCodeHandler_RegIz2>(deserializer.ReadInt32());
			return 1;
		case LegacyOpCodeHandlerKind::Reservednop:
			elem = std::make_shared<OpCodeHandler_Reservednop>(deserializer.ReadHandler(), deserializer.ReadHandler());
			return 1;
		case LegacyOpCodeHandlerKind::RIb:
			elem = std::make_shared<OpCodeHandler_RIb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::RIbIb:
			elem = std::make_shared<OpCodeHandler_RIbIb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Rv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Rv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Rv_32_64:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Rv_32_64>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::RvMw_Gw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_RvMw_Gw>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Simple:
			elem = std::make_shared<OpCodeHandler_Simple>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Simple_ModRM:
			elem = std::make_shared<OpCodeHandler_Simple_ModRM>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Simple2_3a:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple2>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Simple2_3b:
			elem = std::make_shared<OpCodeHandler_Simple2>(deserializer.ReadCode(), deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Simple2Iw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple2Iw>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Simple3:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple3>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Simple4:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple4>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Simple4b:
		{
			code = deserializer.ReadCode();
			auto code2 = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple4>(code, code2);
			return 1;
		}
		case LegacyOpCodeHandlerKind::Simple5:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple5>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Simple5_ModRM_as:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Simple5_ModRM_as>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::SimpleReg:
			elem = std::make_shared<OpCodeHandler_SimpleReg>(deserializer.ReadCode(), deserializer.ReadInt32());
			return 1;
		case LegacyOpCodeHandlerKind::ST_STi:
			elem = std::make_shared<OpCodeHandler_ST_STi>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::STi:
			elem = std::make_shared<OpCodeHandler_STi>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::STi_ST:
			elem = std::make_shared<OpCodeHandler_STi_ST>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Sw_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Sw_Ev>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::V_Ev:
			elem = std::make_shared<OpCodeHandler_V_Ev>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::VM:
			elem = std::make_shared<OpCodeHandler_VM>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VN:
			elem = std::make_shared<OpCodeHandler_VN>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VQ:
			elem = std::make_shared<OpCodeHandler_VQ>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VRIbIb:
			elem = std::make_shared<OpCodeHandler_VRIbIb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VW_2:
			elem = std::make_shared<OpCodeHandler_VW>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VW_3:
			elem = std::make_shared<OpCodeHandler_VW>(deserializer.ReadCode(), deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VWIb_2:
			elem = std::make_shared<OpCodeHandler_VWIb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::VWIb_3:
			elem = std::make_shared<OpCodeHandler_VWIb>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::VX_E_Ib:
			elem = std::make_shared<OpCodeHandler_VX_E_Ib>(code = deserializer.ReadCode(), (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::VX_Ev:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_VX_Ev>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Wbinvd:
			elem = std::make_shared<OpCodeHandler_Wbinvd>();
			return 1;
		case LegacyOpCodeHandlerKind::WV:
			elem = std::make_shared<OpCodeHandler_WV>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Xb_Yb:
			elem = std::make_shared<OpCodeHandler_Xb_Yb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Xchg_Reg_rAX:
			elem = std::make_shared<OpCodeHandler_Xchg_Reg_rAX>(deserializer.ReadInt32());
			return 1;
		case LegacyOpCodeHandlerKind::Xv_Yv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Xv_Yv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Yb_Reg:
			elem = std::make_shared<OpCodeHandler_Yb_Reg>(deserializer.ReadCode(), deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Yb_Xb:
			elem = std::make_shared<OpCodeHandler_Yb_Xb>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Yv_Reg:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Yv_Reg>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::Yv_Reg2:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Yv_Reg2>(code, (Code)(code + 1));
			return 1;
		case LegacyOpCodeHandlerKind::Yv_Xv:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Yv_Xv>(code, (Code)(code + 1), (Code)(code + 2));
			return 1;
		case LegacyOpCodeHandlerKind::M_Sw:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_M_Sw>(code);
			return 1;
		case LegacyOpCodeHandlerKind::Sw_M:
			code = deserializer.ReadCode();
			elem = std::make_shared<OpCodeHandler_Sw_M>(code);
			return 1;
		case LegacyOpCodeHandlerKind::Rq:
			elem = std::make_shared<OpCodeHandler_Rq>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::Gd_Rd:
			elem = std::make_shared<OpCodeHandler_Gd_Rd>(deserializer.ReadCode());
			return 1;
		case LegacyOpCodeHandlerKind::PrefixEsCsSsDs:
			elem = std::make_shared<OpCodeHandler_PrefixEsCsSsDs>(deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::PrefixFsGs:
			elem = std::make_shared<OpCodeHandler_PrefixFsGs>(deserializer.ReadRegister());
			return 1;
		case LegacyOpCodeHandlerKind::Prefix66:
			elem = std::make_shared<OpCodeHandler_Prefix66>();
			return 1;
		case LegacyOpCodeHandlerKind::Prefix67:
			elem = std::make_shared<OpCodeHandler_Prefix67>();
			return 1;
		case LegacyOpCodeHandlerKind::PrefixF0:
			elem = std::make_shared<OpCodeHandler_PrefixF0>();
			return 1;
		case LegacyOpCodeHandlerKind::PrefixF2:
			elem = std::make_shared<OpCodeHandler_PrefixF2>();
			return 1;
		case LegacyOpCodeHandlerKind::PrefixF3:
			elem = std::make_shared<OpCodeHandler_PrefixF3>();
			return 1;
		case LegacyOpCodeHandlerKind::PrefixREX:
			elem = std::make_shared<OpCodeHandler_PrefixREX>(deserializer.ReadHandler(), static_cast<std::uint32_t>(deserializer.ReadInt32()));
			return 1;
		default:
			throw InvalidOperationException();
		}
	}
}
