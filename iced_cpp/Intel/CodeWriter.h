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
	/// Used by an <see cref="Encoder"/> to write encoded instructions
	/// </summary>
	class CodeWriter
	{
	private:
		/// <summary>
		/// Writes the next byte
		/// </summary>
		/// <param name="value">Value</param>
	public:
		virtual void WriteByte(std::uint8_t value) = 0;
	};
}
