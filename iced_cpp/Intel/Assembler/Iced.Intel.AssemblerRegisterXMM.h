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
   //ORIGINAL LINE: [DebuggerDisplay("{" + nameof(Value) + "}")][EditorBrowsable(EditorBrowsableState.Never)] public partial struct AssemblerRegisterXMM: IEquatable<AssemblerRegisterXMM>
	class AssemblerRegisterXMM : public IEquatable<AssemblerRegisterXMM>
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A Register</param>
	public:
		AssemblerRegisterXMM(Register value);
		/// <summary>
		/// The register value.
		/// </summary>
		Register Value = static_cast<Register>(0);
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A register</param>
		/// <param name="flags">The mask</param>
		AssemblerRegisterXMM(Register value, AssemblerOperandFlags flags);
		AssemblerOperandFlags Flags = static_cast<AssemblerOperandFlags>(0);
		/// <summary>
		/// Apply mask Register K1.
		/// </summary>
		AssemblerRegisterXMM k1() const;
		/// <summary>
		/// Apply mask Register K2.
		/// </summary>
		AssemblerRegisterXMM k2() const;
		/// <summary>
		/// Apply mask Register K3.
		/// </summary>
		AssemblerRegisterXMM k3() const;
		/// <summary>
		/// Apply mask Register K4.
		/// </summary>
		AssemblerRegisterXMM k4() const;
		/// <summary>
		/// Apply mask Register K5.
		/// </summary>
		AssemblerRegisterXMM k5() const;
		/// <summary>
		/// Apply mask Register K6.
		/// </summary>
		AssemblerRegisterXMM k6() const;
		/// <summary>
		/// Apply mask Register K7.
		/// </summary>
		AssemblerRegisterXMM k7() const;
		/// <summary>
		/// Apply mask Zeroing.
		/// </summary>
		AssemblerRegisterXMM z() const;
		/// <summary>
		/// Suppress all exceptions
		/// </summary>
		AssemblerRegisterXMM sae() const;
		/// <summary>
		/// Round to nearest (even)
		/// </summary>
		AssemblerRegisterXMM rn_sae() const;
		/// <summary>
		/// Round down (toward -inf)
		/// </summary>
		AssemblerRegisterXMM rd_sae() const;
		/// <summary>
		/// Round up (toward +inf)
		/// </summary>
		AssemblerRegisterXMM ru_sae() const;
		/// <summary>
		/// Round toward zero (truncate)
		/// </summary>
		AssemblerRegisterXMM rz_sae() const;
		/// <summary>
		/// Converts a <see cref="AssemblerRegisterXMM"/> to a <see cref="Register"/>.
		/// </summary>
		/// <param name="reg">AssemblerRegisterXMM</param>
		/// <returns></returns>
		operator Register() const;
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
		bool Equals(AssemblerRegisterXMM other) override;
		/// <inheritdoc />
		std::int32_t GetHashCode();
		/// <inheritdoc />
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public override bool Equals(Object? obj)
		bool Equals(std::any obj);
		/// <summary>
		/// Equality operator for <see cref="AssemblerRegisterXMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator == (AssemblerRegisterXMM right);
		/// <summary>
		/// Inequality operator for <see cref="AssemblerRegisterXMM"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator != (AssemblerRegisterXMM right);

		inline bool operator == (Register right) { return (Register)(*this) == right; }
		inline std::string ToString() const { return to_string(Value); }

		AssemblerRegisterXMM() = default;
	};
}
