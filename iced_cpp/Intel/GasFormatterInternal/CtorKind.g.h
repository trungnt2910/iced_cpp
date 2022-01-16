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

#pragma once

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel::GasFormatterInternal
{
	enum class CtorKind
	{
		Previous,
		Normal_1,
		Normal_2a,
		Normal_2b,
		Normal_2c,
		Normal_3,
		AamAad,
		asz,
		bnd,
		ST_STi,
		DeclareData,
		er_2,
		er_4,
		far,
		imul,
		maskmovq,
		movabs,
		nop,
		OpSize,
		OpSize2_bnd,
		OpSize3,
		os,
		STi_ST,
		sae,
		CC_1,
		CC_2,
		CC_3,
		os_jcc_1,
		os_jcc_2,
		os_jcc_3,
		os_loopcc,
		os_loop,
		os_mem,
		Reg16,
		os_mem2,
		os2_3,
		os2_4,
		STIG1,
		pblendvb,
		pclmulqdq,
		pops,
		mem16,
		Reg32
	};

	DEFINE_COMP(CtorKind)
		DEFINE_ARITH(CtorKind)

}
