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
		Iced::Intel::Instruction Instruction;

		/// <summary>
		/// The instruction that couldn't be encoded
		/// </summary>
	public:
		Iced::Intel::Instruction GetInstruction() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">Exception message</param>
		/// <param name="instruction">Instruction</param>
		EncoderException(const std::string& message, Iced::Intel::Instruction const instruction);
	};
}
