// C# helper headers




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
#include "Mnemonic.g.h"
#include "MnemonicUtilsData.g.h"
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Extension methods
	/// </summary>
	class MnemonicUtils final
	{
		/// <summary>
		/// Gets the mnemonic
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static Mnemonic Mnemonic(this Code code)
		static constexpr Iced::Intel::Mnemonic Mnemonic(Code code)
		{
			return static_cast<Iced::Intel::Mnemonic>(MnemonicUtilsData::toMnemonic[static_cast<std::int32_t>(code)]);
		}
	};
}
