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

#include "../Register.g.h"
#include "AssemblerOperandFlags.h"
#include "AssemblerMemoryOperand.h"
#include <any>
#include <format>

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
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [DebuggerDisplay("{" + nameof(Value) + "}")][EditorBrowsable(EditorBrowsableState.Never)] public partial struct AssemblerRegisterYMM: IEquatable<AssemblerRegisterYMM>
	class AssemblerRegisterYMM : public IEquatable<AssemblerRegisterYMM>
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A Register</param>
	public:
		AssemblerRegisterYMM(Register value);
		/// <summary>
		/// The register value.
		/// </summary>
		Register Value = static_cast<Register>(0);
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A register</param>
		/// <param name="flags">The mask</param>
		AssemblerRegisterYMM(Register value, AssemblerOperandFlags flags);
		AssemblerOperandFlags Flags = static_cast<AssemblerOperandFlags>(0);
		/// <summary>
		/// Apply mask Register K1.
		/// </summary>
		AssemblerRegisterYMM GetK1() const;
		/// <summary>
		/// Apply mask Register K2.
		/// </summary>
		AssemblerRegisterYMM GetK2() const;
		/// <summary>
		/// Apply mask Register K3.
		/// </summary>
		AssemblerRegisterYMM GetK3() const;
		/// <summary>
		/// Apply mask Register K4.
		/// </summary>
		AssemblerRegisterYMM GetK4() const;
		/// <summary>
		/// Apply mask Register K5.
		/// </summary>
		AssemblerRegisterYMM GetK5() const;
		/// <summary>
		/// Apply mask Register K6.
		/// </summary>
		AssemblerRegisterYMM GetK6() const;
		/// <summary>
		/// Apply mask Register K7.
		/// </summary>
		AssemblerRegisterYMM GetK7() const;
		/// <summary>
		/// Apply mask Zeroing.
		/// </summary>
		AssemblerRegisterYMM GetZ() const;
		/// <summary>
		/// Suppress all exceptions
		/// </summary>
		AssemblerRegisterYMM GetSae() const;
		/// <summary>
		/// Round to nearest (even)
		/// </summary>
		AssemblerRegisterYMM GetRnSae() const;
		/// <summary>
		/// Round down (toward -inf)
		/// </summary>
		AssemblerRegisterYMM GetRdSae() const;
		/// <summary>
		/// Round up (toward +inf)
		/// </summary>
		AssemblerRegisterYMM GetRuSae() const;
		/// <summary>
		/// Round toward zero (truncate)
		/// </summary>
		AssemblerRegisterYMM GetRzSae() const;
		/// <summary>
		/// Converts a <see cref="AssemblerRegisterYMM"/> to a <see cref="Register"/>.
		/// </summary>
		/// <param name="reg">AssemblerRegisterYMM</param>
		/// <returns></returns>
		operator Register();
		/// <summary>
		/// Adds a register (base) with a displacement and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="displacement">The displacement</param>
		/// <returns></returns>
		AssemblerMemoryOperand operator + (std::int64_t displacement);
		/// <summary>
		/// Subtracts a register (base) with a displacement and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="displacement">The displacement</param>
		/// <returns></returns>
		AssemblerMemoryOperand operator - (std::int64_t displacement);
		/// <summary>
		/// Multiplies an index register by a scale and return a memory operand.
		/// </summary>
		/// <param name="left">The base register</param>
		/// <param name="scale">The scale</param>
		/// <returns></returns>
		AssemblerMemoryOperand operator *(std::int32_t scale);
		/// <inheritdoc />
		bool Equals(AssemblerRegisterYMM other) override;
		/// <inheritdoc />
		std::int32_t GetHashCode();
		/// <inheritdoc />
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public override bool Equals(Object? obj)
		bool Equals(std::any obj);
		/// <summary>
		/// Equality operator for <see cref="AssemblerRegisterYMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator == (AssemblerRegisterYMM right);
		/// <summary>
		/// Inequality operator for <see cref="AssemblerRegisterYMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator != (AssemblerRegisterYMM right);

		AssemblerRegisterYMM() = default;
	};
}