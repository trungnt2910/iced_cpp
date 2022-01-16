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

#include "MvexTupleTypeLutKind.g.h"
#include "MvexEHBit.g.h"
#include "MvexConvFn.g.h"
#include "Code.g.h"
#include "TupleType.g.h"
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/* readonly */
	class MvexInfo
	{
		/* readonly */
	private:
		std::int32_t index = 0;
	public:
		MvexTupleTypeLutKind GetTupleTypeLutKind() const;
		MvexEHBit GetEHBit() const;
		MvexConvFn GetConvFn() const;
		std::uint32_t GetInvalidConvFns() const;
		std::uint32_t GetInvalidSwizzleFns() const;
		bool IsNDD() const;
		bool IsNDS() const;
		bool GetCanUseEvictionHint() const;
		bool GetCanUseImmRoundingControl() const;
		bool GetCanUseRoundingControl() const;
		bool GetCanUseSuppressAllExceptions() const;
		bool GetIgnoresOpMaskRegister() const;
		bool GetRequireOpMaskRegister() const;
		bool GetNoSaeRc() const;
		bool IsConvFn32() const;
		bool GetIgnoresEvictionHint() const;
		MvexInfo(Code code);
		TupleType GetTupleType(std::int32_t sss);

		MvexInfo() = default;
	};
}
