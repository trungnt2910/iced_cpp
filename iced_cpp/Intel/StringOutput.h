// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "FormatterOutput.h"
#include "FormatterTextKind.g.h"
#include <string>

namespace Iced::Intel
{
	/// <summary>
	/// Formatter output that stores the formatted text in a <see cref="StringBuilder"/>
	/// </summary>
	class StringOutput final : public FormatterOutput
	{
	private:
		std::string sb;
		/// <summary>
		/// Constructor
		/// </summary>
	public:
		constexpr StringOutput() = default;
		/// </summary>
		/// Writes text and text kind
		/// </summary>
		/// <param name="text">Text, can be an empty string</param>
		/// <param name="kind">Text kind. This value can be identical to the previous value passed to this method. It's
		/// the responsibility of the implementer to merge any such strings if needed.</param>
		constexpr void Write(const std::string& text, FormatterTextKind kind) override
		{
			sb.append(text);
		}
		/// <summary>
		/// Clears the <see cref="StringBuilder"/> instance so this class can be reused to format the next instruction
		/// </summary>
		constexpr void Reset()
		{
			sb.clear();
		}
		/// <summary>
		/// Returns the current formatted text and clears the <see cref="std::string"/> instance so this class can be reused to format the next instruction
		/// </summary>
		/// <returns></returns>
		constexpr std::string ToStringAndReset()
		{
			std::string temp;
			// Unlike the author who creates a copy of the string and then call Reset(),
			// we can take advantage of the empty string.
			temp.swap(sb);
			return temp;
		}
		/// <summary>
		/// Gets the current output
		/// </summary>
		/// <returns></returns>
		constexpr const std::string& ToString()
		{
			return sb;
		}
	};
}
