// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "Register.g.h"
#include "OpAccess.g.h"
#include <string>

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
		constexpr Iced::Intel::Register GetRegister() const;
		/// <summary>
		/// Register access
		/// </summary>
		constexpr OpAccess GetAccess() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="register">Register</param>
		/// <param name="access">Register access</param>
		constexpr UsedRegister(Iced::Intel::Register register_, OpAccess access);
		/// <summary>
		/// ToString()
		/// </summary>
		/// <returns></returns>
		constexpr std::string ToString() const;

		constexpr UsedRegister() = default;
	};

	constexpr Iced::Intel::Register UsedRegister::GetRegister() const
	{
		return register_;
	}

	constexpr OpAccess UsedRegister::GetAccess() const
	{
		return access;
	}

	constexpr UsedRegister::UsedRegister(Iced::Intel::Register register_, OpAccess access)
	{
		this->register_ = register_;
		this->access = access;
	}

	constexpr std::string UsedRegister::ToString() const
	{
		return Iced::Intel::ToString(GetRegister()) + ":" + Iced::Intel::ToString(GetAccess());
	}
}
