// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "FormatterString.h"
#include <array>

#include "../Internal/DataReader.h"
#include "../IcedConstants.h"

namespace Iced::Intel::FormatterInternal
{
	class RegistersTable final
	{
		// GENERATOR-BEGIN: Registers
		// ⚠️This was generated by GENERATOR!🦹‍♂️
	private:
		inline static constexpr std::array RegistersData = std::to_array<std::uint8_t>({ 0x03, 0x3F, 0x3F, 0x3F, 0x02, 0x61, 0x6C, 0x02, 0x63, 0x6C, 0x02, 0x64, 0x6C, 0x02, 0x62, 0x6C, 0x02, 0x61, 0x68, 0x02, 0x63, 0x68, 0x02, 0x64, 0x68, 0x02, 0x62, 0x68, 0x03, 0x73, 0x70, 0x6C, 0x03, 0x62, 0x70, 0x6C, 0x03, 0x73, 0x69, 0x6C, 0x03, 0x64, 0x69, 0x6C, 0x03, 0x72, 0x38, 0x62, 0x03, 0x72, 0x39, 0x62, 0x04, 0x72, 0x31, 0x30, 0x62, 0x04, 0x72, 0x31, 0x31, 0x62, 0x04, 0x72, 0x31, 0x32, 0x62, 0x04, 0x72, 0x31, 0x33, 0x62, 0x04, 0x72, 0x31, 0x34, 0x62, 0x04, 0x72, 0x31, 0x35, 0x62, 0x02, 0x61, 0x78, 0x02, 0x63, 0x78, 0x02, 0x64, 0x78, 0x02, 0x62, 0x78, 0x02, 0x73, 0x70, 0x02, 0x62, 0x70, 0x02, 0x73, 0x69, 0x02, 0x64, 0x69, 0x03, 0x72, 0x38, 0x77, 0x03, 0x72, 0x39, 0x77, 0x04, 0x72, 0x31, 0x30, 0x77, 0x04, 0x72, 0x31, 0x31, 0x77, 0x04, 0x72, 0x31, 0x32, 0x77, 0x04, 0x72, 0x31, 0x33, 0x77, 0x04, 0x72, 0x31, 0x34, 0x77, 0x04, 0x72, 0x31, 0x35, 0x77, 0x03, 0x65, 0x61, 0x78, 0x03, 0x65, 0x63, 0x78, 0x03, 0x65, 0x64, 0x78, 0x03, 0x65, 0x62, 0x78, 0x03, 0x65, 0x73, 0x70, 0x03, 0x65, 0x62, 0x70, 0x03, 0x65, 0x73, 0x69, 0x03, 0x65, 0x64, 0x69, 0x03, 0x72, 0x38, 0x64, 0x03, 0x72, 0x39, 0x64, 0x04, 0x72, 0x31, 0x30, 0x64, 0x04, 0x72, 0x31, 0x31, 0x64, 0x04, 0x72, 0x31, 0x32, 0x64, 0x04, 0x72, 0x31, 0x33, 0x64, 0x04, 0x72, 0x31, 0x34, 0x64, 0x04, 0x72, 0x31, 0x35, 0x64, 0x03, 0x72, 0x61, 0x78, 0x03, 0x72, 0x63, 0x78, 0x03, 0x72, 0x64, 0x78, 0x03, 0x72, 0x62, 0x78, 0x03, 0x72, 0x73, 0x70, 0x03, 0x72, 0x62, 0x70, 0x03, 0x72, 0x73, 0x69, 0x03, 0x72, 0x64, 0x69, 0x02, 0x72, 0x38, 0x02, 0x72, 0x39, 0x03, 0x72, 0x31, 0x30, 0x03, 0x72, 0x31, 0x31, 0x03, 0x72, 0x31, 0x32, 0x03, 0x72, 0x31, 0x33, 0x03, 0x72, 0x31, 0x34, 0x03, 0x72, 0x31, 0x35, 0x03, 0x65, 0x69, 0x70, 0x03, 0x72, 0x69, 0x70, 0x02, 0x65, 0x73, 0x02, 0x63, 0x73, 0x02, 0x73, 0x73, 0x02, 0x64, 0x73, 0x02, 0x66, 0x73, 0x02, 0x67, 0x73, 0x04, 0x78, 0x6D, 0x6D, 0x30, 0x04, 0x78, 0x6D, 0x6D, 0x31, 0x04, 0x78, 0x6D, 0x6D, 0x32, 0x04, 0x78, 0x6D, 0x6D, 0x33, 0x04, 0x78, 0x6D, 0x6D, 0x34, 0x04, 0x78, 0x6D, 0x6D, 0x35, 0x04, 0x78, 0x6D, 0x6D, 0x36, 0x04, 0x78, 0x6D, 0x6D, 0x37, 0x04, 0x78, 0x6D, 0x6D, 0x38, 0x04, 0x78, 0x6D, 0x6D, 0x39, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x30, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x31, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x32, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x33, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x34, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x35, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x36, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x37, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x38, 0x05, 0x78, 0x6D, 0x6D, 0x31, 0x39, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x30, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x31, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x32, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x33, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x34, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x35, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x36, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x37, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x38, 0x05, 0x78, 0x6D, 0x6D, 0x32, 0x39, 0x05, 0x78, 0x6D, 0x6D, 0x33, 0x30, 0x05, 0x78, 0x6D, 0x6D, 0x33, 0x31, 0x04, 0x79, 0x6D, 0x6D, 0x30, 0x04, 0x79, 0x6D, 0x6D, 0x31, 0x04, 0x79, 0x6D, 0x6D, 0x32, 0x04, 0x79, 0x6D, 0x6D, 0x33, 0x04, 0x79, 0x6D, 0x6D, 0x34, 0x04, 0x79, 0x6D, 0x6D, 0x35, 0x04, 0x79, 0x6D, 0x6D, 0x36, 0x04, 0x79, 0x6D, 0x6D, 0x37, 0x04, 0x79, 0x6D, 0x6D, 0x38, 0x04, 0x79, 0x6D, 0x6D, 0x39, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x30, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x31, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x32, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x33, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x34, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x35, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x36, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x37, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x38, 0x05, 0x79, 0x6D, 0x6D, 0x31, 0x39, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x30, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x31, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x32, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x33, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x34, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x35, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x36, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x37, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x38, 0x05, 0x79, 0x6D, 0x6D, 0x32, 0x39, 0x05, 0x79, 0x6D, 0x6D, 0x33, 0x30, 0x05, 0x79, 0x6D, 0x6D, 0x33, 0x31, 0x04, 0x7A, 0x6D, 0x6D, 0x30, 0x04, 0x7A, 0x6D, 0x6D, 0x31, 0x04, 0x7A, 0x6D, 0x6D, 0x32, 0x04, 0x7A, 0x6D, 0x6D, 0x33, 0x04, 0x7A, 0x6D, 0x6D, 0x34, 0x04, 0x7A, 0x6D, 0x6D, 0x35, 0x04, 0x7A, 0x6D, 0x6D, 0x36, 0x04, 0x7A, 0x6D, 0x6D, 0x37, 0x04, 0x7A, 0x6D, 0x6D, 0x38, 0x04, 0x7A, 0x6D, 0x6D, 0x39, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x30, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x31, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x32, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x33, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x34, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x35, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x36, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x37, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x38, 0x05, 0x7A, 0x6D, 0x6D, 0x31, 0x39, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x30, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x31, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x32, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x33, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x34, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x35, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x36, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x37, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x38, 0x05, 0x7A, 0x6D, 0x6D, 0x32, 0x39, 0x05, 0x7A, 0x6D, 0x6D, 0x33, 0x30, 0x05, 0x7A, 0x6D, 0x6D, 0x33, 0x31, 0x02, 0x6B, 0x30, 0x02, 0x6B, 0x31, 0x02, 0x6B, 0x32, 0x02, 0x6B, 0x33, 0x02, 0x6B, 0x34, 0x02, 0x6B, 0x35, 0x02, 0x6B, 0x36, 0x02, 0x6B, 0x37, 0x04, 0x62, 0x6E, 0x64, 0x30, 0x04, 0x62, 0x6E, 0x64, 0x31, 0x04, 0x62, 0x6E, 0x64, 0x32, 0x04, 0x62, 0x6E, 0x64, 0x33, 0x03, 0x63, 0x72, 0x30, 0x03, 0x63, 0x72, 0x31, 0x03, 0x63, 0x72, 0x32, 0x03, 0x63, 0x72, 0x33, 0x03, 0x63, 0x72, 0x34, 0x03, 0x63, 0x72, 0x35, 0x03, 0x63, 0x72, 0x36, 0x03, 0x63, 0x72, 0x37, 0x03, 0x63, 0x72, 0x38, 0x03, 0x63, 0x72, 0x39, 0x04, 0x63, 0x72, 0x31, 0x30, 0x04, 0x63, 0x72, 0x31, 0x31, 0x04, 0x63, 0x72, 0x31, 0x32, 0x04, 0x63, 0x72, 0x31, 0x33, 0x04, 0x63, 0x72, 0x31, 0x34, 0x04, 0x63, 0x72, 0x31, 0x35, 0x03, 0x64, 0x72, 0x30, 0x03, 0x64, 0x72, 0x31, 0x03, 0x64, 0x72, 0x32, 0x03, 0x64, 0x72, 0x33, 0x03, 0x64, 0x72, 0x34, 0x03, 0x64, 0x72, 0x35, 0x03, 0x64, 0x72, 0x36, 0x03, 0x64, 0x72, 0x37, 0x03, 0x64, 0x72, 0x38, 0x03, 0x64, 0x72, 0x39, 0x04, 0x64, 0x72, 0x31, 0x30, 0x04, 0x64, 0x72, 0x31, 0x31, 0x04, 0x64, 0x72, 0x31, 0x32, 0x04, 0x64, 0x72, 0x31, 0x33, 0x04, 0x64, 0x72, 0x31, 0x34, 0x04, 0x64, 0x72, 0x31, 0x35, 0x05, 0x73, 0x74, 0x28, 0x30, 0x29, 0x05, 0x73, 0x74, 0x28, 0x31, 0x29, 0x05, 0x73, 0x74, 0x28, 0x32, 0x29, 0x05, 0x73, 0x74, 0x28, 0x33, 0x29, 0x05, 0x73, 0x74, 0x28, 0x34, 0x29, 0x05, 0x73, 0x74, 0x28, 0x35, 0x29, 0x05, 0x73, 0x74, 0x28, 0x36, 0x29, 0x05, 0x73, 0x74, 0x28, 0x37, 0x29, 0x03, 0x6D, 0x6D, 0x30, 0x03, 0x6D, 0x6D, 0x31, 0x03, 0x6D, 0x6D, 0x32, 0x03, 0x6D, 0x6D, 0x33, 0x03, 0x6D, 0x6D, 0x34, 0x03, 0x6D, 0x6D, 0x35, 0x03, 0x6D, 0x6D, 0x36, 0x03, 0x6D, 0x6D, 0x37, 0x03, 0x74, 0x72, 0x30, 0x03, 0x74, 0x72, 0x31, 0x03, 0x74, 0x72, 0x32, 0x03, 0x74, 0x72, 0x33, 0x03, 0x74, 0x72, 0x34, 0x03, 0x74, 0x72, 0x35, 0x03, 0x74, 0x72, 0x36, 0x03, 0x74, 0x72, 0x37, 0x04, 0x74, 0x6D, 0x6D, 0x30, 0x04, 0x74, 0x6D, 0x6D, 0x31, 0x04, 0x74, 0x6D, 0x6D, 0x32, 0x04, 0x74, 0x6D, 0x6D, 0x33, 0x04, 0x74, 0x6D, 0x6D, 0x34, 0x04, 0x74, 0x6D, 0x6D, 0x35, 0x04, 0x74, 0x6D, 0x6D, 0x36, 0x04, 0x74, 0x6D, 0x6D, 0x37, 0x02, 0x73, 0x74, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x3F });
		static constexpr std::int32_t MaxStringLength = 5;
		// GENERATOR-END: Registers
	public:
		static constexpr std::vector<FormatterString> GetRegisters()
		{
			auto reader = Iced::Intel::Internal::DataReader(RegistersData, MaxStringLength);
			auto strings = std::vector<FormatterString>(IcedConstants::RegisterEnumCount);
			for (std::int32_t i = 0; i < strings.size(); i++)
			{
				strings[i] = FormatterString(reader.ReadAsciiString());
			}
			if (reader.GetCanRead())
			{
				throw std::runtime_error("invalid operation");
			}
			return strings;
		}
	};
}


