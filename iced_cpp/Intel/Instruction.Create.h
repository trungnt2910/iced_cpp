// C# helper headers

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
	// GENERATOR-BEGIN: RepPrefixKind
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	/// <summary><c>REP</c>/<c>REPE</c>/<c>REPNE</c> prefix</summary>
	enum class RepPrefixKind
	{
		/// <summary>No <c>REP</c>/<c>REPE</c>/<c>REPNE</c> prefix</summary>
		None = 0,
		/// <summary><c>REP</c>/<c>REPE</c> prefix</summary>
		Repe = 1,
		/// <summary><c>REPNE</c> prefix</summary>
		Repne = 2
	};

	DEFINE_COMP(RepPrefixKind)
		DEFINE_ARITH(RepPrefixKind)

		// GENERATOR-END: RepPrefixKind
}
