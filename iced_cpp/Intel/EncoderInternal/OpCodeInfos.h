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
	class OpCodeInfosInternal
	{
		friend class OpCodeInfos;
	private:
		static consteval std::array<OpCodeInfo, IcedConstants::CodeEnumCount> CreateInfos()
		{
			auto infos = std::array<OpCodeInfo, IcedConstants::CodeEnumCount>();
			const auto& encFlags1 = EncoderData::EncFlags1;
			const auto& encFlags2 = EncoderData::EncFlags2;
			const auto& encFlags3 = EncoderData::EncFlags3;
			const auto& opcFlags1 = OpCodeInfoData::OpcFlags1;
			const auto& opcFlags2 = OpCodeInfoData::OpcFlags2;
			int index = 0;

			for (std::int32_t i = 0; i < infos.size(); i++)
			{
				std::construct_at<OpCodeInfo>(&infos[i], static_cast<Code>(i), static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), static_cast<EncFlags3>(encFlags3[i]), static_cast<OpCodeInfoFlags1>(opcFlags1[i]), static_cast<OpCodeInfoFlags2>(opcFlags2[i]));
				infos[i].toOpCodeStringIndex = index;

				index += (int)OpCodeFormatter(infos[i], infos[i].lkind, (infos[i].opcFlags1 & OpCodeInfoFlags1::ModRegRmString) != 0).Format().size() + 1;

				infos[i].toInstructionStringIndex = index;
				auto fmtOption = static_cast<InstrStrFmtOption>((static_cast<std::uint32_t>(infos[i].opcFlags2) >> static_cast<std::int32_t>(OpCodeInfoFlags2::InstrStrFmtOptionShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags2::InstrStrFmtOptionMask));
				index += (int)InstructionFormatter(infos[i], fmtOption).Format().size() + 1;

			}
			return infos;
		}
	};

	class OpCodeInfos final
	{
	public:
		inline static constexpr std::array<OpCodeInfo, IcedConstants::CodeEnumCount> Infos = OpCodeInfosInternal::CreateInfos();
	};

}
