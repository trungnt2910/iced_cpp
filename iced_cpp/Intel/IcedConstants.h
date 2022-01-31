// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "IcedConstants.g.h"
#include "Code.g.h"

namespace Iced::Intel
{
	namespace IcedConstants
	{
#if defined(MVEX)
		constexpr bool IsMvex(Code code)
		{
			return (static_cast<std::uint32_t>(code) - MvexStart) < MvexLength;
		}
#else
		constexpr bool IsMvex(Code code)
		{
			return false;
		}
#endif
	}
}