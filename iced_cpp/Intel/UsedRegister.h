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

#include "Register.g.h"
#include "OpAccess.g.h"
#include <string>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// A register used by an instruction
	/// </summary>
	class UsedRegister
	{
		/* readonly */
	private:
		Iced::Intel::Register register_ = static_cast<Iced::Intel::Register>(0);
		/* readonly */
		OpAccess access = static_cast<OpAccess>(0);
		/// <summary>
		/// Register
		/// </summary>
	public:
		Iced::Intel::Register GetRegister() const;
		/// <summary>
		/// Register access
		/// </summary>
		OpAccess GetAccess() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="register">Register</param>
		/// <param name="access">Register access</param>
		UsedRegister(Iced::Intel::Register register_, OpAccess access);
		/// <summary>
		/// ToString()
		/// </summary>
		/// <returns></returns>
		std::string ToString();

		UsedRegister() = default;
	};
}
