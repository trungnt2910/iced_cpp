/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(MASM)
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include "../ToString.h"
#include "../Internal/StringHelpers.h"
namespace Iced::Intel::MasmFormatterInternal {
	enum class InstrOpInfoFlags : std::uint16_t {
		None  = 0x00000000,
		MemSize_Mask  = 0x00000007,
		MemSize_Sse  = 0x00000000,
		MemSize_Mmx  = 0x00000001,
		MemSize_Normal  = 0x00000002,
		MemSize_Nothing  = 0x00000003,
		MemSize_XmmwordPtr  = 0x00000004,
		MemSize_DwordOrQword  = 0x00000005,
		ShowNoMemSize_ForceSize  = 0x00000008,
		ShowMinMemSize_ForceSize  = 0x00000010,
		JccNotTaken  = 0x00000020,
		JccTaken  = 0x00000040,
		BndPrefix  = 0x00000080,
		IgnoreIndexReg  = 0x00000100,
		MnemonicIsDirective  = 0x00000200,
	};
	constexpr InstrOpInfoFlags& operator^=(InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return a = (InstrOpInfoFlags)((std::uint16_t)a ^ (std::uint16_t)b); }
	constexpr InstrOpInfoFlags operator^(const InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return (InstrOpInfoFlags)((std::uint16_t)a ^ (std::uint16_t)b); }
	constexpr InstrOpInfoFlags& operator|=(InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return a = (InstrOpInfoFlags)((std::uint16_t)a | (std::uint16_t)b); }
	constexpr InstrOpInfoFlags operator|(const InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return (InstrOpInfoFlags)((std::uint16_t)a | (std::uint16_t)b); }
	constexpr InstrOpInfoFlags& operator&=(InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return a = (InstrOpInfoFlags)((std::uint16_t)a & (std::uint16_t)b); }
	constexpr InstrOpInfoFlags operator&(const InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return (InstrOpInfoFlags)((std::uint16_t)a & (std::uint16_t)b); }
	constexpr InstrOpInfoFlags operator~(const InstrOpInfoFlags& a) { return (InstrOpInfoFlags)(~((std::uint16_t)a)); }
	constexpr std::uint16_t operator+(const InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return ((std::uint16_t)a + (std::uint16_t)b); }
	constexpr std::uint16_t operator+(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a + b); }
	constexpr std::uint16_t operator+(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a + (std::uint16_t)b); }
	constexpr std::uint16_t operator-(const InstrOpInfoFlags& a, const InstrOpInfoFlags& b) { return ((std::uint16_t)a - (std::uint16_t)b); }
	constexpr std::uint16_t operator-(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a - b); }
	constexpr std::uint16_t operator-(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a - (std::uint16_t)b); }
	constexpr InstrOpInfoFlags operator++(InstrOpInfoFlags& a, int) { auto temp = a; a = InstrOpInfoFlags(a + 1); return temp; }
	constexpr InstrOpInfoFlags& operator++(InstrOpInfoFlags& a) { return a = InstrOpInfoFlags(a + 1); }
	constexpr InstrOpInfoFlags operator--(InstrOpInfoFlags& a, int) { auto temp = a; a = InstrOpInfoFlags(a - 1); return temp; }
	constexpr InstrOpInfoFlags& operator--(InstrOpInfoFlags& a) { return a = InstrOpInfoFlags(a - 1); }
	constexpr bool operator==(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a == b); }
	constexpr bool operator==(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a == (std::uint16_t)b); }
	constexpr bool operator>=(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a >= b); }
	constexpr bool operator>=(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a >= (std::uint16_t)b); }
	constexpr bool operator<=(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a <= b); }
	constexpr bool operator<=(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a <= (std::uint16_t)b); }
	constexpr bool operator>(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a > b); }
	constexpr bool operator>(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a > (std::uint16_t)b); }
	constexpr bool operator<(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a < b); }
	constexpr bool operator<(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a < (std::uint16_t)b); }
	constexpr bool operator!=(const InstrOpInfoFlags& a, const std::uint16_t& b) { return ((std::uint16_t)a != b); }
	constexpr bool operator!=(const std::uint16_t& a, const InstrOpInfoFlags& b) { return (a != (std::uint16_t)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags& e) {
	std::string result;
	auto temp = e;
	if (temp == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::None) {
		return "None";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mask) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mask) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mask;
		result += "MemSize_Mask, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Nothing) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Nothing) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Nothing;
		result += "MemSize_Nothing, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_DwordOrQword) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_DwordOrQword) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_DwordOrQword;
		result += "MemSize_DwordOrQword, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mmx) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mmx) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Mmx;
		result += "MemSize_Mmx, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Normal) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Normal) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_Normal;
		result += "MemSize_Normal, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_XmmwordPtr) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_XmmwordPtr) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MemSize_XmmwordPtr;
		result += "MemSize_XmmwordPtr, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowNoMemSize_ForceSize) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowNoMemSize_ForceSize) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowNoMemSize_ForceSize;
		result += "ShowNoMemSize_ForceSize, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowMinMemSize_ForceSize) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowMinMemSize_ForceSize) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::ShowMinMemSize_ForceSize;
		result += "ShowMinMemSize_ForceSize, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccNotTaken) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccNotTaken) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccNotTaken;
		result += "JccNotTaken, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccTaken) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccTaken) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::JccTaken;
		result += "JccTaken, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::BndPrefix) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::BndPrefix) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::BndPrefix;
		result += "BndPrefix, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::IgnoreIndexReg) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::IgnoreIndexReg) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::IgnoreIndexReg;
		result += "IgnoreIndexReg, ";
	}
	if ((temp & Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MnemonicIsDirective) == Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MnemonicIsDirective) {
		temp ^= Iced::Intel::MasmFormatterInternal::InstrOpInfoFlags::MnemonicIsDirective;
		result += "MnemonicIsDirective, ";
	}
	if (temp != 0 || result.empty()) return Internal::StringHelpers::ToDec((std::uint16_t)e);
	return result.substr(0, result.size() - 2);
}
#endif
