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
	enum class MvexTupleTypeLutKind {
		/// <summary><see cref="int_"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c></summary>
		Int32  = 0,
		/// <summary><see cref="int_"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with half memory size (32 bytes instead of 64 bytes, eg. <c>VCVTUDQ2PD</c>/<c>VCVTDQ2PD</c>)</summary>
		Int32_Half  = 1,
		/// <summary><see cref="int_"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with built-in <c>{4to16}</c> broadcast</summary>
		Int32_4to16  = 2,
		/// <summary><see cref="int_"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with built-in <c>{1to16}</c> broadcast or element level</summary>
		Int32_1to16_or_elem  = 3,
		/// <summary><see cref="long_"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c></summary>
		Int64  = 4,
		/// <summary><see cref="long_"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c> with built-in <c>{4to8}</c> broadcast</summary>
		Int64_4to8  = 5,
		/// <summary><see cref="long_"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c> with built-in <c>{1to8}</c> broadcast or element level</summary>
		Int64_1to8_or_elem  = 6,
		/// <summary><see cref="float_"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c></summary>
		Float32  = 7,
		/// <summary><see cref="float_"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with half memory size (32 bytes instead of 64 bytes, eg. <c>VCVTPS2PD</c></summary>
		Float32_Half  = 8,
		/// <summary><see cref="float_"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with built-in <c>{4to16}</c> broadcast</summary>
		Float32_4to16  = 9,
		/// <summary><see cref="float_"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with built-in <c>{1to16}</c> broadcast or element level</summary>
		Float32_1to16_or_elem  = 10,
		/// <summary><see cref="double_"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c></summary>
		Float64  = 11,
		/// <summary><see cref="double_"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c> with built-in <c>{4to8}</c> broadcast</summary>
		Float64_4to8  = 12,
		/// <summary><see cref="double_"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c> with built-in <c>{1to8}</c> broadcast or element level</summary>
		Float64_1to8_or_elem  = 13,
	};
	constexpr int operator+(const MvexTupleTypeLutKind& a, const MvexTupleTypeLutKind& b) { return ((int)a + (int)b); }
	constexpr int operator+(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a + b); }
	constexpr int operator+(const int& a, const MvexTupleTypeLutKind& b) { return (a + (int)b); }
	constexpr int operator-(const MvexTupleTypeLutKind& a, const MvexTupleTypeLutKind& b) { return ((int)a - (int)b); }
	constexpr int operator-(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a - b); }
	constexpr int operator-(const int& a, const MvexTupleTypeLutKind& b) { return (a - (int)b); }
	constexpr MvexTupleTypeLutKind operator++(MvexTupleTypeLutKind& a, int) { auto temp = a; a = MvexTupleTypeLutKind(a + 1); return temp; }
	constexpr MvexTupleTypeLutKind& operator++(MvexTupleTypeLutKind& a) { return a = MvexTupleTypeLutKind(a + 1); }
	constexpr MvexTupleTypeLutKind operator--(MvexTupleTypeLutKind& a, int) { auto temp = a; a = MvexTupleTypeLutKind(a - 1); return temp; }
	constexpr MvexTupleTypeLutKind& operator--(MvexTupleTypeLutKind& a) { return a = MvexTupleTypeLutKind(a - 1); }
	constexpr bool operator==(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a == b); }
	constexpr bool operator==(const int& a, const MvexTupleTypeLutKind& b) { return (a == (int)b); }
	constexpr bool operator>=(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a >= b); }
	constexpr bool operator>=(const int& a, const MvexTupleTypeLutKind& b) { return (a >= (int)b); }
	constexpr bool operator<=(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a <= b); }
	constexpr bool operator<=(const int& a, const MvexTupleTypeLutKind& b) { return (a <= (int)b); }
	constexpr bool operator>(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a > b); }
	constexpr bool operator>(const int& a, const MvexTupleTypeLutKind& b) { return (a > (int)b); }
	constexpr bool operator<(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a < b); }
	constexpr bool operator<(const int& a, const MvexTupleTypeLutKind& b) { return (a < (int)b); }
	constexpr bool operator!=(const MvexTupleTypeLutKind& a, const int& b) { return ((int)a != b); }
	constexpr bool operator!=(const int& a, const MvexTupleTypeLutKind& b) { return (a != (int)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::MvexTupleTypeLutKind& e) {
	switch (e) {
		case Iced::Intel::MvexTupleTypeLutKind::Int32: return "Int32";
		case Iced::Intel::MvexTupleTypeLutKind::Int32_Half: return "Int32_Half";
		case Iced::Intel::MvexTupleTypeLutKind::Int32_4to16: return "Int32_4to16";
		case Iced::Intel::MvexTupleTypeLutKind::Int32_1to16_or_elem: return "Int32_1to16_or_elem";
		case Iced::Intel::MvexTupleTypeLutKind::Int64: return "Int64";
		case Iced::Intel::MvexTupleTypeLutKind::Int64_4to8: return "Int64_4to8";
		case Iced::Intel::MvexTupleTypeLutKind::Int64_1to8_or_elem: return "Int64_1to8_or_elem";
		case Iced::Intel::MvexTupleTypeLutKind::Float32: return "Float32";
		case Iced::Intel::MvexTupleTypeLutKind::Float32_Half: return "Float32_Half";
		case Iced::Intel::MvexTupleTypeLutKind::Float32_4to16: return "Float32_4to16";
		case Iced::Intel::MvexTupleTypeLutKind::Float32_1to16_or_elem: return "Float32_1to16_or_elem";
		case Iced::Intel::MvexTupleTypeLutKind::Float64: return "Float64";
		case Iced::Intel::MvexTupleTypeLutKind::Float64_4to8: return "Float64_4to8";
		case Iced::Intel::MvexTupleTypeLutKind::Float64_1to8_or_elem: return "Float64_1to8_or_elem";
		default: return Internal::StringHelpers::ToDec((int)e);
	}
}
#endif
