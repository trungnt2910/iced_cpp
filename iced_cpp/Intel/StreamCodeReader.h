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

#include "CodeReader.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Code reader from a <see cref="System.IO.Stream"/>. 
	/// </summary>
	class StreamCodeReader final : public CodeReader
	{
		/// <summary>
		/// Creates a new instance of <see cref="StreamCodeReader"/>. 
		/// </summary>
		/// <param name="stream">The input stream</param>
	public:
		StreamCodeReader(class Stream* stream);
		/// <summary>
		/// The stream this instance is writing to
		/// </summary>
		class Stream* Stream;
		/// <summary>
		/// Reads the next byte or returns less than 0 if there are no more bytes
		/// </summary>
		/// <returns></returns>
		std::int32_t ReadByte() override;
	};
}
