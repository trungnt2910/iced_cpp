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

#include "../BlockEncoder.h"
#include "Label.h"
#include <vector>
#include <stdexcept>
#include <format>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Result of <see cref="Assembler.Assemble"/>.
	/// </summary>
	class AssemblerResult
	{
	public:
		AssemblerResult(std::vector<BlockEncoderResult>& result);
		/// <summary>
		/// The associated block encoder result.
		/// </summary>
		std::vector<BlockEncoderResult> Result;
		/// <summary>
		/// Gets the RIP of the specified label.
		/// </summary>
		/// <param name="label">A label.</param>
		/// <param name="index">Result index</param>
		/// <returns>RIP of the label.</returns>
		std::uint64_t GetLabelRIP(Label* const label, std::int32_t index = 0);

		AssemblerResult() = default;
	};
}
