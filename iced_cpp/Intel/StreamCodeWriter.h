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

#include "CodeWriter.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Code writer to a <see cref="System.IO.Stream"/>. 
	/// </summary>
	class StreamCodeWriter final : public CodeWriter
	{
		/// <summary>
		/// Creates a new instance of <see cref="StreamCodeWriter"/>. 
		/// </summary>
		/// <param name="stream">The output stream</param>
	public:
		StreamCodeWriter(Stream* stream);
		/// <summary>
		/// The stream this instance is writing to
		/// </summary>
		Stream* Stream;
		/// <summary>
		/// Writes the next byte
		/// </summary>
		/// <param name="value">Value</param>
		void WriteByte(std::uint8_t value) override;
	};
}
