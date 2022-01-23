/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(DECODER) || defined(ENCODER)
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include "ToString.h"
#include "Internal/StringHelpers.h"
namespace Iced::Intel {
	enum class MandatoryPrefixByte : std::uint32_t {
		None ,
		P66 ,
		PF3 ,
		PF2 ,
	};
	constexpr std::uint32_t operator+(const MandatoryPrefixByte& a, const MandatoryPrefixByte& b) { return ((std::uint32_t)a + (std::uint32_t)b); }
	constexpr std::uint32_t operator+(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a + b); }
	constexpr std::uint32_t operator+(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a + (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const MandatoryPrefixByte& a, const MandatoryPrefixByte& b) { return ((std::uint32_t)a - (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a - b); }
	constexpr std::uint32_t operator-(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a - (std::uint32_t)b); }
	constexpr MandatoryPrefixByte operator++(MandatoryPrefixByte& a, int) { auto temp = a; a = MandatoryPrefixByte(a + 1); return temp; }
	constexpr MandatoryPrefixByte& operator++(MandatoryPrefixByte& a) { return a = MandatoryPrefixByte(a + 1); }
	constexpr MandatoryPrefixByte operator--(MandatoryPrefixByte& a, int) { auto temp = a; a = MandatoryPrefixByte(a - 1); return temp; }
	constexpr MandatoryPrefixByte& operator--(MandatoryPrefixByte& a) { return a = MandatoryPrefixByte(a - 1); }
	constexpr bool operator==(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a == b); }
	constexpr bool operator==(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a == (std::uint32_t)b); }
	constexpr bool operator>=(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a >= b); }
	constexpr bool operator>=(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a >= (std::uint32_t)b); }
	constexpr bool operator<=(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a <= b); }
	constexpr bool operator<=(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a <= (std::uint32_t)b); }
	constexpr bool operator>(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a > b); }
	constexpr bool operator>(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a > (std::uint32_t)b); }
	constexpr bool operator<(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a < b); }
	constexpr bool operator<(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a < (std::uint32_t)b); }
	constexpr bool operator!=(const MandatoryPrefixByte& a, const std::uint32_t& b) { return ((std::uint32_t)a != b); }
	constexpr bool operator!=(const std::uint32_t& a, const MandatoryPrefixByte& b) { return (a != (std::uint32_t)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::MandatoryPrefixByte& e) {
	switch (e) {
		case Iced::Intel::MandatoryPrefixByte::None: return "None";
		case Iced::Intel::MandatoryPrefixByte::P66: return "P66";
		case Iced::Intel::MandatoryPrefixByte::PF3: return "PF3";
		case Iced::Intel::MandatoryPrefixByte::PF2: return "PF2";
		default: return Internal::StringHelpers::ToDec((std::uint32_t)e);
	}
}
#endif
