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

#include <string>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// This is needed because net45/netstandard2.0 reference assemblies don't
// have any nullable attributes
namespace System
{
	class string2 final
	{
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsNullOrEmpty([NotNullWhen(false)] string? value)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsNullOrEmpty([NotNullWhen(false)] string? value)
		static bool IsNullOrEmpty(const std::string& value);
	};
}
namespace System::Diagnostics
{
	class Debug2 final
	{
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [Conditional("DEBUG")] public static void Assert([DoesNotReturnIf(false)] bool condition)
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [Conditional("DEBUG")] public static void Assert([DoesNotReturnIf(false)] bool condition)
		static void Assert(bool condition);
	};
}
