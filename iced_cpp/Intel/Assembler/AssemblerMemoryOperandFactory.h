// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "MemoryOperandSize.g.h"
#include "../Register.g.h"
#include "AssemblerOperandFlags.h"
#include "AssemblerMemoryOperand.h"
#include "Label.h"
#include "AssemblerRegister.g.h"

namespace Iced::Intel
{
	/// <summary>
	/// Memory operand factory.
	/// </summary>
	class AssemblerMemoryOperandFactory
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="size">Size of this memory operand.</param>
	public:
		constexpr AssemblerMemoryOperandFactory(MemoryOperandSize size);
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="size">Size of this memory operand.</param>
		/// <param name="segment">Segment register</param>
		/// <param name="flags">Flags</param>
		constexpr AssemblerMemoryOperandFactory(MemoryOperandSize size, Register segment, AssemblerOperandFlags flags);
		/// <summary>
		/// Size of this memory operand.
		/// </summary>
		MemoryOperandSize Size = static_cast<MemoryOperandSize>(0);
		/// <summary>
		/// Segment register.
		/// </summary>
		Register Segment = static_cast<Register>(0);
		/// <summary>
		/// Gets the mask associated with this operand.
		/// </summary>
		AssemblerOperandFlags Flags = static_cast<AssemblerOperandFlags>(0);
		/// <summary>
		/// Use the ES register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory es() const;
		/// <summary>
		/// Use the CS register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory cs() const;
		/// <summary>
		/// Use the CS register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory ss() const;
		/// <summary>
		/// Use the DS register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory ds() const;
		/// <summary>
		/// Use the FS register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory fs() const;
		/// <summary>
		/// Use the GS register with this memory operand.
		/// </summary>
		constexpr AssemblerMemoryOperandFactory gs() const;
		/// <summary>
		/// Specify the content of the memory operand (Base + Index * Scale + Displacement).
		/// </summary>
		/// <param name="operand">Size of this memory operand.</param>
		constexpr AssemblerMemoryOperand operator [](AssemblerMemoryOperand operand) const;
		/// <summary>
		/// Specify a long offset displacement.
		/// </summary>
		/// <param name="offset">Offset of this memory operand.</param>
		constexpr AssemblerMemoryOperand operator [](std::int64_t offset) const;
		/// <summary>
		/// Specify a ulong offset displacement.
		/// </summary>
		/// <param name="offset">Offset of this memory operand.</param>
		constexpr AssemblerMemoryOperand operator [](std::uint64_t offset) const;
		/// <summary>
		/// Specify a memory operand with a label.
		/// </summary>
		constexpr AssemblerMemoryOperand operator [](const Label& label) const;

#include "AssemblerMemoryOperandFactory.RegisterFunctions.g.h"

		constexpr AssemblerMemoryOperandFactory() = default;
	};

	constexpr AssemblerMemoryOperandFactory::AssemblerMemoryOperandFactory(MemoryOperandSize size)
	{
		Segment = Register::None;
		Size = size;
		Flags = AssemblerOperandFlags::None;
	}

	constexpr AssemblerMemoryOperandFactory::AssemblerMemoryOperandFactory(MemoryOperandSize size, Register segment, AssemblerOperandFlags flags)
	{
		Size = size;
		Segment = segment;
		Flags = flags;
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::es() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::ES, Flags);
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::cs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::CS, Flags);
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::ss() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::SS, Flags);
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::ds() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::DS, Flags);
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::fs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::FS, Flags);
	}

	constexpr AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::gs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::GS, Flags);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](AssemblerMemoryOperand operand) const
	{
		return AssemblerMemoryOperand(Size, Segment, operand.Base, operand.Index, operand.Scale, operand.Displacement, Flags);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](std::int64_t offset) const
	{
		return AssemblerMemoryOperand(Size, Segment, Register::None, Register::None, 1, offset, Flags);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](std::uint64_t offset) const
	{
		return AssemblerMemoryOperand(Size, Segment, Register::None, Register::None, 1, static_cast<std::int64_t>(offset), Flags);
	}

	constexpr AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](const Label& label) const
	{
		return AssemblerMemoryOperand(Size, Segment, Register::RIP, Register::None, 1, static_cast<std::int64_t>(label.GetId()), Flags);
	}
}
