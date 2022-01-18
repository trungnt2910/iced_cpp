#pragma once

#include "Register.g.h"
#include "RegisterExtensions.defs.h"

#include <cassert>
#include <cstdint>
#include <climits>
#include <limits>

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
		constexpr Iced::Intel::Register GetRegister() const;
		/// <summary>
		/// Gets the base register, eg. <c>AL</c>, <c>AX</c>, <c>EAX</c>, <c>RAX</c>, <c>MM0</c>, <c>XMM0</c>, <c>YMM0</c>, <c>ZMM0</c>, <c>ES</c>
		/// </summary>
		constexpr Iced::Intel::Register GetBase() const;
		/// <summary>
		/// The register number (index) relative to <see cref="Base"/>, eg. 0-15, or 0-31, or if 8-bit GPR, 0-19
		/// </summary>
		constexpr std::int32_t GetNumber() const;
		/// <summary>
		/// The full register that this one is a part of, eg. <c>CL</c>/<c>CH</c>/<c>CX</c>/<c>ECX</c>/<c>RCX</c> -> <c>RCX</c>, <c>XMM11</c>/<c>YMM11</c>/<c>ZMM11</c> -> <c>ZMM11</c>
		/// </summary>
		constexpr Iced::Intel::Register GetFullRegister() const;
		/// <summary>
		/// Gets the full register that this one is a part of, except if it's a GPR in which case the 32-bit register is returned,
		/// eg. <c>CL</c>/<c>CH</c>/<c>CX</c>/<c>ECX</c>/<c>RCX</c> -> <c>ECX</c>, <c>XMM11</c>/<c>YMM11</c>/<c>ZMM11</c> -> <c>ZMM11</c>
		/// </summary>
		constexpr Iced::Intel::Register GetFullRegister32() const;
		/// <summary>
		/// Size of the register in bytes
		/// </summary>
		constexpr std::int32_t GetSize() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="register">Register</param>
		/// <param name="baseRegister">Base register, eg. AL, AX, EAX, RAX, XMM0, YMM0, ZMM0, ES</param>
		/// <param name="fullRegister">Full register, eg. RAX, ZMM0, ES</param>
		/// <param name="size">Size of register in bytes</param>
		constexpr RegisterInfo(Iced::Intel::Register register_, Iced::Intel::Register baseRegister, Iced::Intel::Register fullRegister, std::int32_t size);

		constexpr RegisterInfo() = default;
	};

	constexpr Iced::Intel::Register RegisterInfo::GetRegister() const
	{
		return static_cast<Iced::Intel::Register>(register_);
	}

	constexpr Iced::Intel::Register RegisterInfo::GetBase() const
	{
		return static_cast<Iced::Intel::Register>(baseRegister);
	}

	constexpr std::int32_t RegisterInfo::GetNumber() const
	{
		return register_ - baseRegister;
	}

	constexpr Iced::Intel::Register RegisterInfo::GetFullRegister() const
	{
		return static_cast<Iced::Intel::Register>(fullRegister);
	}

	constexpr Iced::Intel::Register RegisterInfo::GetFullRegister32() const
	{
		auto fullRegister = static_cast<Iced::Intel::Register>(this->fullRegister);
		if (Iced::Intel::RegisterExtensions::IsGPR(fullRegister))
		{
			assert(Register::RAX <= fullRegister && fullRegister <= Register::R15);
			return (Register)(fullRegister - Register::RAX + Register::EAX);
		}
		return fullRegister;
	}

	constexpr std::int32_t RegisterInfo::GetSize() const
	{
		return size;
	}

	constexpr RegisterInfo::RegisterInfo(Iced::Intel::Register register_, Iced::Intel::Register baseRegister, Iced::Intel::Register fullRegister, std::int32_t size)
	{
		assert(baseRegister <= register_);
		assert(static_cast<std::uint32_t>(register_) <= std::numeric_limits<std::uint8_t>::max());
		this->register_ = static_cast<std::uint8_t>(register_);
		assert(static_cast<std::uint32_t>(baseRegister) <= std::numeric_limits<std::uint8_t>::max());
		this->baseRegister = static_cast<std::uint8_t>(baseRegister);
		assert(static_cast<std::uint32_t>(fullRegister) <= std::numeric_limits<std::uint8_t>::max());
		this->fullRegister = static_cast<std::uint8_t>(fullRegister);
		assert(static_cast<std::uint32_t>(size) <= std::numeric_limits<std::uint16_t>::max());
		this->size = static_cast<std::uint16_t>(size);
		pad1 = 0;
		pad2 = 0;
		pad3 = 0;
	}
}
