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

#include "OpCodeInfos.h"
#include "../Iced.Intel.IcedConstants.h"
#include "EncoderData.g.h"
#include "OpCodeInfoData.g.h"
#include "../Code.g.h"
#include "Enums.h"
#include "OpCodeInfosEnums.h"

namespace Iced::Intel::EncoderInternal
{

	const std::vector<OpCodeInfo*> OpCodeInfos::Infos = CreateInfos();

	std::vector<OpCodeInfo*> OpCodeInfos::CreateInfos()
	{
		auto infos = std::vector<OpCodeInfo*>(IcedConstants::CodeEnumCount);
		const auto& encFlags1 = EncoderData::EncFlags1;
		const auto& encFlags2 = EncoderData::EncFlags2;
		const auto& encFlags3 = EncoderData::EncFlags3;
		const auto& opcFlags1 = OpCodeInfoData::OpcFlags1;
		const auto& opcFlags2 = OpCodeInfoData::OpcFlags2;
		const auto& sb = new StringBuilder();
		for (std::int32_t i = 0; i < infos.size(); i++)
		{
			infos[i] = new OpCodeInfo(static_cast<Code>(i), static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), static_cast<EncFlags3>(encFlags3[i]), static_cast<OpCodeInfoFlags1>(opcFlags1[i]), static_cast<OpCodeInfoFlags2>(opcFlags2[i]), sb);
		}
		return infos;
	}
}
