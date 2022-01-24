// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#if defined(ENCODER) && defined(BLOCK_ENCODER) && defined(CODE_ASSEMBLER)

#include <string>

#include "../GetHashCode.h"
#include "../Register.g.h"
#include "AssemblerOperandFlags.h"
#include "MemoryOperandSize.g.h"
#include "../MemoryOperand.h"

namespace Iced::Intel
{
	/// <summary>
	/// Defines an assembly memory operand used with <see cref="Assembler"/>.
	/// </summary>
	struct AssemblerMemoryOperand
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
		constexpr AssemblerMemoryOperand(MemoryOperandSize size, Register segment, Register base, Register index, std::int32_t scale, std::int64_t displacement, AssemblerOperandFlags flags);
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
		constexpr bool IsBroadcast() const;
		/// <summary>
		/// Gets a boolean indicating if this memory operand is a memory access using displacement only (no base and index registers are used).
		/// </summary>
		constexpr bool IsDisplacementOnly() const;
		/// <summary>
		/// Apply mask Register K1.
		/// </summary>
		constexpr AssemblerMemoryOperand k1() const;
		/// <summary>
		/// Apply mask Register K2.
		/// </summary>
		constexpr AssemblerMemoryOperand k2() const;
		/// <summary>
		/// Apply mask Register K3.
		/// </summary>
		constexpr AssemblerMemoryOperand k3() const;
		/// <summary>
		/// Apply mask Register K4.
		/// </summary>
		constexpr AssemblerMemoryOperand k4() const;
		/// <summary>
		/// Apply mask Register K5.
		/// </summary>
		constexpr AssemblerMemoryOperand k5() const;
		/// <summary>
		/// Apply mask Register K6.
		/// </summary>
		constexpr AssemblerMemoryOperand k6() const;
		/// <summary>
		/// Apply mask Register K7.
		/// </summary>
		constexpr AssemblerMemoryOperand k7() const;
		/// <summary>
		/// Adds a displacement to a memory operand.
		/// </summary>
		/// <param name="left">The memory operand.</param>
		/// <param name="displacement">displacement.</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator + (std::int64_t displacement) const;
		/// <summary>
		/// Subtracts a displacement to a memory operand.
		/// </summary>
		/// <param name="left">The memory operand.</param>
		/// <param name="displacement">displacement.</param>
		/// <returns></returns>
		constexpr AssemblerMemoryOperand operator - (std::int64_t displacement) const;
		/// <summary>
		/// Gets a memory operand for the specified bitness.
		/// </summary>
		/// <param name="bitness">The bitness</param>
		constexpr MemoryOperand ToMemoryOperand(std::int32_t bitness) const;
		/// <inheritdoc />
		constexpr std::int32_t GetHashCode() const;
		/// <summary>
		/// Equality operator for <see cref="AssemblerMemoryOperand"/>.
		/// </summary>
		/// <param name="left">Left operand</param>
		/// <param name="right">Right operand</param>
		/// <returns><c>true</c> if equal; otherwise <c>false</c></returns>
		constexpr bool operator == (AssemblerMemoryOperand right) const;
		/// <summary>
		/// Inequality operator for <see cref="AssemblerMemoryOperand"/>.
		/// </summary>
		/// <param name="left">Left operand</param>
		/// <param name="right">Right operand</param>
		/// <returns><c>true</c> if not equal; otherwise <c>false</c></returns>
		constexpr bool operator != (AssemblerMemoryOperand right) const;

		inline std::string ToString() const;

		constexpr AssemblerMemoryOperand() = default;
	};

	constexpr AssemblerMemoryOperand::AssemblerMemoryOperand(MemoryOperandSize size, Register segment, Register base, Register index, std::int32_t scale, std::int64_t displacement, AssemblerOperandFlags flags)
	{
		Size = size;
		Segment = segment;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		Flags = flags;
	}

	constexpr bool AssemblerMemoryOperand::IsBroadcast() const
	{
		return (Flags & AssemblerOperandFlags::Broadcast) != 0;
	}

	constexpr bool AssemblerMemoryOperand::IsDisplacementOnly() const
	{
		return Base == Register::None && Index == Register::None;
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k1() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k2() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k3() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k4() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k5() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k6() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::k7() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}
	
	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::operator + (std::int64_t displacement) const 
	{
		return AssemblerMemoryOperand(this->Size, Register::None, this->Base, this->Index, this->Scale, this->Displacement + displacement, this->Flags);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperand::operator - (std::int64_t displacement) const 
	{
		return AssemblerMemoryOperand(this->Size, Register::None, this->Base, this->Index, this->Scale, this->Displacement - displacement, this->Flags);
	}

	constexpr MemoryOperand AssemblerMemoryOperand::ToMemoryOperand(std::int32_t bitness) const 
	{
		std::int32_t dispSize = 1;
		if (IsDisplacementOnly()) 
		{
			dispSize = bitness / 8;
		}
		else if (Displacement == 0) 
		{
			dispSize = 0;
		}
		return MemoryOperand(Base, Index, Scale, Displacement, dispSize, (Flags & AssemblerOperandFlags::Broadcast) != 0, Segment);
	}

	constexpr std::int32_t AssemblerMemoryOperand::GetHashCode() const 
	{
		//	 unchecked
		auto hashCode = static_cast<std::int32_t>(Size);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Segment);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Base);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Index);
		hashCode = (hashCode * 397) ^ Scale;
		hashCode = (hashCode * 397) ^ Iced::Intel::GetHashCode(Displacement);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Flags);
		return hashCode;
		//C# TO C++ CONVERTER TODO TASK: End of the original C# 'unchecked' block.
	}

	constexpr bool AssemblerMemoryOperand::operator == (AssemblerMemoryOperand right) const 
	{
		return Size == right.Size && Segment == right.Segment && Base == right.Base && Index == right.Index && Scale == right.Scale && Displacement == right.Displacement && Flags == right.Flags;
	}

	constexpr bool AssemblerMemoryOperand::operator != (AssemblerMemoryOperand right) const 
	{
		return !((*this) == right);
	}

	inline std::string AssemblerMemoryOperand::ToString() const
	{
		return nameof(AssemblerMemoryOperand)"(" +
#define LIST_PARAM(s) std::string(nameof((s))"=" + ::Iced::Intel::ToString((s))) 
			LIST_PARAM(Size) + "," +
			LIST_PARAM(Segment) + "," +
			LIST_PARAM(Base) + "," +
			LIST_PARAM(Index) + "," +
			LIST_PARAM(Scale) + "," +
			LIST_PARAM(Displacement) + "," +
			LIST_PARAM(Flags) + ")";
#undef LIST_PARAM
	}
}

#endif