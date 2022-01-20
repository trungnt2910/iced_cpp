// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "Code.g.h"
#include "OpCodeInfo.h"
#include "EncoderInternal/OpCodeInfos.h"

#include <stdexcept>

namespace Iced::Intel
{
	/// <summary>
	/// Extensions
	/// </summary>
	class EncoderCodeExtensions final
	{
		/// <summary>
		/// Gets a <see cref="OpCodeInfo"/>
		/// </summary>
		/// <param name="code">Code value</param>
		/// <returns></returns>
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static OpCodeInfo ToOpCode(this Code code)
		inline static const OpCodeInfo& ToOpCode(Code code);
	};

	inline const OpCodeInfo& EncoderCodeExtensions::ToOpCode(Code code)
	{
		const auto& infos = EncoderInternal::OpCodeInfos::Infos;
		if (static_cast<std::uint32_t>(code) >= static_cast<std::uint32_t>(infos.size()))
		{
			throw std::invalid_argument("invalid code");
		}
		return infos[static_cast<std::int32_t>(code)];
	}
}
