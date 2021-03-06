// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "Iced.Intel.Instruction.h"
#include <string>
#include <stdexcept>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Thrown if the encoder can't encode an instruction
	/// </summary>
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [Serializable] public class EncoderException : Exception
	class EncoderException : public std::runtime_error
	{
	private:
		const class Instruction Instruction;

		/// <summary>
		/// The instruction that couldn't be encoded
		/// </summary>
	public:
		const class Instruction& GetInstruction() const
		{
			return Instruction;
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">Exception message</param>
		/// <param name="instruction">Instruction</param>
		EncoderException(const std::string& message, const class Instruction& instruction) : std::runtime_error(message), Instruction(instruction)
		{
		}
	};
}
