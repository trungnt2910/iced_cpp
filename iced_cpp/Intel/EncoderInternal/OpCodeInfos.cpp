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

	std::vector<OpCodeInfo*> OpCodeInfos::Infos = CreateInfos();

	std::vector<OpCodeInfo*> OpCodeInfos::CreateInfos()
	{
		auto infos = std::vector<OpCodeInfo*>(IcedConstants::CodeEnumCount);
		auto encFlags1 = EncoderData::EncFlags1;
		auto encFlags2 = EncoderData::EncFlags2;
		auto encFlags3 = EncoderData::EncFlags3;
		auto opcFlags1 = OpCodeInfoData::OpcFlags1;
		auto opcFlags2 = OpCodeInfoData::OpcFlags2;
		auto sb = new StringBuilder();
		for (std::int32_t i = 0; i < infos.size(); i++)
		{
			infos[i] = new OpCodeInfo(static_cast<Code>(i), static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), static_cast<EncFlags3>(encFlags3[i]), static_cast<OpCodeInfoFlags1>(opcFlags1[i]), static_cast<OpCodeInfoFlags2>(opcFlags2[i]), sb);
		}
		return infos;
	}
}
