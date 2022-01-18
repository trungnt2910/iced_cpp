#pragma once

#include "Register.g.h"
#include <vector>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class RegisterInfo;
	/// <summary>
	/// <see cref="Register"/> extension methods
	/// </summary>
	namespace RegisterExtensions
	{
		/// <summary>
		/// Gets register info
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static RegisterInfo GetInfo(Register register_);
		/// <summary>
		/// Gets the base register, eg. <c>AL</c>, <c>AX</c>, <c>EAX</c>, <c>RAX</c>, <c>MM0</c>, <c>XMM0</c>, <c>YMM0</c>, <c>ZMM0</c>, <c>ES</c>
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static Register GetBaseRegister(Register register_);
		/// <summary>
		/// The register number (index) relative to <see cref="GetBaseRegister(Register)"/>, eg. 0-15, or 0-31, or if 8-bit GPR, 0-19
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static std::int32_t GetNumber(Register register_);
		/// <summary>
		/// Gets the full register that this one is a part of, eg. CL/CH/CX/ECX/RCX -> RCX, XMM11/YMM11/ZMM11 -> ZMM11
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static Register GetFullRegister(Register register_);
		/// <summary>
		/// Gets the full register that this one is a part of, except if it's a GPR in which case the 32-bit register is returned,
		/// eg. CL/CH/CX/ECX/RCX -> ECX, XMM11/YMM11/ZMM11 -> ZMM11
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static Register GetFullRegister32(Register register_);
		/// <summary>
		/// Gets the size of the register in bytes
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static std::int32_t GetSize(Register register_);


		/// <summary>
		/// Checks if it's a segment register (<c>ES</c>, <c>CS</c>, <c>SS</c>, <c>DS</c>, <c>FS</c>, <c>GS</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsSegmentRegister(Register register_);
		/// <summary>
		/// Checks if it's a general purpose register (<c>AL</c>-<c>R15L</c>, <c>AX</c>-<c>R15W</c>, <c>EAX</c>-<c>R15D</c>, <c>RAX</c>-<c>R15</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsGPR(Register register_);
		/// <summary>
		/// Checks if it's an 8-bit general purpose register (<c>AL</c>-<c>R15L</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsGPR8(Register register_);
		/// <summary>
		/// Checks if it's a 16-bit general purpose register (<c>AX</c>-<c>R15W</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsGPR16(Register register_);
		/// <summary>
		/// Checks if it's a 32-bit general purpose register (<c>EAX</c>-<c>R15D</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsGPR32(Register register_);
		/// <summary>
		/// Checks if it's a 64-bit general purpose register (<c>RAX</c>-<c>R15</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsGPR64(Register register_);
		/// <summary>
		/// Checks if it's a 128-bit vector register (<c>XMM0</c>-<c>XMM31</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsXMM(Register register_);
		/// <summary>
		/// Checks if it's a 256-bit vector register (<c>YMM0</c>-<c>YMM31</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsYMM(Register register_);
		/// <summary>
		/// Checks if it's a 512-bit vector register (<c>ZMM0</c>-<c>ZMM31</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsZMM(Register register_);
		/// <summary>
		/// Checks if it's <c>EIP</c>/<c>RIP</c>
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsIP(Register register_);
		/// <summary>
		/// Checks if it's an opmask register (<c>K0</c>-<c>K7</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsK(Register register_);
		/// <summary>
		/// Checks if it's a control register (<c>CR0</c>-<c>CR15</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsCR(Register register_);
		/// <summary>
		/// Checks if it's a debug register (<c>DR0</c>-<c>DR15</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsDR(Register register_);
		/// <summary>
		/// Checks if it's a test register (<c>TR0</c>-<c>TR7</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsTR(Register register_);
		/// <summary>
		/// Checks if it's an FPU stack register (<c>ST0</c>-<c>ST7</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsST(Register register_);
		/// <summary>
		/// Checks if it's a bound register (<c>BND0</c>-<c>BND3</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsBND(Register register_);
		/// <summary>
		/// Checks if it's an MMX register (<c>MM0</c>-<c>MM7</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsMM(Register register_);
		/// <summary>
		/// Checks if it's a tile register (<c>TMM0</c>-<c>TMM7</c>)
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsTMM(Register register_);
		/// <summary>
		/// Checks if it's an <c>XMM</c>, <c>YMM</c> or <c>ZMM</c> register
		/// </summary>
		/// <param name="register">Register</param>
		/// <returns></returns>
		constexpr static bool IsVectorRegister(Register register_);
	};
}