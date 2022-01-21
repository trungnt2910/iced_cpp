#pragma once

#include <array>
#include <algorithm>
#include <string>
#include "InstructionFormatter.defs.h"
#include "OpCodeFormatter.defs.h"
#include "OpCodeInfos.h"

namespace Iced::Intel::EncoderInternal
{
	class OpCodeInfoStringsInternal
	{
	private:
		friend class OpCodeInfoStrings;
		static consteval int GetDataSize()
		{
			int result = 0;
			const auto& infos = OpCodeInfos::Infos;
			for (const auto& i : infos)
			{
				// null terminated
				result += (int)OpCodeFormatter(i, i.lkind, (i.opcFlags1 & OpCodeInfoFlags1::ModRegRmString) != 0).Format().size() + 1;
				auto fmtOption = static_cast<InstrStrFmtOption>((static_cast<std::uint32_t>(i.opcFlags2) >> static_cast<std::int32_t>(OpCodeInfoFlags2::InstrStrFmtOptionShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags2::InstrStrFmtOptionMask));
				result += (int)InstructionFormatter(i, fmtOption).Format().size() + 1;
			}
			return result;
		}
		template <int DataSize>
		static consteval std::array<char, DataSize> GetData()
		{
			std::array<char, DataSize> result;
			const auto& infos = OpCodeInfos::Infos;
			std::int32_t pos = 0;
			for (const auto& i : infos)
			{
				// null terminated
				std::string opCodeString = OpCodeFormatter(i, i.lkind, (i.opcFlags1 & OpCodeInfoFlags1::ModRegRmString) != 0).Format();
				auto fmtOption = static_cast<InstrStrFmtOption>((static_cast<std::uint32_t>(i.opcFlags2) >> static_cast<std::int32_t>(OpCodeInfoFlags2::InstrStrFmtOptionShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags2::InstrStrFmtOptionMask));
				std::string instructionString = InstructionFormatter(i, fmtOption).Format();

				std::copy(opCodeString.begin(), opCodeString.end(), result.begin() + pos);
				pos += (int)opCodeString.size();
				result[pos] = 0;
				++pos;
				std::copy(instructionString.begin(), instructionString.end(), result.begin() + pos);
				pos += (int)instructionString.size();
				result[pos] = 0;
				++pos;
			}
			return result;
		}
	};


	class OpCodeInfoStrings
	{
		inline static constexpr int DataSize = OpCodeInfoStringsInternal::GetDataSize();

	public:
		inline static constexpr std::array<char, DataSize> Data = OpCodeInfoStringsInternal::GetData<DataSize>();
	};
}