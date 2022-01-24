// C# helper headers

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
		FpuStackIncrementInfo(std::int32_t increment, bool conditional, bool writesTop);

		FpuStackIncrementInfo() = default;
	};
}
