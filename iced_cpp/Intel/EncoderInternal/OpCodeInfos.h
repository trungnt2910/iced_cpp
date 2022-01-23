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
		static consteval std::array<OpCodeInfo, IcedConstants::CodeEnumCount> CreateInfos(const char* pos = nullptr)
		{
			auto infos = std::array<OpCodeInfo, IcedConstants::CodeEnumCount>();
			const auto& encFlags1 = EncoderData::EncFlags1;
			const auto& encFlags2 = EncoderData::EncFlags2;
			const auto& encFlags3 = EncoderData::EncFlags3;
			const auto& opcFlags1 = OpCodeInfoData::OpcFlags1;
			const auto& opcFlags2 = OpCodeInfoData::OpcFlags2;

			for (std::int32_t i = 0; i < infos.size(); i++)
			{
				std::construct_at<OpCodeInfo>(&infos[i], static_cast<Code>(i), static_cast<EncFlags1>(encFlags1[i]), static_cast<EncFlags2>(encFlags2[i]), static_cast<EncFlags3>(encFlags3[i]), static_cast<OpCodeInfoFlags1>(opcFlags1[i]), static_cast<OpCodeInfoFlags2>(opcFlags2[i]));
				if (pos != nullptr)
				{
					std::size_t tempLength = infos[i].toOpCodeString.length();
					infos[i].toOpCodeString.~basic_string();
					infos[i].toOpCodeCharPtr = pos;
					pos += tempLength + 1;

					tempLength = infos[i].toInstructionString.length();
					infos[i].toInstructionString.~basic_string();
					infos[i].toInstructionCharPtr = pos;
					pos += tempLength + 1;

					infos[i].useCharPtr = true;
				}
			}
			return infos;
		}
		static consteval std::size_t CreateSize()
		{
			auto infos = CreateInfos();
			std::size_t result = 0;
			for (const auto& i : infos)
			{
				result += i.toOpCodeString.size() + 1;
				result += i.toInstructionString.size() + 1;
			}
			return result;
		}
		template <std::size_t DataSize>
		static consteval std::array<char, DataSize> CreateArray()
		{
			std::array<char, DataSize> result;
			char* pos = result.data();
			auto infos = CreateInfos();
			for (const auto& i : infos)
			{
				pos += Internal::StringHelpers::Copy(i.toOpCodeString.c_str(), pos);
				*pos = '\0'; ++pos;
				pos += Internal::StringHelpers::Copy(i.toInstructionString.c_str(), pos);
				*pos = '\0'; ++pos;
			}
			return result;
		}
	};

	class OpCodeInfos final
	{
	private:
		inline static constexpr std::size_t DataSize = OpCodeInfosInternal::CreateSize();
		inline static constexpr std::array<char, DataSize> Data = OpCodeInfosInternal::CreateArray<DataSize>();
	public:
		inline static constexpr std::array<OpCodeInfo, IcedConstants::CodeEnumCount> Infos = OpCodeInfosInternal::CreateInfos(Data.data());
	};

}
