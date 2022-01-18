#pragma once

#include <csharp/classes.h>

#include <string>

#include "../Register.g.h"
#include "../RegisterExtensions.h"
#include "AssemblerOperandFlags.h"
#include "AssemblerMemoryOperand.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	/// <summary>
	/// An assembler register used with <see cref="Assembler"/>.
	/// </summary>
	class AssemblerRegisterZMM
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A Register</param>
	public:
		constexpr AssemblerRegisterZMM(Register value);
		/// <summary>
		/// The register value.
		/// </summary>
		Register Value = static_cast<Register>(0);
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A register</param>
		/// <param name="flags">The mask</param>
		constexpr AssemblerRegisterZMM(Register value, AssemblerOperandFlags flags);
		AssemblerOperandFlags Flags = static_cast<AssemblerOperandFlags>(0);
		/// <summary>
		/// Apply mask Register K1.
		/// </summary>
		constexpr AssemblerRegisterZMM k1() const;
		/// <summary>
		/// Apply mask Register K2.
		/// </summary>
		constexpr AssemblerRegisterZMM k2() const;
		/// <summary>
		/// Apply mask Register K3.
		/// </summary>
		constexpr AssemblerRegisterZMM k3() const;
		/// <summary>
		/// Apply mask Register K4.
		/// </summary>
		constexpr AssemblerRegisterZMM k4() const;
		/// <summary>
		/// Apply mask Register K5.
		/// </summary>
		constexpr AssemblerRegisterZMM k5() const;
		/// <summary>
		/// Apply mask Register K6.
		/// </summary>
		constexpr AssemblerRegisterZMM k6() const;
		/// <summary>
		/// Apply mask Register K7.
		/// </summary>
		constexpr AssemblerRegisterZMM k7() const;
		/// <summary>
		/// Apply mask Zeroing.
		/// </summary>
		constexpr AssemblerRegisterZMM z() const;
		/// <summary>
		/// Suppress all exceptions
		/// </summary>
		constexpr AssemblerRegisterZMM sae() const;
		/// <summary>
		/// Round to nearest (even)
		/// </summary>
		constexpr AssemblerRegisterZMM rn_sae() const;
		/// <summary>
		/// Round down (toward -inf)
		/// </summary>
		constexpr AssemblerRegisterZMM rd_sae() const;
		/// <summary>
		/// Round up (toward +inf)
		/// </summary>
		constexpr AssemblerRegisterZMM ru_sae() const;
		/// <summary>
		/// Round toward zero (truncate)
		/// </summary>
		constexpr AssemblerRegisterZMM rz_sae() const;
		/// <summary>
		/// Converts a <see cref="AssemblerRegisterZMM"/> to a <see cref="Register"/>.
		/// </summary>
		/// <param name="reg">AssemblerRegisterZMM</param>
		/// <returns></returns>
		constexpr operator Register() const;
		/// <summary>
		/// Adds a register (base) with a displacement and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="displacement">The displacement</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator + (std::int64_t displacement) const;
		/// <summary>
		/// Subtracts a register (base) with a displacement and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="displacement">The displacement</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator - (std::int64_t displacement) const;
		/// <summary>
		/// Multiplies an index register by a scale and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="scale">The scale</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator *(std::int32_t scale) const;
		/// <inheritdoc />
		inline std::int32_t GetHashCode() const;
		/// <summary>
		/// Equality operator for <see cref="AssemblerRegisterZMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		constexpr bool operator == (AssemblerRegisterZMM right) const;
		/// <summary>
		/// Inequality operator for <see cref="AssemblerRegisterZMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		constexpr bool operator != (AssemblerRegisterZMM right) const;

		constexpr bool operator == (Register right) const;

		inline std::string ToString() const;

		constexpr AssemblerRegisterZMM() = default;
	};

	constexpr AssemblerRegisterZMM::AssemblerRegisterZMM(Register value)
	{
		if (!Iced::Intel::RegisterExtensions::IsZMM(value))
		{
			throw ArgumentOutOfRangeException(std::format("Invalid register {0:s}. Must be a ZMM register", nameof(value)));
		}
		Value = value;
		Flags = AssemblerOperandFlags::None;
	}

	constexpr AssemblerRegisterZMM::AssemblerRegisterZMM(Register value, AssemblerOperandFlags flags)
	{
		Value = value;
		Flags = flags;
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k1() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k2() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k3() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k4() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k5() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k6() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::k7() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::z() const
	{
		return AssemblerRegisterZMM(Value, Flags | AssemblerOperandFlags::Zeroing);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::sae() const
	{
		return AssemblerRegisterZMM(Value, Flags | AssemblerOperandFlags::SuppressAllExceptions);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::rn_sae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundToNearest);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::rd_sae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundDown);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::ru_sae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundUp);
	}

	constexpr AssemblerRegisterZMM AssemblerRegisterZMM::rz_sae() const
	{
		return AssemblerRegisterZMM(Value, (Flags & ~AssemblerOperandFlags::RoundControlMask) | AssemblerOperandFlags::RoundTowardZero);
	}

	constexpr AssemblerRegisterZMM::operator Register() const
	{
		return this->Value;
	}

	constexpr AssemblerMemoryOperand AssemblerRegisterZMM::operator + (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegisterZMM::operator - (std::int64_t displacement) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, *this, Register::None, 1, -displacement, AssemblerOperandFlags::None);
	}

	constexpr AssemblerMemoryOperand AssemblerRegisterZMM::operator *(std::int32_t scale) const
	{
		return AssemblerMemoryOperand(MemoryOperandSize::None, Register::None, Register::None, *this, scale, 0, AssemblerOperandFlags::None);
	}

	inline std::int32_t AssemblerRegisterZMM::GetHashCode() const
	{
		return (static_cast<std::int32_t>(Value) * 397) ^ static_cast<std::int32_t>(Flags);
	}

	constexpr bool AssemblerRegisterZMM::operator == (AssemblerRegisterZMM right) const
	{
		return Value == right.Value;
	}

	constexpr bool AssemblerRegisterZMM::operator != (AssemblerRegisterZMM right) const
	{
		return Value != right.Value;
	}

	constexpr bool AssemblerRegisterZMM::operator == (Register right) const
	{
		return Value == right;
	}

	inline std::string AssemblerRegisterZMM::ToString() const
	{
		return to_string(Value);
	}
}