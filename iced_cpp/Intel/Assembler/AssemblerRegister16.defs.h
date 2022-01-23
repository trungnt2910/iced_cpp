#pragma once

#include <cstdint>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	enum class Register;

	class AssemblerMemoryOperand;

	/// <summary>
	/// An assembler register used with <see cref="Assembler"/>.
	/// </summary>
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [DebuggerDisplay("{" + nameof(Value) + "}")][EditorBrowsable(EditorBrowsableState.Never)] public partial struct AssemblerRegister16: IEquatable<AssemblerRegister16>
	class AssemblerRegister16
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A Register</param>
	public:
		constexpr AssemblerRegister16(Register value);
		/// <summary>
		/// The register value.
		/// </summary>
		Register Value = static_cast<Register>(0);
		/// <summary>
		/// Converts a <see cref="AssemblerRegister16"/> to a <see cref="Register"/>.
		/// </summary>
		/// <param name="reg">AssemblerRegister16</param>
		/// <returns></returns>
		constexpr operator Register() const;
		/// <summary>
		/// Adds a register (base) to another register (index) and return a memory operand.
		/// </summary>
		/// <param name="left">The base register.</param>
		/// <param name="right">The index register</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator + (AssemblerRegister16 right) const;
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
		constexpr std::int32_t GetHashCode() const;
		/// <summary>
		/// Equality operator for <see cref="AssemblerRegister16"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		constexpr bool operator == (AssemblerRegister16 right) const;
		/// <summary>
		/// Inequality operator for <see cref="AssemblerRegister16"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		constexpr bool operator != (AssemblerRegister16 right) const;

		constexpr inline bool operator == (Register right) const;
		inline std::string ToString() const;
		
		constexpr AssemblerRegister16() = default;
	};
}
