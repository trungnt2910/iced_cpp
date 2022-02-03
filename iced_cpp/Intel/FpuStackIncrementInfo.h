// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once
#if defined(INSTR_INFO)
#include <cstdint>

namespace Iced::Intel
{
	/// <summary>
	/// Contains the FPU <c>TOP</c> increment, whether it's conditional and whether the instruction writes to <c>TOP</c>
	/// </summary>
	class FpuStackIncrementInfo
	{
		/// <summary>
		/// Used if <see cref="WritesTop"/> is <see langword="true"/>:<br/>
		/// <br/>
		/// Value added to <c>TOP</c>.<br/>
		/// <br/>
		/// This is negative if it pushes one or more values and positive if it pops one or more values
		/// and <c>0</c> if it writes to <c>TOP</c> (eg. <c>FLDENV</c>, etc) without pushing/popping anything.
		/// </summary>
	public:
		std::int32_t Increment = 0;
		/// <summary>
		/// <see langword="true"/> if it's a conditional push/pop (eg. <c>FPTAN</c> or <c>FSINCOS</c>)
		/// </summary>
		bool Conditional = false;
		/// <summary>
		/// <see langword="true"/> if <c>TOP</c> is written (it's a conditional/unconditional push/pop, <c>FNSAVE</c>, <c>FLDENV</c>, etc)
		/// </summary>
		bool WritesTop = false;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="increment"></param>
		/// <param name="conditional"></param>
		/// <param name="writesTop"></param>
		constexpr FpuStackIncrementInfo(std::int32_t increment, bool conditional, bool writesTop)
			: Increment(increment), Conditional(conditional), WritesTop(writesTop)
		{
		}

		constexpr FpuStackIncrementInfo() = default;
	};
}
#endif