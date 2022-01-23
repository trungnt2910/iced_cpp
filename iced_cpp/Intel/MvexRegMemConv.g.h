/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(MVEX)
#include <array>
#include <stdexcept>
#include <string>
#include "ToString.h"
#include "Internal/StringHelpers.h"
namespace Iced::Intel {
	enum class MvexRegMemConv {
		/// <summary>No operand conversion</summary>
		None  = 0,
		/// <summary>Register swizzle: <c>zmm0</c> or <c>zmm0 {dcba}</c></summary>
		RegSwizzleNone  = 1,
		/// <summary>Register swizzle: <c>zmm0 {cdab}</c></summary>
		RegSwizzleCdab  = 2,
		/// <summary>Register swizzle: <c>zmm0 {badc}</c></summary>
		RegSwizzleBadc  = 3,
		/// <summary>Register swizzle: <c>zmm0 {dacb}</c></summary>
		RegSwizzleDacb  = 4,
		/// <summary>Register swizzle: <c>zmm0 {aaaa}</c></summary>
		RegSwizzleAaaa  = 5,
		/// <summary>Register swizzle: <c>zmm0 {bbbb}</c></summary>
		RegSwizzleBbbb  = 6,
		/// <summary>Register swizzle: <c>zmm0 {cccc}</c></summary>
		RegSwizzleCccc  = 7,
		/// <summary>Register swizzle: <c>zmm0 {dddd}</c></summary>
		RegSwizzleDddd  = 8,
		/// <summary>Memory Up/DownConv: <c>[rax]</c> / <c>zmm0</c></summary>
		MemConvNone  = 9,
		/// <summary>Memory UpConv: <c>[rax] {1to16}</c> or <c>[rax] {1to8}</c></summary>
		MemConvBroadcast1  = 10,
		/// <summary>Memory UpConv: <c>[rax] {4to16}</c> or <c>[rax] {4to8}</c></summary>
		MemConvBroadcast4  = 11,
		/// <summary>Memory Up/DownConv: <c>[rax] {float16}</c> / <c>zmm0 {float16}</c></summary>
		MemConvFloat16  = 12,
		/// <summary>Memory Up/DownConv: <c>[rax] {uint8}</c> / <c>zmm0 {uint8}</c></summary>
		MemConvUint8  = 13,
		/// <summary>Memory Up/DownConv: <c>[rax] {sint8}</c> / <c>zmm0 {sint8}</c></summary>
		MemConvSint8  = 14,
		/// <summary>Memory Up/DownConv: <c>[rax] {uint16}</c> / <c>zmm0 {uint16}</c></summary>
		MemConvUint16  = 15,
		/// <summary>Memory Up/DownConv: <c>[rax] {sint16}</c> / <c>zmm0 {sint16}</c></summary>
		MemConvSint16  = 16,
	};
	constexpr int operator+(const MvexRegMemConv& a, const MvexRegMemConv& b) { return ((int)a + (int)b); }
	constexpr int operator+(const MvexRegMemConv& a, const int& b) { return ((int)a + b); }
	constexpr int operator+(const int& a, const MvexRegMemConv& b) { return (a + (int)b); }
	constexpr int operator-(const MvexRegMemConv& a, const MvexRegMemConv& b) { return ((int)a - (int)b); }
	constexpr int operator-(const MvexRegMemConv& a, const int& b) { return ((int)a - b); }
	constexpr int operator-(const int& a, const MvexRegMemConv& b) { return (a - (int)b); }
	constexpr MvexRegMemConv operator++(MvexRegMemConv& a, int) { auto temp = a; a = MvexRegMemConv(a + 1); return temp; }
	constexpr MvexRegMemConv& operator++(MvexRegMemConv& a) { return a = MvexRegMemConv(a + 1); }
	constexpr MvexRegMemConv operator--(MvexRegMemConv& a, int) { auto temp = a; a = MvexRegMemConv(a - 1); return temp; }
	constexpr MvexRegMemConv& operator--(MvexRegMemConv& a) { return a = MvexRegMemConv(a - 1); }
	constexpr bool operator==(const MvexRegMemConv& a, const int& b) { return ((int)a == b); }
	constexpr bool operator==(const int& a, const MvexRegMemConv& b) { return (a == (int)b); }
	constexpr bool operator>=(const MvexRegMemConv& a, const int& b) { return ((int)a >= b); }
	constexpr bool operator>=(const int& a, const MvexRegMemConv& b) { return (a >= (int)b); }
	constexpr bool operator<=(const MvexRegMemConv& a, const int& b) { return ((int)a <= b); }
	constexpr bool operator<=(const int& a, const MvexRegMemConv& b) { return (a <= (int)b); }
	constexpr bool operator>(const MvexRegMemConv& a, const int& b) { return ((int)a > b); }
	constexpr bool operator>(const int& a, const MvexRegMemConv& b) { return (a > (int)b); }
	constexpr bool operator<(const MvexRegMemConv& a, const int& b) { return ((int)a < b); }
	constexpr bool operator<(const int& a, const MvexRegMemConv& b) { return (a < (int)b); }
	constexpr bool operator!=(const MvexRegMemConv& a, const int& b) { return ((int)a != b); }
	constexpr bool operator!=(const int& a, const MvexRegMemConv& b) { return (a != (int)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::MvexRegMemConv& e) {
	switch (e) {
		case Iced::Intel::MvexRegMemConv::None: return "None";
		case Iced::Intel::MvexRegMemConv::RegSwizzleNone: return "RegSwizzleNone";
		case Iced::Intel::MvexRegMemConv::RegSwizzleCdab: return "RegSwizzleCdab";
		case Iced::Intel::MvexRegMemConv::RegSwizzleBadc: return "RegSwizzleBadc";
		case Iced::Intel::MvexRegMemConv::RegSwizzleDacb: return "RegSwizzleDacb";
		case Iced::Intel::MvexRegMemConv::RegSwizzleAaaa: return "RegSwizzleAaaa";
		case Iced::Intel::MvexRegMemConv::RegSwizzleBbbb: return "RegSwizzleBbbb";
		case Iced::Intel::MvexRegMemConv::RegSwizzleCccc: return "RegSwizzleCccc";
		case Iced::Intel::MvexRegMemConv::RegSwizzleDddd: return "RegSwizzleDddd";
		case Iced::Intel::MvexRegMemConv::MemConvNone: return "MemConvNone";
		case Iced::Intel::MvexRegMemConv::MemConvBroadcast1: return "MemConvBroadcast1";
		case Iced::Intel::MvexRegMemConv::MemConvBroadcast4: return "MemConvBroadcast4";
		case Iced::Intel::MvexRegMemConv::MemConvFloat16: return "MemConvFloat16";
		case Iced::Intel::MvexRegMemConv::MemConvUint8: return "MemConvUint8";
		case Iced::Intel::MvexRegMemConv::MemConvSint8: return "MemConvSint8";
		case Iced::Intel::MvexRegMemConv::MemConvUint16: return "MemConvUint16";
		case Iced::Intel::MvexRegMemConv::MemConvSint16: return "MemConvSint16";
		default: return Internal::StringHelpers::ToDec((int)e);
	}
}
#endif
