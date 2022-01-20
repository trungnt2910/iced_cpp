// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "CodeSize.g.h"
#include "Register.g.h"

#include <cstdint>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
namespace Iced::Intel
{
	class InstructionUtils final
	{
	public:
		static constexpr std::int32_t GetAddressSizeInBytes(Register baseReg, Register indexReg, std::int32_t displSize, CodeSize codeSize)
		{
			if ((Register::RAX <= baseReg && baseReg <= Register::R15) || (Register::RAX <= indexReg && indexReg <= Register::R15) || baseReg == Register::RIP)
			{
				return 8;
			}
			if ((Register::EAX <= baseReg && baseReg <= Register::R15D) || (Register::EAX <= indexReg && indexReg <= Register::R15D) || baseReg == Register::EIP)
			{
				return 4;
			}
			if ((Register::AX <= baseReg && baseReg <= Register::DI) || (Register::AX <= indexReg && indexReg <= Register::DI))
			{
				return 2;
			}
			if (displSize == 2 || displSize == 4 || displSize == 8)
			{
				return displSize;
			}
			auto switchTempVar_0 = codeSize;


			return (switchTempVar_0 == CodeSize::Code64) ? static_cast<std::uint8_t>(8) : (switchTempVar_0 == CodeSize::Code32) ? static_cast<std::uint8_t>(4) : (switchTempVar_0 == CodeSize::Code16) ? static_cast<std::uint8_t>(2) : static_cast<std::uint8_t>(8);
		}
	};
}
