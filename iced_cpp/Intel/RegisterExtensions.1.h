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
#include <limits>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// <see cref="Register"/> information
	/// </summary>
	class RegisterInfo
	{
		/* readonly */
	private:
		std::uint8_t register_ = 0;
		/* readonly */
		std::uint8_t baseRegister = 0;
		/* readonly */
		std::uint8_t fullRegister = 0;
		/* readonly */
		std::uint16_t size = 0;
		/* readonly */
		std::uint8_t pad1 = 0, pad2 = 0, pad3 = 0;
		/// <summary>
		/// Gets the register
		/// </summary>
	public:
		Iced::Intel::Register GetRegister() const;
		/// <summary>
		/// Gets the base register, eg. <c>AL</c>, <c>AX</c>, <c>EAX</c>, <c>RAX</c>, <c>MM0</c>, <c>XMM0</c>, <c>YMM0</c>, <c>ZMM0</c>, <c>ES</c>
		/// </summary>
		Iced::Intel::Register GetBase() const;
		/// <summary>
		/// The register number (index) relative to <see cref="Base"/>, eg. 0-15, or 0-31, or if 8-bit GPR, 0-19
		/// </summary>
		std::int32_t GetNumber() const;
		/// <summary>
		/// The full register that this one is a part of, eg. <c>CL</c>/<c>CH</c>/<c>CX</c>/<c>ECX</c>/<c>RCX</c> -> <c>RCX</c>, <c>XMM11</c>/<c>YMM11</c>/<c>ZMM11</c> -> <c>ZMM11</c>
		/// </summary>
		Iced::Intel::Register GetFullRegister() const;
		/// <summary>
		/// Gets the full register that this one is a part of, except if it's a GPR in which case the 32-bit register is returned,
		/// eg. <c>CL</c>/<c>CH</c>/<c>CX</c>/<c>ECX</c>/<c>RCX</c> -> <c>ECX</c>, <c>XMM11</c>/<c>YMM11</c>/<c>ZMM11</c> -> <c>ZMM11</c>
		/// </summary>
		Iced::Intel::Register GetFullRegister32() const;
		/// <summary>
		/// Size of the register in bytes
		/// </summary>
		std::int32_t GetSize() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="register">Register</param>
		/// <param name="baseRegister">Base register, eg. AL, AX, EAX, RAX, XMM0, YMM0, ZMM0, ES</param>
		/// <param name="fullRegister">Full register, eg. RAX, ZMM0, ES</param>
		/// <param name="size">Size of register in bytes</param>
		RegisterInfo(Iced::Intel::Register register_, Iced::Intel::Register baseRegister, Iced::Intel::Register fullRegister, std::int32_t size);

		RegisterInfo() = default;
	};
}
