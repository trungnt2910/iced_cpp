// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>
#include <csharp/interfaces.h>
#include <csharp/primitives.h>

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace System
{
	// Array.Empty<T>() is only available since net46 (net45 doesn't support it)
	class Array2 final
	{
	public:
		template<typename T>
		static std::vector<T> Empty()
		{
			return EmptyClass<T>::Empty;
		}
	private:
		template<typename T>
		class EmptyClass final
		{
		public:
			static std::vector<T> Empty;
		};
	};
}
