/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(GAS) || defined(INTEL) || defined(MASM) || defined(NASM) || defined(FAST_FMT)
#include <array>
#include <stdexcept>
#include <string>
#include "ToString.h"
#include "Internal/StringHelpers.h"
namespace Iced::Intel {
	enum class MemorySizeOptions {
		/// <summary>Show memory size if the assembler requires it, else don&apos;t show anything</summary>
		Default  = 0,
		/// <summary>Always show the memory size, even if the assembler doesn&apos;t need it</summary>
		Always  = 1,
		/// <summary>Show memory size if a human can&apos;t figure out the size of the operand</summary>
		Minimal  = 2,
		/// <summary>Never show memory size</summary>
		Never  = 3,
	};
	constexpr int operator+(const MemorySizeOptions& a, const MemorySizeOptions& b) { return ((int)a + (int)b); }
	constexpr int operator+(const MemorySizeOptions& a, const int& b) { return ((int)a + b); }
	constexpr int operator+(const int& a, const MemorySizeOptions& b) { return (a + (int)b); }
	constexpr int operator-(const MemorySizeOptions& a, const MemorySizeOptions& b) { return ((int)a - (int)b); }
	constexpr int operator-(const MemorySizeOptions& a, const int& b) { return ((int)a - b); }
	constexpr int operator-(const int& a, const MemorySizeOptions& b) { return (a - (int)b); }
	constexpr MemorySizeOptions operator++(MemorySizeOptions& a, int) { auto temp = a; a = MemorySizeOptions(a + 1); return temp; }
	constexpr MemorySizeOptions& operator++(MemorySizeOptions& a) { return a = MemorySizeOptions(a + 1); }
	constexpr MemorySizeOptions operator--(MemorySizeOptions& a, int) { auto temp = a; a = MemorySizeOptions(a - 1); return temp; }
	constexpr MemorySizeOptions& operator--(MemorySizeOptions& a) { return a = MemorySizeOptions(a - 1); }
	constexpr bool operator==(const MemorySizeOptions& a, const int& b) { return ((int)a == b); }
	constexpr bool operator==(const int& a, const MemorySizeOptions& b) { return (a == (int)b); }
	constexpr bool operator>=(const MemorySizeOptions& a, const int& b) { return ((int)a >= b); }
	constexpr bool operator>=(const int& a, const MemorySizeOptions& b) { return (a >= (int)b); }
	constexpr bool operator<=(const MemorySizeOptions& a, const int& b) { return ((int)a <= b); }
	constexpr bool operator<=(const int& a, const MemorySizeOptions& b) { return (a <= (int)b); }
	constexpr bool operator>(const MemorySizeOptions& a, const int& b) { return ((int)a > b); }
	constexpr bool operator>(const int& a, const MemorySizeOptions& b) { return (a > (int)b); }
	constexpr bool operator<(const MemorySizeOptions& a, const int& b) { return ((int)a < b); }
	constexpr bool operator<(const int& a, const MemorySizeOptions& b) { return (a < (int)b); }
	constexpr bool operator!=(const MemorySizeOptions& a, const int& b) { return ((int)a != b); }
	constexpr bool operator!=(const int& a, const MemorySizeOptions& b) { return (a != (int)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::MemorySizeOptions& e) {
	switch (e) {
		case Iced::Intel::MemorySizeOptions::Default: return "Default";
		case Iced::Intel::MemorySizeOptions::Always: return "Always";
		case Iced::Intel::MemorySizeOptions::Minimal: return "Minimal";
		case Iced::Intel::MemorySizeOptions::Never: return "Never";
		default: return Internal::StringHelpers::ToDec((int)e);
	}
}
#endif
