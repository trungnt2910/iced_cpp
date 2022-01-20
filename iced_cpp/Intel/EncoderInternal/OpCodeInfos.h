// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "../OpCodeInfo.h"
#include <array>
#include <memory>

#include "EncoderData.g.h"
#include "OpCodeInfoData.g.h"

#include "../Iced.Intel.IcedConstants.h"

namespace Iced::Intel::EncoderInternal
{
	namespace Internal
	{
		consteval std::array<OpCodeInfo, IcedConstants::CodeEnumCount> CreateInfos()
		{
			auto infos = std::array<OpCodeInfo, IcedConstants::CodeEnumCount>();
			const auto& encFlags1 = EncoderData::EncFlags1;
			const auto& encFlags2 = EncoderData::EncFlags2;
			const auto& encFlags3 = EncoderData::EncFlags3;
			const auto& opcFlags1 = OpCodeInfoData::OpcFlags1;
			const auto& opcFlags2 = OpCodeInfoData::OpcFlags2;
			for (std::int32_t i = 0; i < infos.size(); i++)
			{
				std::construct_at<OpCodeInfo>(&infos[i], OpCodeInfo(static_cast<Code>(i), static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), static_cast<EncFlags3>(encFlags3[i]), static_cast<OpCodeInfoFlags1>(opcFlags1[i]), static_cast<OpCodeInfoFlags2>(opcFlags2[i])));
			}
			return infos;
		}
	}

	class OpCodeInfos final
	{
	public:
		inline static constexpr std::array<OpCodeInfo, IcedConstants::CodeEnumCount> Infos = Internal::CreateInfos();
	};

}
