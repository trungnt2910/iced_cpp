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
#include "MemoryOperandSize.g.h"
#include "Iced.Intel.AssemblerRegister16.h"
#include "Iced.Intel.AssemblerRegister32.h"
#include "Iced.Intel.AssemblerRegister64.h"
#include "../MemoryOperand.h"
#include <any>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Defines an assembly memory operand used with <see cref="Assembler"/>.
	/// </summary>
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [DebuggerDisplay("{" + nameof(Base) + "} + {" + nameof(Index) + "} * {" + nameof(Scale) + "} + {" + nameof(Displacement) + "}")][EditorBrowsable(EditorBrowsableState.Never)] public struct AssemblerMemoryOperand : IEquatable<AssemblerMemoryOperand>
	class AssemblerMemoryOperand : public IEquatable<AssemblerMemoryOperand>
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="size">Size of the operand.</param>
		/// <param name="segment">Segment register.</param>
		/// <param name="base">Base register.</param>
		/// <param name="index">Index register.</param>
		/// <param name="scale">Scale of the index.</param>
		/// <param name="displacement">Displacement.</param>
		/// <param name="flags">Flags attached to this operand.</param>
	public:
		AssemblerMemoryOperand(MemoryOperandSize size, Register segment, Register base, Register index, std::int32_t scale, std::int64_t displacement, AssemblerOperandFlags flags);
		/// <summary>
		/// Gets the size of the operand.
		/// </summary>
		MemoryOperandSize Size = static_cast<MemoryOperandSize>(0);
		/// <summary>
		/// Gets the segment register.
		/// </summary>
		Register Segment = static_cast<Register>(0);
		/// <summary>
		/// Gets the register used as a base.
		/// </summary>
		Register Base = static_cast<Register>(0);
		/// <summary>
		/// Gets the register used as an index.
		/// </summary>
		Register Index = static_cast<Register>(0);
		/// <summary>
		/// Gets the scale applied to the index register.
		/// </summary>
		std::int32_t Scale = 0;
		/// <summary>
		/// Gets the displacement.
		/// </summary>
		std::int64_t Displacement = 0;
		/// <summary>
		/// Gets the mask associated with this operand.
		/// </summary>
		AssemblerOperandFlags Flags = static_cast<AssemblerOperandFlags>(0);
		/// <summary>
		/// Gets a boolean indicating if this memory operand is a broadcast.
		/// </summary>
		bool IsBroadcast() const;
		/// <summary>
		/// Gets a boolean indicating if this memory operand is a memory access using displacement only (no base and index registers are used).
		/// </summary>
		bool IsDisplacementOnly() const;
		/// <summary>
		/// Apply mask Register K1.
		/// </summary>
		AssemblerMemoryOperand GetK1() const;
		/// <summary>
		/// Apply mask Register K2.
		/// </summary>
		AssemblerMemoryOperand GetK2() const;
		/// <summary>
		/// Apply mask Register K3.
		/// </summary>
		AssemblerMemoryOperand GetK3() const;
		/// <summary>
		/// Apply mask Register K4.
		/// </summary>
		AssemblerMemoryOperand GetK4() const;
		/// <summary>
		/// Apply mask Register K5.
		/// </summary>
		AssemblerMemoryOperand GetK5() const;
		/// <summary>
		/// Apply mask Register K6.
		/// </summary>
		AssemblerMemoryOperand GetK6() const;
		/// <summary>
		/// Apply mask Register K7.
		/// </summary>
		AssemblerMemoryOperand GetK7() const;
		/// <summary>
		/// Adds a 16-bit memory operand with an new base or index.
		/// </summary>
		/// <param name="left">The base or index.</param>
		/// <param name="right">The memory operand.</param>
		/// <returns></returns>
		friend   static AssemblerMemoryOperand operator + (AssemblerRegister16 left, AssemblerMemoryOperand right);
		/// <summary>
		/// Adds a 32-bit memory operand with an new base or index.
		/// </summary>
		/// <param name="left">The base or index.</param>
		/// <param name="right">The memory operand.</param>
		/// <returns></returns>
		friend   static AssemblerMemoryOperand operator + (AssemblerRegister32 left, AssemblerMemoryOperand right);
		/// <summary>
		/// Adds a 64-bit memory operand with an new base or index.
		/// </summary>
		/// <param name="left">The base or index.</param>
		/// <param name="right">The memory operand.</param>
		/// <returns></returns>
		friend   static AssemblerMemoryOperand operator + (AssemblerRegister64 left, AssemblerMemoryOperand right);
		/// <summary>
		/// Adds a displacement to a memory operand.
		/// </summary>
		/// <param name="left">The memory operand.</param>
		/// <param name="displacement">displacement.</param>
		/// <returns></returns>
		AssemblerMemoryOperand operator + (std::int64_t displacement);
		/// <summary>
		/// Subtracts a displacement to a memory operand.
		/// </summary>
		/// <param name="left">The memory operand.</param>
		/// <param name="displacement">displacement.</param>
		/// <returns></returns>
		AssemblerMemoryOperand operator - (std::int64_t displacement);
		/// <summary>
		/// Gets a memory operand for the specified bitness.
		/// </summary>
		/// <param name="bitness">The bitness</param>
		MemoryOperand ToMemoryOperand(std::int32_t bitness);
		/// <inheritdoc />
		bool Equals(AssemblerMemoryOperand other) override;
		/// <inheritdoc />
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public override bool Equals(Object? obj)
		bool Equals(std::any obj);
		/// <inheritdoc />
		std::int32_t GetHashCode();
		/// <summary>
		/// Equality operator for <see cref="AssemblerMemoryOperand"/>.
		/// </summary>
		/// <param name="left">Left operand</param>
		/// <param name="right">Right operand</param>
		/// <returns><c>true</c> if equal; otherwise <c>false</c></returns>
		bool operator == (AssemblerMemoryOperand right);
		/// <summary>
		/// Inequality operator for <see cref="AssemblerMemoryOperand"/>.
		/// </summary>
		/// <param name="left">Left operand</param>
		/// <param name="right">Right operand</param>
		/// <returns><c>true</c> if not equal; otherwise <c>false</c></returns>
		bool operator != (AssemblerMemoryOperand right);

		AssemblerMemoryOperand() = default;
	};
}
