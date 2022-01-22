// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



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
namespace Iced::Intel::MasmFormatterInternal
{
	enum class CtorKind
	{
		Previous,
		Normal_1,
		Normal_2,
		AamAad,
		AX,
		AY,
		bnd,
		STIG1,
		DeclareData,
		DX,
		fword,
		Int3,
		imul,
		invlpga,
		CCa_1,
		CCa_2,
		CCa_3,
		CCb_1,
		CCb_2,
		CCb_3,
		jcc_1,
		jcc_2,
		jcc_3,
		Loopcc1,
		Loopcc2,
		maskmovq,
		memsize,
		YD,
		YX,
		monitor,
		mwait,
		mwaitx,
		nop,
		OpSize_1,
		OpSize_2,
		OpSize2,
		YA,
		pblendvb,
		pclmulqdq,
		pops_2,
		pops_3,
		XY,
		reg,
		Reg16,
		Reg32,
		reverse,
		ST_STi,
		STi_ST,
		XLAT
	};

	DEFINE_COMP(CtorKind)
		DEFINE_ARITH(CtorKind)

}
