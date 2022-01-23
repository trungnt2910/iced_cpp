/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(INSTR_INFO)
#include <array>
#include <stdexcept>
#include <string>
#include "ToString.h"
#include "Internal/StringHelpers.h"
namespace Iced::Intel {
	enum class FlowControl {
		/// <summary>The next instruction that will be executed is the next instruction in the instruction stream</summary>
		Next  = 0,
		/// <summary>It&apos;s an unconditional branch instruction: <c>JMP NEAR</c>, <c>JMP FAR</c></summary>
		UnconditionalBranch  = 1,
		/// <summary>It&apos;s an unconditional indirect branch: <c>JMP NEAR reg</c>, <c>JMP NEAR [mem]</c>, <c>JMP FAR [mem]</c></summary>
		IndirectBranch  = 2,
		/// <summary>It&apos;s a conditional branch instruction: <c>Jcc SHORT</c>, <c>Jcc NEAR</c>, <c>LOOP</c>, <c>LOOPcc</c>, <c>JRCXZ</c>, <c>JKccD SHORT</c>, <c>JKccD NEAR</c></summary>
		ConditionalBranch  = 3,
		/// <summary>It&apos;s a return instruction: <c>RET NEAR</c>, <c>RET FAR</c>, <c>IRET</c>, <c>SYSRET</c>, <c>SYSEXIT</c>, <c>RSM</c>, <c>SKINIT</c>, <c>RDM</c>, <c>UIRET</c></summary>
		Return  = 4,
		/// <summary>It&apos;s a call instruction: <c>CALL NEAR</c>, <c>CALL FAR</c>, <c>SYSCALL</c>, <c>SYSENTER</c>, <c>VMLAUNCH</c>, <c>VMRESUME</c>, <c>VMCALL</c>, <c>VMMCALL</c>, <c>VMGEXIT</c>, <c>VMRUN</c>, <c>TDCALL</c>, <c>SEAMCALL</c>, <c>SEAMRET</c></summary>
		Call  = 5,
		/// <summary>It&apos;s an indirect call instruction: <c>CALL NEAR reg</c>, <c>CALL NEAR [mem]</c>, <c>CALL FAR [mem]</c></summary>
		IndirectCall  = 6,
		/// <summary>It&apos;s an interrupt instruction: <c>INT n</c>, <c>INT3</c>, <c>INT1</c>, <c>INTO</c>, <c>SMINT</c>, <c>DMINT</c></summary>
		Interrupt  = 7,
		/// <summary>It&apos;s <c>XBEGIN</c></summary>
		XbeginXabortXend  = 8,
		/// <summary>It&apos;s an invalid instruction, eg. <see cref="Code.INVALID"/>, <c>UD0</c>, <c>UD1</c>, <c>UD2</c></summary>
		Exception  = 9,
	};
	constexpr int operator+(const FlowControl& a, const FlowControl& b) { return ((int)a + (int)b); }
	constexpr int operator+(const FlowControl& a, const int& b) { return ((int)a + b); }
	constexpr int operator+(const int& a, const FlowControl& b) { return (a + (int)b); }
	constexpr int operator-(const FlowControl& a, const FlowControl& b) { return ((int)a - (int)b); }
	constexpr int operator-(const FlowControl& a, const int& b) { return ((int)a - b); }
	constexpr int operator-(const int& a, const FlowControl& b) { return (a - (int)b); }
	constexpr FlowControl operator++(FlowControl& a, int) { auto temp = a; a = FlowControl(a + 1); return temp; }
	constexpr FlowControl& operator++(FlowControl& a) { return a = FlowControl(a + 1); }
	constexpr FlowControl operator--(FlowControl& a, int) { auto temp = a; a = FlowControl(a - 1); return temp; }
	constexpr FlowControl& operator--(FlowControl& a) { return a = FlowControl(a - 1); }
	constexpr bool operator==(const FlowControl& a, const int& b) { return ((int)a == b); }
	constexpr bool operator==(const int& a, const FlowControl& b) { return (a == (int)b); }
	constexpr bool operator>=(const FlowControl& a, const int& b) { return ((int)a >= b); }
	constexpr bool operator>=(const int& a, const FlowControl& b) { return (a >= (int)b); }
	constexpr bool operator<=(const FlowControl& a, const int& b) { return ((int)a <= b); }
	constexpr bool operator<=(const int& a, const FlowControl& b) { return (a <= (int)b); }
	constexpr bool operator>(const FlowControl& a, const int& b) { return ((int)a > b); }
	constexpr bool operator>(const int& a, const FlowControl& b) { return (a > (int)b); }
	constexpr bool operator<(const FlowControl& a, const int& b) { return ((int)a < b); }
	constexpr bool operator<(const int& a, const FlowControl& b) { return (a < (int)b); }
	constexpr bool operator!=(const FlowControl& a, const int& b) { return ((int)a != b); }
	constexpr bool operator!=(const int& a, const FlowControl& b) { return (a != (int)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::FlowControl& e) {
	switch (e) {
		case Iced::Intel::FlowControl::Next: return "Next";
		case Iced::Intel::FlowControl::UnconditionalBranch: return "UnconditionalBranch";
		case Iced::Intel::FlowControl::IndirectBranch: return "IndirectBranch";
		case Iced::Intel::FlowControl::ConditionalBranch: return "ConditionalBranch";
		case Iced::Intel::FlowControl::Return: return "Return";
		case Iced::Intel::FlowControl::Call: return "Call";
		case Iced::Intel::FlowControl::IndirectCall: return "IndirectCall";
		case Iced::Intel::FlowControl::Interrupt: return "Interrupt";
		case Iced::Intel::FlowControl::XbeginXabortXend: return "XbeginXabortXend";
		case Iced::Intel::FlowControl::Exception: return "Exception";
		default: return Internal::StringHelpers::ToDec((int)e);
	}
}
#endif
