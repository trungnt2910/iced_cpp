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

#include "FormatterOutput.h"
#include "FormatterTextKind.g.h"
#include <string>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Formatter output that stores the formatted text in a <see cref="StringBuilder"/>
	/// </summary>
	class StringOutput final : public FormatterOutput
	{
		/* readonly */
	private:
		StringBuilder* sb;
		/// <summary>
		/// Constructor
		/// </summary>
	public:
		StringOutput();
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="sb">String builder</param>
		StringOutput(StringBuilder* sb);
		/// <summary>
		/// Writes text and text kind
		/// </summary>
		/// <param name="text">Text, can be an empty string</param>
		/// <param name="kind">Text kind. This value can be identical to the previous value passed to this method. It's
		/// the responsibility of the implementer to merge any such strings if needed.</param>
		void Write(const std::string& text, FormatterTextKind kind) override;
		/// <summary>
		/// Clears the <see cref="StringBuilder"/> instance so this class can be reused to format the next instruction
		/// </summary>
		void Reset();
		/// <summary>
		/// Returns the current formatted text and clears the <see cref="StringBuilder"/> instance so this class can be reused to format the next instruction
		/// </summary>
		/// <returns></returns>
		std::string ToStringAndReset();
		/// <summary>
		/// Gets the current output
		/// </summary>
		/// <returns></returns>
		std::string ToString();
	};
}
