// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Fast formatter options
	/// </summary>
	class FastFormatterOptions final
	{
	private:
		enum class Flags1 : int
		{
			None = 0,
			SpaceAfterOperandSeparator = 0x00000001,
			RipRelativeAddresses = 0x00000002,
			UsePseudoOps = 0x00000004,
			ShowSymbolAddress = 0x00000008,
			AlwaysShowSegmentRegister = 0x00000010,
			AlwaysShowMemorySize = 0x00000020,
			UppercaseHex = 0x00000040,
			UseHexPrefix = 0x00000080
		};

		DEFINE_FLAGS_FRIEND(Flags1)
		DEFINE_COMP_FRIEND(Flags1)
			DEFINE_ARITH_FRIEND(Flags1)
	private:
		Flags1 flags1 = static_cast<Flags1>(0);
	public:
		FastFormatterOptions();
		/// <summary>
		/// Add a space after the operand separator
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov rax, rcx</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov rax,rcx</c>
		/// </summary>
		bool GetSpaceAfterOperandSeparator() const;
		void SetSpaceAfterOperandSeparator(bool value);
		/// <summary>
		/// Show <c>RIP+displ</c> or the virtual address
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rip+12345678h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[1029384756AFBECDh]</c>
		/// </summary>
		bool GetRipRelativeAddresses() const;
		void SetRipRelativeAddresses(bool value);
		/// <summary>
		/// Use pseudo instructions
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>vcmpnltsd xmm2,xmm6,xmm3</c>
		/// <br/>
		/// <see langword="false"/>: <c>vcmpsd xmm2,xmm6,xmm3,5</c>
		/// </summary>
		bool GetUsePseudoOps() const;
		void SetUsePseudoOps(bool value);
		/// <summary>
		/// Show the original value after the symbol name
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[myfield (12345678)]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[myfield]</c>
		/// </summary>
		bool GetShowSymbolAddress() const;
		void SetShowSymbolAddress(bool value);
		/// <summary>
		/// Always show the effective segment register. If the option is <see langword="false"/>, only show the segment register if
		/// there's a segment override prefix.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,ds:[ecx]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[ecx]</c>
		/// </summary>
		bool GetAlwaysShowSegmentRegister() const;
		void SetAlwaysShowSegmentRegister(bool value);
		/// <summary>
		/// Always show memory operands' size
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,dword ptr [ebx]</c> / <c>add byte ptr [eax],0x12</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[ebx]</c> / <c>add byte ptr [eax],0x12</c>
		/// </summary>
		bool GetAlwaysShowMemorySize() const;
		void SetAlwaysShowMemorySize(bool value);
		/// <summary>
		/// Use uppercase hex digits
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>0xFF</c>
		/// <br/>
		/// <see langword="false"/>: <c>0xff</c>
		/// </summary>
		bool GetUppercaseHex() const;
		void SetUppercaseHex(bool value);
		/// <summary>
		/// Use a hex prefix (<c>0x</c>) or a hex suffix (<c>h</c>)
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>0x5A</c>
		/// <br/>
		/// <see langword="false"/>: <c>5Ah</c>
		/// </summary>
		bool GetUseHexPrefix() const;
		void SetUseHexPrefix(bool value);
	};
}
