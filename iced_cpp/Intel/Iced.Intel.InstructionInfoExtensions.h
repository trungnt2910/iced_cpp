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

#include "Code.g.h"
#include "EncodingKind.g.h"
#include "CpuidFeature.g.h"
#include "FlowControl.g.h"
#include "ConditionCode.g.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::InstructionInfoInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Extension methods
	/// </summary>
	class InstructionInfoExtensions final
	{
		/// <summary>
		/// Gets the encoding, eg. Legacy, 3DNow!, VEX, EVEX, XOP
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static EncodingKind Encoding(this Code code)
		static EncodingKind Encoding(Code code);
		/// <summary>
		/// Gets the CPU or CPUID feature flags
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static CpuidFeature[] CpuidFeatures(this Code code)
		static std::vector<CpuidFeature> CpuidFeatures(Code code);
		/// <summary>
		/// Gets control flow info
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static FlowControl FlowControl(this Code code)
		static Iced::Intel::FlowControl FlowControl(Code code);
		/// <summary>
		/// Checks if it's a privileged instruction (all CPL=0 instructions (except <c>VMCALL</c>) and IOPL instructions <c>IN</c>, <c>INS</c>, <c>OUT</c>, <c>OUTS</c>, <c>CLI</c>, <c>STI</c>)
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsPrivileged(this Code code)
		static bool IsPrivileged(Code code);
		/// <summary>
		/// Checks if this is an instruction that implicitly uses the stack pointer (<c>SP</c>/<c>ESP</c>/<c>RSP</c>), eg. <c>CALL</c>, <c>PUSH</c>, <c>POP</c>, <c>RET</c>, etc.
		/// See also <see cref="Instruction.StackPointerIncrement"/>
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsStackInstruction(this Code code)
		static bool IsStackInstruction(Code code);
		/// <summary>
		/// Checks if it's an instruction that saves or restores too many registers (eg. <c>FXRSTOR</c>, <c>XSAVE</c>, etc).
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsSaveRestoreInstruction(this Code code)
		static bool IsSaveRestoreInstruction(Code code);
		/// <summary>
		/// Checks if it's a <c>Jcc NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJccNear(this Code code)
		static bool IsJccNear(Code code);
		/// <summary>
		/// Checks if it's a <c>Jcc SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJccShort(this Code code)
		static bool IsJccShort(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpShort(this Code code)
		static bool IsJmpShort(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpNear(this Code code)
		static bool IsJmpNear(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP SHORT</c> or a <c>JMP NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpShortOrNear(this Code code)
		static bool IsJmpShortOrNear(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP FAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpFar(this Code code)
		static bool IsJmpFar(Code code);
		/// <summary>
		/// Checks if it's a <c>CALL NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsCallNear(this Code code)
		static bool IsCallNear(Code code);
		/// <summary>
		/// Checks if it's a <c>CALL FAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsCallFar(this Code code)
		static bool IsCallFar(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP NEAR reg/[mem]</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpNearIndirect(this Code code)
		static bool IsJmpNearIndirect(Code code);
		/// <summary>
		/// Checks if it's a <c>JMP FAR [mem]</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJmpFarIndirect(this Code code)
		static bool IsJmpFarIndirect(Code code);
		/// <summary>
		/// Checks if it's a <c>CALL NEAR reg/[mem]</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsCallNearIndirect(this Code code)
		static bool IsCallNearIndirect(Code code);
		/// <summary>
		/// Checks if it's a <c>CALL FAR [mem]</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsCallFarIndirect(this Code code)
		static bool IsCallFarIndirect(Code code);
		/// <summary>
		/// Checks if it's a <c>JKccD SHORT</c> or <c>JKccD NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJkccShortOrNear(this Code code)
		static bool IsJkccShortOrNear(Code code);
		/// <summary>
		/// Checks if it's a <c>JKccD NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJkccNear(this Code code)
		static bool IsJkccNear(Code code);
		/// <summary>
		/// Checks if it's a <c>JKccD SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJkccShort(this Code code)
		static bool IsJkccShort(Code code);
		/// <summary>
		/// Gets the condition code if it's <c>Jcc</c>, <c>SETcc</c>, <c>CMOVcc</c>, <c>LOOPcc</c> else
		/// <see cref="ConditionCode.None"/> is returned
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
		static Iced::Intel::ConditionCode ConditionCode(Code code);
		/// <summary>
		/// Checks if it's a string instruction such as <c>MOVS</c>, <c>LODS</c>, <c>STOS</c>, etc.
		/// </summary>
		/// <returns></returns>
		static bool IsStringInstruction(Code code);


		/// <summary>
		/// Negates the condition code, eg. <c>JE</c> -> <c>JNE</c>. Can be used if it's <c>Jcc</c>, <c>SETcc</c>, <c>CMOVcc</c>, <c>LOOPcc</c>
		/// and returns the original value if it's none of those instructions.
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
		static Code NegateConditionCode(Code code);
		/// <summary>
		/// Converts <c>Jcc/JMP NEAR</c> to <c>Jcc/JMP SHORT</c>. Returns the input if it's not a <c>Jcc/JMP NEAR</c> instruction.
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
		static Code ToShortBranch(Code code);
		/// <summary>
		/// Converts <c>Jcc/JMP SHORT</c> to <c>Jcc/JMP NEAR</c>. Returns the input if it's not a <c>Jcc/JMP SHORT</c> instruction.
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
		static Code ToNearBranch(Code code);


		/// <summary>
		/// Checks if it's a <c>Jcc SHORT</c> or <c>Jcc NEAR</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJccShortOrNear(this Code code)
		static bool IsJccShortOrNear(Code code);
		/// <summary>
		/// Checks if it's a <c>Jcxz SHORT</c>, <c>Jecxz SHORT</c> or <c>Jrcxz SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsJcxShort(this Code code)
		static bool IsJcxShort(Code code);
		/// <summary>
		/// Checks if it's a <c>LOOPcc SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsLoopcc(this Code code)
		static bool IsLoopcc(Code code);
		/// <summary>
		/// Checks if it's a <c>LOOP SHORT</c> instruction
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsLoop(this Code code)
		static bool IsLoop(Code code);
	};
}
