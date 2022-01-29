// C# helper headers




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
#include <stdexcept>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Gets a register value. If <paramref name="register"/> is a segment register, this method should return the segment's base address,
	/// not the segment's register value.
	/// </summary>
	/// <param name="register">Register (GPR8, GPR16, GPR32, GPR64, XMM, YMM, ZMM, seg)</param>
	/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
	/// <param name="elementSize">Only used if it's a vsib memory operand. Size in bytes of elements in vector index register (4 or 8).</param>
	/// <returns></returns>
	using VAGetRegisterValue = std::function<std::uint64_t(Register register_, std::int32_t elementIndex, std::int32_t elementSize)>;
	/// <summary>
	/// Called when calculating the virtual address of a memory operand
	/// </summary>
	class IVARegisterValueProvider
	{
		/// <summary>
		/// Gets a register value. If <paramref name="register"/> is a segment register, this method should return the segment's base address,
		/// not the segment's register value.
		/// </summary>
		/// <param name="register">Register (GPR8, GPR16, GPR32, GPR64, XMM, YMM, ZMM, seg)</param>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="elementSize">Only used if it's a vsib memory operand. Size in bytes of elements in vector index register (4 or 8).</param>
		/// <returns></returns>
	public:
		virtual std::uint64_t GetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize) = 0;
	};
	/// <summary>
	/// Gets a register value. If <paramref name="register"/> is a segment register, this method should return the segment's base address,
	/// not the segment's register value.
	/// </summary>
	/// <param name="register">Register (GPR8, GPR16, GPR32, GPR64, XMM, YMM, ZMM, seg)</param>
	/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
	/// <param name="elementSize">Only used if it's a vsib memory operand. Size in bytes of elements in vector index register (4 or 8).</param>
	/// <param name="value">Updated with the register value if successful</param>
	/// <returns></returns>
	using VATryGetRegisterValue = std::function<bool(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value)>;
	/// <summary>
	/// Called when calculating the virtual address of a memory operand
	/// </summary>
	class IVATryGetRegisterValueProvider
	{
		/// <summary>
		/// Gets a register value. If <paramref name="register"/> is a segment register, this method should return the segment's base address,
		/// not the segment's register value.
		/// </summary>
		/// <param name="register">Register (GPR8, GPR16, GPR32, GPR64, XMM, YMM, ZMM, seg)</param>
		/// <param name="elementIndex">Only used if it's a vsib memory operand. This is the element index of the vector index register.</param>
		/// <param name="elementSize">Only used if it's a vsib memory operand. Size in bytes of elements in vector index register (4 or 8).</param>
		/// <param name="value">Updated with the register value if successful</param>
		/// <returns></returns>
	public:
		virtual bool TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value) = 0;
	};
	class VARegisterValueProviderDelegateImpl final : public IVATryGetRegisterValueProvider
	{
		/* readonly */
	private:
		VAGetRegisterValue getRegisterValue;
	public:
		VARegisterValueProviderDelegateImpl(VAGetRegisterValue getRegisterValue);
		bool TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value) override;
	};
	class VARegisterValueProviderAdapter final : public IVATryGetRegisterValueProvider
	{
		/* readonly */
	private:
		IVARegisterValueProvider* provider;
	public:
		VARegisterValueProviderAdapter(IVARegisterValueProvider* provider);
		bool TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value) override;
	};
	class VATryGetRegisterValueDelegateImpl final : public IVATryGetRegisterValueProvider
	{
		/* readonly */
	private:
		VATryGetRegisterValue getRegisterValue;
	public:
		VATryGetRegisterValueDelegateImpl(VATryGetRegisterValue getRegisterValue);
		bool TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value) override;
	};
}
