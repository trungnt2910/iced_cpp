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
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	/// <summary>MVEX tuple type lut kind used together with the <c>MVEX.SSS</c> bits to get the tuple type</summary>
	enum class MvexTupleTypeLutKind
	{
		/// <summary><see cref="int"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c></summary>
		Int32 = 0,
		/// <summary><see cref="int"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with half memory size (32 bytes instead of 64 bytes, eg. <c>VCVTUDQ2PD</c>/<c>VCVTDQ2PD</c>)</summary>
		Int32_Half = 1,
		/// <summary><see cref="int"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with built-in <c>{4to16}</c> broadcast</summary>
		Int32_4to16 = 2,
		/// <summary><see cref="int"/> elements, eg. <c>Si32</c>/<c>Di32</c>/<c>Ui32</c> with built-in <c>{1to16}</c> broadcast or element level</summary>
		Int32_1to16_or_elem = 3,
		/// <summary><see cref="long"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c></summary>
		Int64 = 4,
		/// <summary><see cref="long"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c> with built-in <c>{4to8}</c> broadcast</summary>
		Int64_4to8 = 5,
		/// <summary><see cref="long"/> elements, eg. <c>Si64</c>/<c>Di64</c>/<c>Ui64</c> with built-in <c>{1to8}</c> broadcast or element level</summary>
		Int64_1to8_or_elem = 6,
		/// <summary><see cref="float"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c></summary>
		Float32 = 7,
		/// <summary><see cref="float"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with half memory size (32 bytes instead of 64 bytes, eg. <c>VCVTPS2PD</c></summary>
		Float32_Half = 8,
		/// <summary><see cref="float"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with built-in <c>{4to16}</c> broadcast</summary>
		Float32_4to16 = 9,
		/// <summary><see cref="float"/> elements, eg. <c>Sf32</c>/<c>Df32</c>/<c>Uf32</c> with built-in <c>{1to16}</c> broadcast or element level</summary>
		Float32_1to16_or_elem = 10,
		/// <summary><see cref="double"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c></summary>
		Float64 = 11,
		/// <summary><see cref="double"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c> with built-in <c>{4to8}</c> broadcast</summary>
		Float64_4to8 = 12,
		/// <summary><see cref="double"/> elements, eg. <c>Sf64</c>/<c>Df64</c>/<c>Uf64</c> with built-in <c>{1to8}</c> broadcast or element level</summary>
		Float64_1to8_or_elem = 13
	};

	DEFINE_COMP(MvexTupleTypeLutKind)
		DEFINE_ARITH(MvexTupleTypeLutKind)

}
