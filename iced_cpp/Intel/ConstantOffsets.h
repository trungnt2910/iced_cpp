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
namespace Iced::Intel
{
	/// <summary>
	/// Contains the offsets of the displacement and immediate. Call the decoder's GetConstantOffsets() method
	/// to get the offsets of the constants after the instruction has been decoded. The encoder has a similar method.
	/// </summary>
	class ConstantOffsets
	{
		/// <summary>
		/// The offset of the displacement, if any
		/// </summary>
	public:
		std::uint8_t DisplacementOffset = 0;
		/// <summary>
		/// Size in bytes of the displacement, or 0 if there's no displacement
		/// </summary>
		std::uint8_t DisplacementSize = 0;
		/// <summary>
		/// The offset of the first immediate, if any.
		/// 
		/// This field can be invalid even if the operand has an immediate if it's an immediate that isn't part
		/// of the instruction stream, eg. <c>SHL AL,1</c>.
		/// </summary>
		std::uint8_t ImmediateOffset = 0;
		/// <summary>
		/// Size in bytes of the first immediate, or 0 if there's no immediate
		/// </summary>
		std::uint8_t ImmediateSize = 0;
		/// <summary>
		/// The offset of the second immediate, if any.
		/// </summary>
		std::uint8_t ImmediateOffset2 = 0;
		/// <summary>
		/// Size in bytes of the second immediate, or 0 if there's no second immediate
		/// </summary>
		std::uint8_t ImmediateSize2 = 0;
		// pad to 8 bytes so the jitter can generate better code
	private:
		std::uint8_t pad1 = 0;
		std::uint8_t pad2 = 0;
		/// <summary>
		/// <see langword="true"/> if <see cref="DisplacementOffset"/> and <see cref="DisplacementSize"/> are valid
		/// </summary>
	public:
		bool GetHasDisplacement() const;
		/// <summary>
		/// <see langword="true"/> if <see cref="ImmediateOffset"/> and <see cref="ImmediateSize"/> are valid
		/// </summary>
		bool GetHasImmediate() const;
		/// <summary>
		/// <see langword="true"/> if <see cref="ImmediateOffset2"/> and <see cref="ImmediateSize2"/> are valid
		/// </summary>
		bool GetHasImmediate2() const;
	};
}
